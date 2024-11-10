#ifndef GLOBAL_VAR_H_
#define GLOBAL_VAR_H_

#include <QString>
#include <QVector>

#include "tcnStyle.h"

#include "define.h"
#include "struct.h"

#include "fileManager.h"
#include "tools.h"

#include "settings/settings.h"

#include "manage/manage.h"

class cGlobalVar {

public:
    cGlobalVar();
    ~cGlobalVar();

    cFileManager* fileManager = nullptr;

    QVector<QString> _debugInConsole;
    void debugInConsole(QString str);
    void debugInConsoleEOL(QString str);

    QStringList _listFolderSearch;

    QStringList _exeptDir;
    sFolder s_folderRead;

private:
};

extern cGlobalVar* c_globalVar;
extern cTools* c_tools;
extern cSettings* c_settings;

// global
extern QList<QRect> list_screen;
extern QRect sizescreen;

extern eProfileChoose app_color_profile;
extern bool app_show_console;
extern int app_font_size;
extern bool git_log_command;

// management
extern cManage* c_manage;

extern QList<sGitProject> l_gitProject;
extern sGitProject current_gitProject;

extern QString default_dev_branch;

#endif // GLOBAL_VAR_H_
