#include "mainWin.h"

#include "console.h"
#include "pushBtn.h"
#include "setMessage.h"

cMainWin::cMainWin(QWidget* parent)
    : QMainWindow(parent)
{
    this->setWindowTitle(cMake_projectName + QString(" - page::main - ") + cMake_projectVersion + " qt" + cMake_qtVersion + " - tcn-system.com");
    this->setWindowIcon(QIcon(_D_ICON_PATH));

    splitter = new QSplitter(Qt::Orientation::Horizontal);

    // if (app_show_console) {
    //     c_console = new cConsole();
    //     splitter->addWidget(c_console);
    // }

    QVBoxLayout* left_splitter_layout = new QVBoxLayout;
    {
        // QScrollBar* scrollBarH = new QScrollBar;
        // QScrollBar* scrollBarV = new QScrollBar;

        scrollArea = new QScrollArea;

        scrollArea->setWidgetResizable(true);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        //scrollArea->setHorizontalScrollBar(scrollBarH);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        //scrollArea->setVerticalScrollBar(scrollBarV);


        group_gitListProject = new QGroupBox;
        group_gitListProject->setVisible(true);
        scrollArea->setVisible(true);

        group_gitListProject->setTitle(" git project ");
        scrollArea->setWidget(group_gitListProject);
        left_splitter_layout->addWidget(scrollArea);

        // left_splitter_layout->addStretch(20);

        projetGitWin = new cProjetGitWin;
        left_splitter_layout->addWidget(projetGitWin);

        qpb_settings = new QPushButton(" >> settings << ");
        qpb_settings->setVisible(false);
        connect(qpb_settings, SIGNAL(pressed()), this, SLOT(SLOT_qpb_settings()));
        left_splitter_layout->addWidget(qpb_settings);

        qpb_back = new QPushButton(" << back << ");
        qpb_back->setVisible(false);
        connect(qpb_back, SIGNAL(pressed()), this, SLOT(SLOT_qpb_back()));
        left_splitter_layout->addWidget(qpb_back);
    }

    QVBoxLayout* right_splitter_layout = new QVBoxLayout;
    {
        textEdit = new QTextEdit;
        textEdit->setText("");

        textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

        //textEdit->setAcceptRichText(true);
        textEdit->setReadOnly(true);
        //textEdit->setTextInteractionFlags(Qt::NoTextInteraction);
        textEdit->setAlignment(Qt::AlignTop);
        textEdit->setWordWrapMode(QTextOption::NoWrap);
        textEdit->setFrameStyle(QFrame::NoFrame);
        // textEdit->setMinimumSize(600, 380);
        textEdit->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);

        // textEdit->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored);
        // textEdit->setWidgetResizable(True);

        connect(projetGitWin, &cProjetGitWin::SIGNAL_textEdit, this, &cMainWin::SLOT_textEdit);

        right_splitter_layout->addWidget(textEdit);
        //        right_splitter_layout->addStretch(20);
    }

    QWidget* leftWidget = new QWidget;
    leftWidget->setLayout(left_splitter_layout);
    QWidget* rightWidget = new QWidget;
    rightWidget->setLayout(right_splitter_layout);

    splitter->addWidget(leftWidget);
    splitter->addWidget(rightWidget);

//    splitter->setCollapsible(0, false);
//    splitter->setCollapsible(1, false);

    setCentralWidget(splitter);

    // splitter->setSizes({ 1 , 99999 });
    // splitter->setSizes({ 99999 , 1 , 1 });

    QList<int> Sizes;
    Sizes.append(0.3 * sizescreen.width());
    Sizes.append(0.7 * sizescreen.width());
    splitter->setSizes(Sizes);

    double _resize = 0.85;
    this->resize(sizescreen.width() * _resize, sizescreen.height() * _resize);

    // if (l_screen.size() > 1)
    //     this->move(list_screen.at(1).x(), list_screen.at(1).y());

    connect(this, &cMainWin::SIGNAL_close_event, projetGitWin, &cProjetGitWin::SLOT_closeEvent);

    c_globalVar->debugInConsoleEOL("Start Projet");

    load_gitProject();
}

cMainWin::~cMainWin()
{
    SLOT_closeEvent();
}
void cMainWin::closeEvent(QCloseEvent* e)
{
    qDebug() << "cMainWin::closeEvent" << e;

    SLOT_closeEvent();

    e->accept();
}
void cMainWin::SLOT_closeEvent()
{
    emit SIGNAL_close_event();
}

void cMainWin::SLOT_readDirectory()
{
    QString _srcPath = "";

    if (idx_list_seach < c_globalVar->_listFolderSearch.size()) {
        _srcPath = c_globalVar->_listFolderSearch.at(idx_list_seach);

        c_globalVar->debugInConsoleEOL("search Folder: " + _srcPath);

        cReadDirectory* readFolder = new cReadDirectory;
        connect(readFolder, &cReadDirectory::finished, this, &cMainWin::SLOT_readDirectory_finish);
        readFolder->setPath(_srcPath, true);
        readFolder->setFolder(&c_globalVar->s_folderRead);
        readFolder->start();

        idx_list_seach++;
    }
}
void cMainWin::SLOT_readDirectory_finish()
{
    QList<cReadDirectory*> _list_read = this->findChildren<cReadDirectory*>();
    foreach (cReadDirectory* _read, _list_read) {
        _read->read_exit();
        delete _read;
    }

    for (int i = 0; i < c_globalVar->s_folderRead.listDir.size(); i++) {

        QString _pathGit = c_globalVar->s_folderRead.listDir.at(i).path_full;
        QStringList l_pathSplit = _pathGit.split("/");

        if (l_pathSplit.size() > 0) {
            if (not l_pathSplit.at(l_pathSplit.size() - 1).compare(".git")) {
                sGitProject _git;

                _git.init();

                QString path = "";
                for (int i = 0; i < l_pathSplit.size() - 1; i++) {
                    if (i > 0)
                        path += "/";
                    path += l_pathSplit.at(i);
                }

                _git.dirPath = QDir(path);
                _git.nameProject = l_pathSplit.at(l_pathSplit.size() - 2);

                l_gitProject.push_back(_git);
            }
        }
    }

    if (idx_list_seach < c_globalVar->_listFolderSearch.size()) {
        SLOT_readDirectory();
        return;
    }

    load_gitProject();
}

void cMainWin::load_gitProject()
{
    QList<cPushBtn*> _list_push = this->findChildren<cPushBtn*>();
    foreach (cPushBtn* _push, _list_push) {
        _push->deleteLater();
        delete _push;
    }

    QLayout* _layout = group_gitListProject->layout();

    if (_layout != nullptr) {
        _layout->deleteLater();

        delete _layout;
    }
    // if(scrollArea != nullptr)
    // {
    //     scrollArea->deleteLater();

    //     delete scrollArea;
    // }

    qpb_back->setVisible(false);
    qpb_settings->setVisible(true);

    if (l_gitProject.size() > 0) {
        group_gitListProject->setVisible(true);
        scrollArea->setVisible(true);

        QVBoxLayout* _layout = new QVBoxLayout;
        for (int i = 0; i < l_gitProject.size(); i++) {

            verif_satus_git_project((sGitProject*) &l_gitProject.at(i));

            cPushBtn* _push = new cPushBtn(l_gitProject.at(i));

            _push->setProperty("id_list", i + 1);

            connect(_push, SIGNAL(clicked()), this, SLOT(SLOT_select_gitProject()));

            _layout->addWidget(_push);
        }

        group_gitListProject->setLayout(_layout);

        scrollArea->setMinimumWidth(group_gitListProject->width());
    }
}

void cMainWin::SLOT_select_gitProject()
{
    cPushBtn* _push = qobject_cast<cPushBtn*>(sender());

    int id_project = _push->property("id_list").toInt();
    if (id_project > 0 and id_project <= l_gitProject.size()) {
        current_gitProject = l_gitProject[id_project - 1];
        qDebug() << "SLOT_select_gitProject " << current_gitProject.nameProject;

        group_gitListProject->setVisible(false);
        scrollArea->setVisible(false);

        textEdit->setText("");

        projetGitWin->startManage();

        qpb_back->setVisible(true);
        qpb_settings->setVisible(false);
    }
}

void cMainWin::SLOT_qpb_settings()
{
    cSettingsWin* c_settingsWin = new cSettingsWin;
    c_settingsWin->show();
}

void cMainWin::SLOT_qpb_back()
{
    if (projetGitWin->manageIsRunning()) {
        projetGitWin->stopManage();

        // idx_list_seach = 0;
        // l_gitProject.clear();

        // SLOT_readDirectory();

        load_gitProject();
    }
}

void cMainWin::SLOT_textEdit(QString _text)
{
    QString _text_previous = textEdit->toPlainText();
    _text_previous += _text;
    textEdit->setText(_text_previous);

    textEdit->verticalScrollBar()->setValue(textEdit->verticalScrollBar()->maximum());
}


bool cMainWin::verif_satus_git_project(sGitProject *_gitProject)
{
    bool _up_to_date = false;

    // LANG=en_US
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.insert("LANG", "en_US");

    QProcess* processStatus = new QProcess;
    processStatus->setWorkingDirectory(_gitProject->dirPath.path());
    processStatus->setProcessEnvironment(env);
    processStatus->setProgram("git");
    processStatus->setArguments(QStringList() << "status");

    processStatus->start();
    processStatus->waitForFinished();

    QByteArray strdata = processStatus->readAll();
    QStringList answerAction = QString(strdata).split("\n");

    processStatus->kill();

    delete processStatus;

    //qDebug()<< "verif_satus_git_project" << answerAction;

    _gitProject->is_up_to_date = false;
    _gitProject->nbre_commit = -1;

    for (int i = 0; i < answerAction.size(); i++) {

        QString _ligne = answerAction.at(i);

        if (_ligne.contains("Your branch is ahead")
            || _ligne.contains("Your branch is up to date"))
        {
            _gitProject->nbre_commit = 1;
        }

        if (_ligne.contains("nothing to commit"))
        {
            _gitProject->is_up_to_date = true;

            _up_to_date = true;
        }
    }

    return _up_to_date;
}
