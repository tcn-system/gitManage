#include "projetGitWin.h"

#include "setMessage.h"

cProjetGitWin::cProjetGitWin(QWidget* parent)
    : QWidget(parent)
{
    QVBoxLayout* main_layout = new QVBoxLayout;
    {
        group_gitProject = new QGroupBox;
        {
            group_gitProject->setVisible(false);

            QVBoxLayout* action_layout = new QVBoxLayout;
            {
                qpb_config = new QPushButton;
                qpb_config->setText("config");
                connect(qpb_config, SIGNAL(pressed()), this, SLOT(SLOT_qpb_config()));
                action_layout->addWidget(qpb_config);

                QGroupBox* group_branch = new QGroupBox;
                group_branch->setTitle(" branch ");
                {
                    QVBoxLayout* branch_layout = new QVBoxLayout;
                    {
                        qpb_branch_list = new QPushButton;
                        qpb_branch_list->setText(" list ( " + QString::number(current_gitProject.l_branch.size()) + " )");
                        connect(qpb_branch_list, SIGNAL(pressed()), this, SLOT(SLOT_qpb_branch_list()));
                        branch_layout->addWidget(qpb_branch_list);

                        qpb_branch_switch = new QPushButton;
                        qpb_branch_switch->setText(" switch ");
                        qpb_branch_switch->setVisible(false);
                        connect(qpb_branch_switch, SIGNAL(pressed()), this, SLOT(SLOT_qpb_branch_switch()));
                        branch_layout->addWidget(qpb_branch_switch);

                    }
                    group_branch->setLayout(branch_layout);
                }
                action_layout->addWidget(group_branch);

                QGroupBox* group_remote = new QGroupBox;
                group_remote->setTitle(" remote ");
                {
                    QVBoxLayout* remote_layout = new QVBoxLayout;
                    {
                        qpb_remote_list = new QPushButton;
                        qpb_remote_list->setText(" list ( " + QString::number(current_gitProject.l_remotePush.nameRemote.size() > 0) + " )");
                        connect(qpb_remote_list, SIGNAL(pressed()), this, SLOT(SLOT_qpb_remote_list()));
                        remote_layout->addWidget(qpb_remote_list);
                    }
                    group_remote->setLayout(remote_layout);
                }
                action_layout->addWidget(group_remote);

                qpb_status = new QPushButton("status");
                connect(qpb_status, SIGNAL(pressed()), this, SLOT(SLOT_qpb_status()));
                action_layout->addWidget(qpb_status);

                qpb_commit = new QPushButton("commit");
                qpb_commit->setEnabled(false);
                qpb_commit->setStyleSheet(c_tcnStyle->styleSheet_QPushButton(e_qpb_not_update));
                connect(qpb_commit, SIGNAL(pressed()), this, SLOT(SLOT_qpb_commit()));
                action_layout->addWidget(qpb_commit);

                action_layout->addStretch(1);

                qpb_push = new QPushButton("push ->");
                qpb_push->setEnabled(false);
                qpb_push->setVisible(false);
                connect(qpb_push, SIGNAL(pressed()), this, SLOT(SLOT_qpb_push()));
                action_layout->addWidget(qpb_push);

                qpb_pull = new QPushButton("pull <-");
                qpb_pull->setEnabled(false);
                qpb_pull->setVisible(false);
                connect(qpb_pull, SIGNAL(pressed()), this, SLOT(SLOT_qpb_pull()));
                action_layout->addWidget(qpb_pull);
            }
            group_gitProject->setLayout(action_layout);
        }
        main_layout->addWidget(group_gitProject);
    }

    this->setMinimumWidth(200);

    setLayout(main_layout);

    connect(c_manage, &cManage::SIGNAL_action_finish, this, &cProjetGitWin::SLOT_action_finish);
    connect(c_manage, &cManage::SIGNAL_action_busy, this, &cProjetGitWin::SLOT_action_busy);

    connect(c_manage, &cManage::SIGNAL_textEdit, this, &cProjetGitWin::SIGNAL_textEdit);

    c_manage->init();
}

cProjetGitWin::~cProjetGitWin()
{
    SLOT_closeEvent();
}
void cProjetGitWin::SLOT_closeEvent()
{
    if (c_manage != nullptr) {
        if (c_manage->isRunning())
            c_manage->stopManage();

        delete c_manage;
    }
}

bool cProjetGitWin::startManage()
{
    if (c_manage != nullptr) {
        if (not c_manage->isRunning()) {
            if (c_manage->startManage()) {
                group_gitProject->setEnabled(false);
                group_gitProject->setTitle(current_gitProject.nameProject);
                group_gitProject->setVisible(true);
            }
        }
    }

    return true;
}
bool cProjetGitWin::stopManage()
{
    group_gitProject->setVisible(false);

    if (c_manage != nullptr) {
        if (c_manage->isRunning())
            c_manage->stopManage();
    }
    return true;
}
bool cProjetGitWin::manageIsRunning()
{
    return c_manage->isRunning();
}

void cProjetGitWin::SLOT_qpb_config()
{
    emit SIGNAL_textEdit("BTN - config\n");

    if (c_manage->action(e_action_git_config))
        group_gitProject->setEnabled(false);
}
void cProjetGitWin::SLOT_qpb_branch_list()
{
    emit SIGNAL_textEdit("BTN - branch list\n");

    if (c_manage->action(e_action_git_branch_list))
        group_gitProject->setEnabled(false);
}
void cProjetGitWin::SLOT_qpb_branch_switch()
{
    emit SIGNAL_textEdit("BTN - branch switch\n");

    if (c_manage->action(e_action_git_branch_switch))
        group_gitProject->setEnabled(false);
}
void cProjetGitWin::SLOT_qpb_remote_list()
{
    emit SIGNAL_textEdit("BTN - remote list\n");

    if (c_manage->action(e_action_git_remote_list))
        group_gitProject->setEnabled(false);
}
void cProjetGitWin::SLOT_qpb_status()
{
    emit SIGNAL_textEdit("BTN - status\n");

    if (c_manage->action(e_action_git_status))
        group_gitProject->setEnabled(false);
}
void cProjetGitWin::SLOT_qpb_commit()
{
    emit SIGNAL_textEdit("BTN - commit\n");

    cSetMessage* setMessage = new cSetMessage;
    connect(setMessage, SIGNAL(SIGNAL_message(QString)), this, SLOT(SLOT_get_message_commit(QString)));
    setMessage->exec();
}
void cProjetGitWin::SLOT_get_message_commit(QString message)
{
    if (message.size() > 0) {
        if (c_manage->action_message(e_action_git_commit, message))
            group_gitProject->setEnabled(false);
    }
}

void cProjetGitWin::SLOT_qpb_push()
{
    emit SIGNAL_textEdit("BTN - push\n");

    if (c_manage->action(e_action_git_push))
        group_gitProject->setEnabled(false);
}

void cProjetGitWin::SLOT_qpb_pull()
{
    emit SIGNAL_textEdit("BTN - pull\n");

    if (c_manage->action(e_action_git_pull))
        group_gitProject->setEnabled(false);
}

void cProjetGitWin::SLOT_action_finish(eActionStat _action)
{
    c_globalVar->debugInConsoleEOL("cMainWin::SLOT_action_finish " + QString::number(_action) + " " + QString::number(current_gitProject.is_up_to_date));

    qpb_branch_list->setText(" list ( " + QString::number(current_gitProject.l_branch.size()) + " )");

    if(current_gitProject.l_branch.at(current_gitProject.idx_branch_in_process).nameBranch != default_dev_branch)
        qpb_branch_switch->setVisible(true);
    else
        qpb_branch_switch->setVisible(false);


    qpb_remote_list->setText(" list ( " + QString::number(current_gitProject.l_remotePush.nameRemote.size() > 0) + " )");

    if (current_gitProject.is_up_to_date == true) // commit
    {
        qpb_commit->setStyleSheet(c_tcnStyle->styleSheet_QPushButton(e_qpb_uncheck));
        qpb_commit->setEnabled(false);
    } else {
        qpb_commit->setStyleSheet(c_tcnStyle->styleSheet_QPushButton(e_qpb_not_update));
        qpb_commit->setEnabled(true);
    }

    if (current_gitProject.l_branch.at(current_gitProject.idx_branch_in_process).nameBranch.size() > 0
        and current_gitProject.l_remotePush.nameRemote.size() > 0) {
        qpb_push->setVisible(true);
        qpb_pull->setVisible(true);
    } else {
        qpb_push->setVisible(false);
        qpb_pull->setVisible(false);
    }

    if (current_gitProject.is_up_to_date == true /*and current_gitProject.nbre_commit > 0*/) // push
    {
        qpb_push->setEnabled(true);
        qpb_pull->setEnabled(true);
    } else {
        qpb_push->setEnabled(false);
        qpb_pull->setEnabled(false);
    }

    if (_action == e_action_init || _action == e_action_git_branch_list) {
        group_gitProject->setTitle(current_gitProject.nameProject + " :: " + current_gitProject.l_branch.at(current_gitProject.idx_branch_in_process).nameBranch);
    }

    group_gitProject->setEnabled(true);
}

void cProjetGitWin::SLOT_action_busy()
{
    group_gitProject->setEnabled(false);
}
