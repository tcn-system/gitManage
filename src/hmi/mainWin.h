#ifndef MAIN_WIN_H_
#define MAIN_WIN_H_

#include <QCheckBox>
#include <QComboBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QScrollArea>
#include <QScrollBar>
#include <QSpinBox>
#include <QSplitter>
#include <QTextEdit>
#include <QVBoxLayout>

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>

#include <QCloseEvent>

#include "../globalVar.h"

#include "../settings/settingsWin.h"

#include "../readDir/readDirectory.h"
#include "projetGitWin.h"

class cMainWin : public QMainWindow {
    Q_OBJECT

public:
    cMainWin(QWidget* parent = nullptr);
    ~cMainWin();

signals:
    void SIGNAL_close_event();

public slots:
    void SLOT_closeEvent();

    void SLOT_readDirectory();
    void SLOT_readDirectory_finish();

    void SLOT_select_gitProject();

    void SLOT_textEdit(QString _text);

    void SLOT_qpb_settings();
    void SLOT_qpb_back();

protected:
    void closeEvent(QCloseEvent* e) override;

private:
    QSplitter* splitter;

    int idx_list_seach;

    // list git project
    QScrollArea* scrollArea;

    QGroupBox* group_gitListProject;

    // projet git
    cProjetGitWin* projetGitWin = nullptr;

    QPushButton* qpb_settings;
    QPushButton* qpb_back;

    QTextEdit* textEdit;

    void load_gitProject();


    bool verif_satus_git_project(sGitProject* _gitProject);
};

#endif // MAIN_WIN_H_
