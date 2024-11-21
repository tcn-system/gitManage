
#include "manage.h"

#include "../globalVar.h"

cManage::cManage(QWidget* qw_parent)
{
    init();

    if (qt_timer == nullptr) {
        qt_timer = new QTimer;
        connect(qt_timer, &QTimer::timeout, this, &cManage::SLOT_timerTick);
    }
}

cManage::~cManage()
{
    qDebug() << "~cManage";

    if (qt_timer != nullptr) {
        if (qt_timer->isActive())
            qt_timer->stop();

        disconnect(qt_timer, &QTimer::timeout, this, &cManage::SLOT_timerTick);

        delete qt_timer;
    }
}

void cManage::init()
{
    e_manage_action = e_action_init;

    e_manage_stat = e_manage_stat_init;
    i_manage_tempo = _D_STOP;

    _time_out = 500;
}

bool cManage::startManage()
{
    if (!qt_timer->isActive()) {
        init();

        qt_timer->start(10);
        i_manage_tempo = 0;

        c_globalVar->debugInConsoleEOL("p_startTimer");

        if (git_log_command)
            startLogFile();
        return true;
    }
    return false;
}
bool cManage::stopManage()
{
    if (qt_timer->isActive()) {
        qt_timer->stop();

        c_globalVar->debugInConsoleEOL("p_stopTimer");

        if (git_log_command)
            stopLogFile();

        init();

        return true;
    }
    return true;
}
bool cManage::isRunning()
{
    return qt_timer->isActive();
}

void cManage::SLOT_timerTick()
{
    disconnect(qt_timer, &QTimer::timeout, this, &cManage::SLOT_timerTick);

    if (i_manage_tempo >= 0)
        i_manage_tempo++;

    if (e_manage_stat != e_manage_stat_wait and i_manage_tempo >= _time_out) {
        _time_out = 500;

        if (processAction != nullptr) {
            stopProcess();

            c_globalVar->debugInConsoleEOL("SLOT_timerTick::timeout");
        }
        i_manage_tempo = 0;
        e_manage_stat = e_manage_stat_wait;
    }

    switch (e_manage_stat) {

    case e_manage_stat_init:

        c_globalVar->debugInConsoleEOL("cManage:: INIT");

        e_manage_stat = e_manage_stat_git_list_branch;
        i_manage_tempo = 0;
        break;

    case e_manage_stat_wait:
        if (i_manage_tempo == 1) {

            c_globalVar->debugInConsoleEOL("cManage:: WAIT");

            emit SIGNAL_action_finish(e_manage_action);

            e_manage_action = e_action_none;
        }
        if (i_manage_tempo > 1000) {
            //emit SIGNAL_action_busy();

            i_manage_tempo = 1;
            //e_manage_stat = e_manage_stat_git_status;
        }
        break;

    case e_manage_stat_git_list_config:
        if (i_manage_tempo == 1) {
            c_globalVar->debugInConsoleEOL("cManage:: git config list");

            askAction.clear();
            askAction << "config",
                askAction << "--list";

            startProcess();
        }
        if (processAction == nullptr) {

            show_answerAction();

            e_manage_stat = e_manage_stat_wait;
            i_manage_tempo = 0;
        }
        break;

    case e_manage_stat_git_list_log:
        if (i_manage_tempo == 1) {
            c_globalVar->debugInConsoleEOL("cManage:: git logs list");

            askAction.clear();
            askAction << "log";

            startProcess();
        }
        if (processAction == nullptr) {

            show_answerAction();

            e_manage_stat = e_manage_stat_wait;
            i_manage_tempo = 0;
        }
        break;

    case e_manage_stat_git_list_branch:
        if (i_manage_tempo == 1) {
            c_globalVar->debugInConsoleEOL("cManage:: git branch list");

            askAction.clear();
            askAction << "branch"
                      << "-a";

            startProcess();
        }
        if (processAction == nullptr) {

            show_answerAction();

            load_branch();

            if (e_manage_action == e_action_init
                || e_manage_action == e_action_git_pull
                || e_manage_action == e_action_git_push) {

                if (verif_branchs_integrity() == true)
                    e_manage_stat = e_manage_stat_git_list_remote;
                else
                    e_manage_stat = e_manage_stat_git_create_dev_branch;

            } else
                e_manage_stat = e_manage_stat_git_status;
            i_manage_tempo = 0;
        }
        break;
    case e_manage_stat_git_create_dev_branch:
        if (i_manage_tempo == 1) {
            c_globalVar->debugInConsoleEOL("cManage:: git branch create dev branch");

            askAction.clear();
            askAction << "branch"
                      << default_dev_branch;

            startProcess();
        }
        if (processAction == nullptr) {

            show_answerAction();

            e_manage_stat = e_manage_stat_git_checkout_dev_branch;
            i_manage_tempo = 0;
        }
        break;
    case e_manage_stat_git_checkout_dev_branch:
        if (i_manage_tempo == 1) {
            c_globalVar->debugInConsoleEOL("cManage:: git checkout dev branch");

            askAction.clear();
            askAction << "checkout"
                      << default_dev_branch;

            startProcess();
        }
        if (processAction == nullptr) {

            show_answerAction();

            // Switched to branch 'dev_tcn'

            e_manage_stat = e_manage_stat_git_list_branch;
            i_manage_tempo = 0;
        }
        break;

    case e_manage_stat_git_list_remote:
        if (i_manage_tempo == 1) {
            c_globalVar->debugInConsoleEOL("cManage:: git remote list");

            askAction.clear();
            askAction << "remote" << "-v";

            startProcess();
        }
        if (processAction == nullptr) {
            if (answerAction.size() > 0) {

                show_answerAction();

                load_remote();
            }

            if (e_manage_action == e_action_init)
                e_manage_stat = e_manage_stat_git_status;
            else
                e_manage_stat = e_manage_stat_git_status;
            i_manage_tempo = 0;
        }
        break;

    case e_manage_stat_git_add:
        if (i_manage_tempo == 1) {
            c_globalVar->debugInConsoleEOL("cManage:: git add .");

            askAction.clear();
            askAction << "add" << ".";

            startProcess();
        }
        if (processAction == nullptr) {

            show_answerAction();

            e_manage_stat = e_manage_stat_git_commit;
            i_manage_tempo = 0;
        }
        break;

    case e_manage_stat_git_commit:
        if (i_manage_tempo == 1) {
            c_globalVar->debugInConsoleEOL("cManage:: git commit");

            askAction.clear();
            // askAction << "commit" << "-m" << "\"" + messageAction + "\"";
            askAction << "commit" << "-m" << messageAction;

            startProcess();
        }
        if (processAction == nullptr) {

            show_answerAction();

            e_manage_stat = e_manage_stat_git_status;
            i_manage_tempo = 0;
        }
        break;

        ///
        /// PUSH
        ///

    case e_manage_stat_git_push:

        e_manage_stat = e_manage_stat_git_push___verif_commit_dev;
        i_manage_tempo = 0;

        break;
    case e_manage_stat_git_push___verif_commit_dev:
        if (i_manage_tempo == 1) {
            c_globalVar->debugInConsoleEOL("cManage:: PUSH git verif commit");

            askAction.clear();
            askAction << "status";

            startProcess();
        }
        if (processAction == nullptr) {
            if (answerAction.size() > 0) {

                show_answerAction();

                manage_status();

                if (current_gitProject.is_up_to_date == true) {

                    e_manage_stat = e_manage_stat_git_push___checkout_dev_to_master;
                    i_manage_tempo = 0;
                }
                else
                {
                    e_manage_stat = e_manage_stat_wait;
                    i_manage_tempo = 0;
                }
            }
        }
        break;
    case e_manage_stat_git_push___checkout_dev_to_master:
        if (i_manage_tempo == 1) {
            c_globalVar->debugInConsoleEOL("cManage:: PUSH git checkout dev to master");

            askAction.clear();
            askAction << "checkout"
                      << current_gitProject.main_master_branch_name;

            startProcess();
            _time_out = 3000; // 30 secondes
        }
        if (processAction == nullptr) {
            if (answerAction.size() > 0) {

                show_answerAction();

                // Switched to branch 'master'
                if(verif_answer_switch_to_branch(current_gitProject.main_master_branch_name))
                {
                    e_manage_stat = e_manage_stat_git_push___pull_master;
                    i_manage_tempo = 0;
                }
                else
                {
                    e_manage_stat = e_manage_stat_errors;
                    i_manage_tempo = 0;
                }
            }
        }
        break;
    case e_manage_stat_git_push___pull_master:
        if (i_manage_tempo == 1) {
            c_globalVar->debugInConsoleEOL("cManage:: PUSH git pull origin master");

            askAction.clear();
            askAction << "pull"
                      << current_gitProject.l_remotePush.nameRemote
                      << current_gitProject.main_master_branch_name; // l_branch.at(current_gitProject.idx_branch_in_process).nameBranch;

            startProcess();
            _time_out = 3000; // 30 secondes
        }
        if (processAction == nullptr) {
            if (answerAction.size() > 0) {

                show_answerAction();

                // Already up to date
                if(verif_answer_pull(current_gitProject.main_master_branch_name))
                {
                    e_manage_stat = e_manage_stat_git_push___merge_dev_to_master;
                    i_manage_tempo = 0;
                }
                else
                {
                    e_manage_stat = e_manage_stat_errors;
                    i_manage_tempo = 0;
                }
            }
        }
        break;
    case e_manage_stat_git_push___merge_dev_to_master:
        if (i_manage_tempo == 1) {
            c_globalVar->debugInConsoleEOL("cManage:: PUSH git merge dev to master");

            askAction.clear();
            askAction << "merge"
                      << default_dev_branch;

            startProcess();
            _time_out = 3000; // 30 secondes
        }
        if (processAction == nullptr) {
            if (answerAction.size() > 0) {

                show_answerAction();

                // Updating 5fd7b48..ac75ea1
                // Fast-forward
                if(verif_answer_merge(current_gitProject.main_master_branch_name , default_dev_branch))
                {
                    e_manage_stat = e_manage_stat_git_push___push_master_to_remote;
                    i_manage_tempo = 0;
                }
                else
                {
                    e_manage_stat = e_manage_stat_errors;
                    i_manage_tempo = 0;
                }
            }
        }
        break;
    case e_manage_stat_git_push___push_master_to_remote:
        if (i_manage_tempo == 1) {
            c_globalVar->debugInConsoleEOL("cManage:: PUSH git push master to remote");

            askAction.clear();
            askAction << "push"
                      << current_gitProject.l_remotePush.nameRemote
                      << current_gitProject.main_master_branch_name;

            startProcess();

            _time_out = 3000; // 30 secondes
        }
        if (processAction == nullptr) {
            if (answerAction.size() > 0) {

                show_answerAction();

                // To https://github.com/tcn-system/gitManage.git
                //   5fd7b48..ac75ea1  master -> master
                if(verif_answer_push(current_gitProject.main_master_branch_name))
                {
                    //e_manage_stat = e_manage_stat_git_push___delete_dev;

                    e_manage_stat = e_manage_stat_git___checkout_master_to_dev;
                    i_manage_tempo = 0;
                }
                else
                {
                    e_manage_stat = e_manage_stat_errors;
                    i_manage_tempo = 0;
                }
            }
        }
        break;
    case e_manage_stat_git_push___delete_dev:
        if (i_manage_tempo == 1) {
            c_globalVar->debugInConsoleEOL("cManage:: PUSH git branch delete dev branch");

            askAction.clear();
            askAction << "branch"
                      << "-d"
                      << default_dev_branch;

            startProcess();
        }
        if (processAction == nullptr) {
            if (answerAction.size() > 0) {

                show_answerAction();

                // Deleted branch dev_tcn (was ac75ea1).
                if(verif_answer_delete_branch(default_dev_branch))
                {
                    e_manage_stat = e_manage_stat_git_list_branch;
                    i_manage_tempo = 0;
                }
                else
                {
                    e_manage_stat = e_manage_stat_errors;
                    i_manage_tempo = 0;
                }
            }
        }
        break;

        ///
        /// PULL
        ///

    case e_manage_stat_git_pull:

        e_manage_stat = e_manage_stat_git_pull___verif_commit_dev;
        i_manage_tempo = 0;

        break;

    case e_manage_stat_git_pull___verif_commit_dev:
        if (i_manage_tempo == 1) {
            c_globalVar->debugInConsoleEOL("cManage:: PULL git verif commit");

            askAction.clear();
            askAction << "status";

            startProcess();
        }
        if (processAction == nullptr) {
            if (answerAction.size() > 0) {

                manage_status();

                if (current_gitProject.is_up_to_date == true) {

                    e_manage_stat = e_manage_stat_git_pull___checkout_dev_to_master;
                    i_manage_tempo = 0;
                }
                else
                {
                    e_manage_stat = e_manage_stat_wait;
                    i_manage_tempo = 0;
                }
            }
        }
        break;
    case e_manage_stat_git_pull___checkout_dev_to_master:
        if (i_manage_tempo == 1) {
            c_globalVar->debugInConsoleEOL("cManage:: PULL git checkout dev to master");

            askAction.clear();
            askAction << "checkout"
                      << current_gitProject.main_master_branch_name;

            startProcess();
            _time_out = 3000; // 30 secondes
        }
        if (processAction == nullptr) {
            if (answerAction.size() > 0) {

                show_answerAction();

                // Switched to branch 'master'
                if(verif_answer_switch_to_branch(current_gitProject.main_master_branch_name))
                {
                    e_manage_stat = e_manage_stat_git_pull___pull_master;
                    i_manage_tempo = 0;
                }
                else
                {
                    e_manage_stat = e_manage_stat_errors;
                    i_manage_tempo = 0;
                }
            }
        }
        break;
    case e_manage_stat_git_pull___pull_master:
        if (i_manage_tempo == 1) {
            c_globalVar->debugInConsoleEOL("cManage:: PULL git pull master from remote");

            askAction.clear();
            askAction << "pull"
                      << current_gitProject.l_remotePush.nameRemote
                      << current_gitProject.main_master_branch_name;

            startProcess();
            _time_out = 3000; // 30 secondes
        }
        if (processAction == nullptr) {
            if (answerAction.size() > 0) {

                show_answerAction();

                if(verif_answer_pull(current_gitProject.main_master_branch_name))
                {
                    e_manage_stat = e_manage_stat_git___checkout_master_to_dev;
                    i_manage_tempo = 0;
                }
                else
                {
                    e_manage_stat = e_manage_stat_errors;
                    i_manage_tempo = 0;
                }
            }
        }
        break;

        ///
        /// merge master to dev
        ///

    case e_manage_stat_git___checkout_master_to_dev:
        if (i_manage_tempo == 1) {
            c_globalVar->debugInConsoleEOL("cManage:: PULL git checkout master to dev");

            askAction.clear();
            askAction << "checkout"
                      << default_dev_branch;

            startProcess();
            _time_out = 3000; // 30 secondes
        }
        if (processAction == nullptr) {
            if (answerAction.size() > 0) {

                show_answerAction();

                if(verif_answer_switch_to_branch(default_dev_branch))
                {
                    e_manage_stat = e_manage_stat_git___merge_master_to_dev;
                    i_manage_tempo = 0;
                }
                else
                {
                    e_manage_stat = e_manage_stat_errors;
                    i_manage_tempo = 0;
                }
            }
        }
        break;

    case e_manage_stat_git___merge_master_to_dev:
        if (i_manage_tempo == 1) {
            c_globalVar->debugInConsoleEOL("cManage:: PULL git merge master to dev");

            askAction.clear();
            askAction << "merge"
                      << current_gitProject.main_master_branch_name;

            startProcess();
            _time_out = 3000; // 30 secondes
        }
        if (processAction == nullptr) {
            if (answerAction.size() > 0) {

                show_answerAction();

                if(verif_answer_merge(default_dev_branch, current_gitProject.main_master_branch_name))
                {
                    e_manage_stat = e_manage_stat_git_status;
                    i_manage_tempo = 0;
                }
                else
                {
                    e_manage_stat = e_manage_stat_errors;
                    i_manage_tempo = 0;
                }
            }
        }
        break;

        ///
        /// STATUS
        ///

    case e_manage_stat_git_status:
        if (i_manage_tempo == 1) {
            c_globalVar->debugInConsoleEOL("cManage:: git status");

            askAction.clear();
            askAction << "status";

            startProcess();
        }
        if (processAction == nullptr) {
            if (answerAction.size() > 0) {

                show_answerAction();

                manage_status();
            }

            if(verify_name_current_branch())
            {
                e_manage_stat = e_manage_stat_wait;
                i_manage_tempo = 0;
            }
            else
            {
                e_manage_stat = e_manage_stat_git_list_branch;
                i_manage_tempo = 0;
            }
        }
        break;


    case e_manage_stat_errors:
        if (i_manage_tempo == 1) {
            c_globalVar->debugInConsoleEOL("cManage:: ERROR");

            i_manage_tempo = -1;
        }
        break;


    default:
        stopManage();
        break;
    }

    connect(qt_timer, &QTimer::timeout, this, &cManage::SLOT_timerTick);
}

bool cManage::action(eActionStat _action)
{
    if (e_manage_stat == e_manage_stat_wait) {
        if (_action == e_action_git_config) {
            e_manage_action = _action;

            e_manage_stat = e_manage_stat_git_list_config;
            i_manage_tempo = 0;
            return true;
        }
        if (_action == e_action_git_log) {
            e_manage_action = _action;

            e_manage_stat = e_manage_stat_git_list_log;
            i_manage_tempo = 0;
            return true;
        }
        if (_action == e_action_git_branch_list) {
            e_manage_action = _action;

            e_manage_stat = e_manage_stat_git_list_branch;
            i_manage_tempo = 0;
            return true;
        }
        if (_action == e_action_git_branch_switch) {
            e_manage_action = _action;

            e_manage_stat = e_manage_stat_git_checkout_dev_branch;
            i_manage_tempo = 0;
            return true;
        }
        if (_action == e_action_git_remote_list) {
            e_manage_action = _action;

            e_manage_stat = e_manage_stat_git_list_remote;
            i_manage_tempo = 0;
            return true;
        }
        if (_action == e_action_git_push) {
            e_manage_action = _action;

            e_manage_stat = e_manage_stat_git_push;
            i_manage_tempo = 0;
            return true;
        }
        if (_action == e_action_git_pull) {
            e_manage_action = _action;

            e_manage_stat = e_manage_stat_git_pull;
            i_manage_tempo = 0;
            return true;
        }
        if (_action == e_action_git_status) {
            e_manage_action = _action;

            e_manage_stat = e_manage_stat_git_status;
            i_manage_tempo = 0;
            return true;
        }
    }
    return false;
}
bool cManage::action_message(eActionStat _action, QString _message)
{
    if (e_manage_stat == e_manage_stat_wait) {
        if (_action == e_action_git_commit) {
            e_manage_action = _action;

            e_manage_stat = e_manage_stat_git_add;
            messageAction = _message;
            i_manage_tempo = 0;
            return true;
        }
    }
    return false;
}

void cManage::show_answerAction()
{
    if (answerAction.size() > 0) {
        QString _textEdit = "";
        for (int i = 0; i < answerAction.size(); i++)
            _textEdit += answerAction.at(i) + "\n";

        emit SIGNAL_textEdit(_textEdit);
    }
}

void cManage::manage_status()
{
    current_gitProject.is_up_to_date = false;
    current_gitProject.nbre_commit = -1;

    for (int i = 0; i < answerAction.size(); i++) {

        QString _ligne = answerAction.at(i);

        if (_ligne.contains("Your branch is ahead")
            || _ligne.contains("Your branch is up to date"))
        {
            current_gitProject.nbre_commit = 1;
        }

        if (_ligne.contains("nothing to commit"))
        {
            current_gitProject.is_up_to_date = true;
        }
    }
}
bool cManage::verify_name_current_branch()
{
    for (int i = 0; i < answerAction.size(); i++) {

        QString _ligne = answerAction.at(i);

        if(_ligne.contains("On branch")) {

            _ligne = _ligne.replace("On branch","");
            _ligne = _ligne.trimmed();

            if(current_gitProject.l_branch.at(current_gitProject.idx_branch_in_process).nameBranch == _ligne)
            {
                return true;
            }
        }

    }
    return false;
}


void cManage::load_branch()
{
    current_gitProject.l_branch.clear();

    int nbre_local_branch = 0;
    int nbre_remote_branch = 0;

    for (int i = 0; i < answerAction.size(); i++) {

        QString _ligne = answerAction.at(i);

        if (_ligne.size() > 3 and not _ligne.contains("HEAD")) {

            QStringList l_element = _ligne.split("/");

            qDebug() << "l_element" << l_element;

            if(l_element.size() > 2 and l_element.at(0).contains("remotes")) // branch remote
            {
                _ligne = l_element.at(1) + "/" + l_element.at(2);

                _ligne = _ligne.simplified();
                _ligne = _ligne.trimmed();

                sGitBranch _branch;
                _branch.init();

                _branch.nameBranch = _ligne;

                current_gitProject.l_branch_remote.push_back(_branch);

                if(current_gitProject.idx_branch_remote_in_process < 0)
                    current_gitProject.idx_branch_remote_in_process = 0;

                nbre_remote_branch++;
            }
            else                     // branch local
            {
                _ligne = l_element.at(0);

                if (_ligne.contains("*"))
                    current_gitProject.idx_branch_in_process = nbre_local_branch;

                _ligne = _ligne.replace("*", "");
                _ligne = _ligne.simplified();
                _ligne = _ligne.trimmed();

                sGitBranch _branch;
                _branch.init();

                _branch.nameBranch = _ligne;

                current_gitProject.l_branch.push_back(_branch);

                nbre_local_branch++;
            }
        }
    }

    for (int i = 0; i < current_gitProject.l_branch.size(); i++) {
        c_globalVar->debugInConsoleEOL("branch -> " + current_gitProject.l_branch.at(i).nameBranch);
    }
}
bool cManage::verif_branchs_integrity()
{
    // il faut au moins deux branch , la principale et celle de dev

    if (current_gitProject.l_branch.size() < 2)
        return false;

    bool b_master_detect = false;
    bool b_default_dev_detect = false;

    for (int i = 0; i < current_gitProject.l_branch.size(); i++) {
        if (not current_gitProject.l_branch.at(i).nameBranch.compare("main")
            or not current_gitProject.l_branch.at(i).nameBranch.compare("master")) {

            current_gitProject.main_master_branch_name = current_gitProject.l_branch.at(i).nameBranch;

            b_master_detect = true;
        }
        if (not current_gitProject.l_branch.at(i).nameBranch.compare(default_dev_branch)) {
            b_default_dev_detect = true;
        }
    }

    if (b_master_detect and b_default_dev_detect)
        return true;

    return false;
}

bool cManage::verif_answer_switch_to_branch(QString _branch)
{
    for (int i = 0; i < answerAction.size(); i++) {
        QString _ligne = answerAction.at(i);

        if( _ligne.contains("Switched to branch")
        and _ligne.contains(_branch) )
        {
            return true;
        }
    }
    return false;
}
bool cManage::verif_answer_delete_branch(QString _branch)
{
    for (int i = 0; i < answerAction.size(); i++) {
        QString _ligne = answerAction.at(i);

        if( _ligne.contains("Deleted branch")
        and _ligne.contains(_branch) )
        {
            return true;
        }
    }

    return false;
}

bool cManage::verif_answer_push(QString _branch)
{

//    _ba "To https://github.com/tcn-system/gitManage.git" ("To", "https://github.com/tcn-system/gitManage.git")
//    _ba "ac75ea1..f1fec8f master -> master" ("ac75ea1..f1fec8f", "master", "->", "master")

    for (int i = 0; i < answerAction.size(); i++) {
        QString _ligne = answerAction.at(i);

        _ligne = _ligne.trimmed();
        _ligne = _ligne.simplified();

        QByteArray _ba = QByteArray(_ligne.toLatin1());

        QStringList l_ligne = _ligne.split(" ");
        if(l_ligne.size() > 3)
        {
            if(not l_ligne.at(1).compare(_branch) and not l_ligne.at(3).compare(_branch))
            {
                return true;
            }
        }
        qDebug() << "_ba" << _ba << l_ligne;

        if( _ligne.contains("Already up to date")
         || _ligne.contains("Everything up-to-date") )
        {
            return true;
        }
    }

    return false;
}
bool cManage::verif_answer_merge(QString _branch_src , QString _branch_dst)
{
    for (int i = 0; i < answerAction.size(); i++) {
        QString _ligne = answerAction.at(i);

        if( _ligne.contains("Fast-forward") ) // type merge
        {
            ;
        }

        if( _ligne.contains("files changed")
         || _ligne.contains("file changed"))
        {
            return true;
        }

        if( _ligne.contains("Already up to date")
         || _ligne.contains("Everything up-to-date") )
        {
            return true;
        }
    }

    return false;
}
bool cManage::verif_answer_pull(QString _branch)
{

//    _ba "From https://github.com/tcn-system/gitManage" ("From", "https://github.com/tcn-system/gitManage")
//    _ba "* branch master -> FETCH_HEAD" ("*", "branch", "master", "->", "FETCH_HEAD")

    for (int i = 0; i < answerAction.size(); i++) {
        QString _ligne = answerAction.at(i);

        _ligne = _ligne.trimmed();
        _ligne = _ligne.simplified();

        QByteArray _ba = QByteArray(_ligne.toLatin1());

        QStringList l_ligne = _ligne.split(" ");
        if(l_ligne.size() > 3)
        {
            if(not l_ligne.at(2).compare(_branch) and not l_ligne.at(4).compare("FETCH_HEAD"))
            {
                return true;
            }
        }
        qDebug() << "_ba" << _ba << l_ligne;

        if( _ligne.contains("Already up to date")
         || _ligne.contains("Everything up-to-date") )
        {
            return true;
        }
    }

    return false;
}


void cManage::load_remote()
{
    current_gitProject.l_remotePush.init();
    current_gitProject.l_remoteFetch.init();

    for (int i = 0; i < answerAction.size(); i++) {
        QString _ligne = answerAction.at(i);
        if (_ligne.size() > 3) {
            QStringList _l_remote = _ligne.split("\t");

            // qDebug() << "l_r" << _l_remote;

            if (_l_remote.size() >= 2) {
                sGitRemote _remote;
                _remote.init();

                _remote.nameRemote = _l_remote.at(0);

                QStringList _l_target = _l_remote.at(1).split(" ");
                if (_l_target.size() >= 2) {
                    _remote.pathRemote = _l_target.at(0);
                    if (not _l_target.at(1).compare("(push)"))
                        current_gitProject.l_remotePush = _remote;
                    if (not _l_target.at(1).compare("(fetch)"))
                        current_gitProject.l_remoteFetch = _remote;
                }
            }
        }
    }

    c_globalVar->debugInConsoleEOL("remote Push  -> " + current_gitProject.l_remotePush.nameRemote + " " + current_gitProject.l_remotePush.pathRemote);
    c_globalVar->debugInConsoleEOL("remote Fetch -> " + current_gitProject.l_remoteFetch.nameRemote + " " + current_gitProject.l_remoteFetch.pathRemote);
}

void cManage::startLogFile()
{
    QDateTime dateTime = QDateTime::currentDateTime();
    QString str;
    std::string filename;

    str = QString(c_globalVar->fileManager->logsDir().path() + "/git_cmd_" + dateTime.toString("yyyy-MM-dd-hh-mm-ss") + ".txt");
    filename = str.toStdString();

    fileLog = fopen(filename.c_str(), "wb");
}
void cManage::stopLogFile()
{
    fclose(fileLog);
}

bool cManage::startProcess()
{
    if (processAction == nullptr) {

        answerAction.clear();

        // LANG=en_US
        QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
        env.insert("LANG", "en_US");

        processAction = new QProcess;
        processAction->setWorkingDirectory(current_gitProject.dirPath.path());
        processAction->setProcessEnvironment(env);
        processAction->setProgram("git");
        processAction->setArguments(askAction);

        // processAction->setProcessChannelMode(QProcess::MergedChannels);

        QString _debug = processAction->program();
        QStringList _debugList = processAction->arguments();
        for (int i = 0; i < _debugList.size(); i++)
            _debug += " " + _debugList.at(i);
        c_globalVar->debugInConsoleEOL("process: " + _debug);

        connect(processAction, SIGNAL(readyRead()), this, SLOT(SLOT_action_readyRead()));
        connect(processAction, SIGNAL(readyReadStandardOutput()), this, SLOT(SLOT_action_rightMessage()));
        connect(processAction, SIGNAL(readyReadStandardError()), this, SLOT(SLOT_action_wrongMessage()));
        connect(processAction, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(SLOT_action_finish(int, QProcess::ExitStatus)));

        if (git_log_command)
            fprintf(fileLog, "-> %s\n", _debug.toStdString().c_str());

        emit SIGNAL_textEdit(_debug + "\n");

        processAction->start();
        processAction->waitForBytesWritten();

        return true;
    }
    return false;
}
void cManage::stopProcess()
{
    if (processAction != nullptr) {

        // c_globalVar->debugInConsoleEOL("cVlcManage::stopProcess ");

        // qDebug() << "process error string:" << processAction->errorString();

        // processAction->waitForFinished();

        disconnect(processAction, SIGNAL(readyRead()), this, SLOT(SLOT_action_readyRead()));
        disconnect(processAction, SIGNAL(readyReadStandardOutput()), this, SLOT(SLOT_action_rightMessage()));
        disconnect(processAction, SIGNAL(readyReadStandardError()), this, SLOT(SLOT_action_wrongMessage()));
        disconnect(processAction, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(SLOT_action_finish(int, QProcess::ExitStatus)));

        processAction->close();
        delete processAction;
        processAction = nullptr;
    }
}
void cManage::SLOT_action_finish(int _exitCode, QProcess::ExitStatus _status)
{
    if (git_log_command) {
        QString _debug = "";
        for (int i = 0; i < answerAction.size(); i++)
            _debug += answerAction.at(i) + "\n";

        fprintf(fileLog, "%s", _debug.toStdString().c_str());
    }
    stopProcess();
}

void cManage::SLOT_action_readyRead()
{
    QByteArray strdata = processAction->readAll();
    answerAction += QString(strdata).split("\n");

    //    qDebug() << "readyRead" << strdata;
}

void cManage::SLOT_action_rightMessage()
{
    QByteArray strdata = processAction->readAllStandardOutput();
    answerAction += QString(strdata).split("\n");

    //    qDebug() << "rightMessage" << strdata;
}

// Show wrong message
void cManage::SLOT_action_wrongMessage()
{
    QByteArray strdata = processAction->readAllStandardError();
    answerAction += QString(strdata).split("\n");

    //    qDebug() << "wrongMessage" << strdata;
}
