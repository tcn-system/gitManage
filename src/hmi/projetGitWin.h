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

    void SLOT_qpb_branch_list();
    void SLOT_qpb_branch_switch();

    void SLOT_qpb_remote_list();

    void SLOT_qpb_status();
    void SLOT_qpb_commit();
    void SLOT_get_message_commit(QString message);

    void SLOT_qpb_push();
    void SLOT_qpb_pull();

    void SLOT_action_finish(eActionStat _action);
    void SLOT_action_busy();

private:
    // git current project
    QGroupBox* group_gitProject;

    // action git
    QPushButton* qpb_config;

    QPushButton* qpb_branch_list;
    QPushButton* qpb_branch_switch;

    QPushButton* qpb_remote_list;

    QPushButton* qpb_status;
    QPushButton* qpb_commit;

    QPushButton* qpb_push;
    QPushButton* qpb_pull;
};

#endif // PROJET_GIT_WIN_H_
