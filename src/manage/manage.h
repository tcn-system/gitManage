#ifndef SNIFFER_RS485_H
#define SNIFFER_RS485_H

#include <QObject>
#include <QString>
#include <QWidget>

#include <QDebug>
#include <QProcess>
#include <QTimer>

#include "../define.h"
#include "../struct.h"

enum eManageStat {

    e_manage_stat_init,
    e_manage_stat_wait,

    /// gestion de la config
    e_manage_stat_git_list_config,

    /// gstion des logs
    e_manage_stat_git_list_log,

    /// gestion des branches
//    How to List Remote Branches in Git?
//        git branch -r . Lists all the remote branches.
//        git branch -r -v . Lists all the remote branches with the latest commit hash and commit message.
//        git ls-remote . Lists all the references in the remote repository, including the branches.
//        git remote show [remote_name ]. ...
//        git branch -a .
    e_manage_stat_git_list_branch,
    e_manage_stat_git_create_dev_branch,
    e_manage_stat_git_checkout_dev_branch,

    /// gestion des remote
    e_manage_stat_git_list_remote,

    /// gestion de la branche en cours
    e_manage_stat_git_status,

    e_manage_stat_git_add,
    e_manage_stat_git_commit,

    /// gestion d'une demande de push
    //       on est sur la branche dev
    //      verif commit ok de la branche dev
    //      passage sur la branche master ou main
    //      pull du master
    //      merge du master avec la dev
    //      push du master
    //      delete de la brance dev
    //      got to e_manage_stat_git_list_branch
    e_manage_stat_git_push,
    e_manage_stat_git_push___verif_commit_dev,
    e_manage_stat_git_push___checkout_dev_to_master,
    e_manage_stat_git_push___pull_master,
    e_manage_stat_git_push___merge_dev_to_master,
    e_manage_stat_git_push___push_master_to_remote,
    e_manage_stat_git_push___delete_dev,

    /// gestion d'une demande de pull
    //       on est sur la branche dev
    //      verif commit ok de la branche dev
    //      passage sur la branche master ou main
    //      pull du master
    //      passage sur la branche dev
    //      merge du master avec la dev
    e_manage_stat_git_pull,
    e_manage_stat_git_pull___verif_commit_dev,
    e_manage_stat_git_pull___checkout_dev_to_master,
    e_manage_stat_git_pull___pull_master,

    e_manage_stat_git___checkout_master_to_dev,
    e_manage_stat_git___merge_master_to_dev,


    /// gestion des erreurs
    e_manage_stat_errors,
};

enum eActionStat {

    e_action_none,

    e_action_init,

    e_action_git_config,
    e_action_git_log,

    e_action_git_branch_list,
    e_action_git_branch_switch,

    e_action_git_remote_list,

    e_action_git_commit,
    e_action_git_status,

    e_action_git_push,
    e_action_git_pull,

};

class cManage : public QWidget {
    Q_OBJECT

public:
    cManage(QWidget* qw_parent = nullptr);
    ~cManage();

    void init();
    bool startManage();
    bool stopManage();

    bool isRunning();

    bool action(eActionStat _action);
    bool action_message(eActionStat _action, QString _message);

signals:

    void SIGNAL_action_finish(eActionStat _action);
    void SIGNAL_action_busy();

    void SIGNAL_textEdit(QString _text);

protected:
public slots:
    void SLOT_timerTick();

    void SLOT_action_finish(int _exitCode, QProcess::ExitStatus _status);
    void SLOT_action_readyRead();
    void SLOT_action_rightMessage();
    void SLOT_action_wrongMessage();

private:
    QTimer* qt_timer = nullptr;

    int i_manage_tempo;
    int _time_out = 1000;
    eManageStat e_manage_stat;

    eActionStat e_manage_action;

    QProcess* processAction = nullptr;

    QStringList askAction;
    QString messageAction;
    bool startProcess();

    QStringList answerAction;
    void stopProcess();

    void show_answerAction();

    void manage_status();
    bool verify_name_current_branch();

    void load_branch();
    bool verif_branchs_integrity();
    bool verif_answer_switch_to_branch(QString _branch);
    bool verif_answer_delete_branch(QString _branch);

    bool verif_answer_push(QString _branch);
    bool verif_answer_merge(QString _branch_src , QString _branch_dst);
    bool verif_answer_pull(QString _branch);

    void load_remote();

    void startLogFile();
    void stopLogFile();
    FILE* fileLog;
};

#endif // BANC_TEST_H
