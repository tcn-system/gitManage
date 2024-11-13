#include "globalVar.h"

#include <QScreen>

#include "define.h"

cGlobalVar::cGlobalVar()
{
    fileManager = new cFileManager(QDir::homePath() + _D_PROJET_PATH_FILE);
    fileManager->verifyAllDirCreate();

    QList<QScreen *>    l_screen = QApplication::screens();
    list_screen.clear();
    for(int i = 0;i < l_screen.size();i++)
    {
        qDebug() << "screen" << QString::number(i) << " " << l_screen.at(i)->size();
        list_screen.push_back(l_screen.at(i)->geometry());
    }
    sizescreen = QGuiApplication::primaryScreen()->geometry();

    app_color_profile = e_profile_choose_standard;
    app_show_console = false;
    app_font_size = 12;
    git_log_command = false;

    _listFolderSearch.clear();

    _exeptDir.clear();
    s_folderRead.init();

    l_gitProject.clear();
    current_gitProject.init();
}
cGlobalVar::~cGlobalVar()
{
    if (fileManager != nullptr)
        delete fileManager;
}

void cGlobalVar::debugInConsole(QString str)
{
    if (app_show_console)
        _debugInConsole.push_back(str);
}

void cGlobalVar::debugInConsoleEOL(QString str)
{
    if (app_show_console)
        _debugInConsole.push_back(str + "\r\n");
}

cGlobalVar* c_globalVar;
cTools* c_tools;
cSettings* c_settings;

// global
QList<QRect> list_screen;
QRect sizescreen;
eProfileChoose app_color_profile;
bool app_show_console;
int app_font_size;
bool git_log_command;

// management
cManage* c_manage;

QList<sGitProject> l_gitProject;
sGitProject current_gitProject;

QString default_dev_branch;
