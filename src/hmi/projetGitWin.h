#ifndef PROJET_GIT_WIN_H_
#define PROJET_GIT_WIN_H_

#include <QCheckBox>
#include <QComboBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QScrollBar>
#include <QSpinBox>
#include <QSplitter>
#include <QVBoxLayout>
#include <QWidget>

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>

#include "../globalVar.h"

#include "../widgets/paraWidget.h"

class cProjetGitWin : public QWidget {
    Q_OBJECT

public:
    cProjetGitWin(QWidget* parent = nullptr);
    ~cProjetGitWin();

    bool startManage();
    bool stopManage();
    bool manageIsRunning();

signals:

    void SIGNAL_textEdit(QString _text);

public slots:
    void SLOT_closeEvent();

    void SLOT_qpb_config();
    void SLOT_qpb_log();

    void SLOT_qpb_branch_list();
    void SLOT_qcb_branch_list_indexChange(int _index);
    void SLOT_qcb_branch_remote_list_indexChange(int _index);
    void SLOT_qpb_branch_switch();

    void SLOT_qpb_remote_list();

    void SLOT_qpb_status();
    void SLOT_qpb_commit();
    void SLOT_get_message_commit(QString message);

    void SLOT_qcb_push_from_indexChange(int _index);
    void SLOT_qcb_push_to_indexChange(int _index);
    void SLOT_qpb_push();

    void SLOT_qcb_pull_from_indexChange(int _index);
    void SLOT_qcb_pull_to_indexChange(int _index);
    void SLOT_qpb_pull();

    void SLOT_action_finish(eActionStat _action);
    void SLOT_action_busy();

private:
    // git current project
    QGroupBox* group_gitProject;

    // action git
    QPushButton* qpb_config;
    QPushButton* qpb_log;

    QPushButton* qpb_branch_list;
    QComboBox*   qcb_branch_list;
    cParaWidget_x2* pw_branch_list;
    QComboBox*   qcb_branch_remote_list;
    cParaWidget_x2* pw_branch_remote_list;
    QPushButton* qpb_branch_switch;

    QPushButton* qpb_remote_list;

    QPushButton* qpb_status;
    QPushButton* qpb_commit;

    // push
    QComboBox*   qcb_push_from;
    QComboBox*   qcb_push_to;
    cParaWidget_x4* pw_push;
    QPushButton* qpb_push;

    // pull
    QComboBox*   qcb_pull_from;
    QComboBox*   qcb_pull_to;
    cParaWidget_x4* pw_pull;
    QPushButton* qpb_pull;
};

#endif // PROJET_GIT_WIN_H_
