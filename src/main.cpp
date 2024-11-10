#include <QApplication>
#include <QFile>
#include <QGuiApplication>
#include <QIcon>
#include <QScreen>
#include <QTextStream>
#include <QtCore/QCoreApplication>

#include "tcnStyle.h"

#include "define.h"
#include "globalVar.h"

#include "init/initWin.h"
#include "settings/settingsWin.h"

#include "hmi/console.h"
#include "hmi/mainWin.h"

#if defined(_WIN32) || defined(_WIN64)

#include <windows.h>
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#endif

void create_cqtdeploy_file();

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    app.setWindowIcon(QIcon(_D_ICON_PATH));

    create_cqtdeploy_file();

    c_globalVar = new cGlobalVar;
    c_tools = new cTools;

    c_settings = new cSettings;

    bool _settings_ok = c_settings->_read_App_Parametre_();

    c_tcnStyle = new cTcnStyle(&app, app_color_profile, app_font_size);
    c_tcnStyle->load_tcnStyle();

    if (not _settings_ok or default_dev_branch.size() < 3) {

        cSettingsWin* settingsWin = new cSettingsWin;
        settingsWin->exec();
        int _exit_settings = settingsWin->get_exitValue();

        qDebug() << "_exit_settings" << _exit_settings;
    }

    cInitWin* initWin = new cInitWin;
    initWin->exec();
    int _exit_init = initWin->get_exitValue();

    qDebug() << "_exit_init" << _exit_init;

    c_manage = new cManage;

    if (app_show_console) {
        c_console = new cConsole();
        c_console->show();
    }

    cMainWin* mainWin = new cMainWin;

    mainWin->show();

    int _exit = app.exec();

    qDebug() << "exit";

    if (c_console != nullptr) {
        c_console->close();
        delete c_console;
    }
    if (c_manage != nullptr) {
        c_manage->stopManage();
        delete c_manage;
    }
    if (c_tools != nullptr) {
        delete c_tools;
    }
    if (c_globalVar != nullptr) {
        delete c_globalVar;
    }

    // app.destroyed();
    // app.deleteLater();
    // delete app;

    return _exit;
}

void create_cqtdeploy_file()
{

#if defined(_WIN32) || defined(_WIN64)

    QString filename_deploy = cMake_binaryPath + QString("/cqtWinDeploy.bat");
    QFile file_deploy(filename_deploy);

    if (file_deploy.exists())
        file_deploy.remove();

    if (file_deploy.open(QIODevice::ReadWrite)) {

        // "C:/Program Files/CQtDeployer/1.6/CQtDeployer.exe" -bin manageModBus.exe -qmake C:/Qt/6.7.1/mingw_64/bin/qmake.exe

        QTextStream stream(&file_deploy);
        stream << "\n";

        stream << QChar('"') << "C:/Program Files/CQtDeployer/1.6/CQtDeployer.exe" << QChar('"')
               << " -bin "
               << cMake_projectName << ".exe"
               << " -qmake "
               << cMake_qtLibPath
               << "/bin/qmake.exe"
               << "\n";

        stream << "\n";
        stream << "pause\n";
        stream << "\n";

        //        file_deploy.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner | QFileDevice::ExeOwner);

        file_deploy.close();
    }

#else
    QString filename_desktop = cMake_binaryPath + QString("/") + cMake_projectName + QString(".desktop");
    QFile file_desktop(filename_desktop);

    if (file_desktop.exists())
        file_desktop.remove();

    //    #!/usr/bin/env xdg-open
    //    [Desktop Entry]
    //    Version=2022.3
    //    Exec=/home/tcousin//Bureau/0_qt_app/app_playVideo/playVideo.sh
    //    Icon=/home/tcousin//Bureau/0_qt_app/0_app_icon/tcnSystemIcon.png
    //    Name=playVideo
    //    GenericName=playVideo
    //    Comment=Develop QT Applications
    //    Encoding=UTF-8
    //    Terminal=false
    //    Type=Application
    //    Categories=Application;IDE;

    if (file_desktop.open(QIODevice::ReadWrite)) {

        QTextStream stream(&file_desktop);
        stream << "#!/usr/bin/env xdg-open\n";

        stream << "[Desktop Entry]\n";
        stream << "Version=2024.0\n";

        stream << "Exec=" << QDir::homePath() << "/Bureau/0_qt_app/app_" << cMake_projectName << "/" << cMake_projectName << ".sh\n";

        stream << "Icon=/home/tcousin/Bureau/0_qt_app/0_app_icon/tcnSystemIcon.png\n";

        stream << "Name=" << cMake_projectName << "\n";
        stream << "GenericName=" << cMake_projectName << "\n";

        stream << "Comment=Develop QT Applications\n"
               << "Encoding=UTF-8\n"
               << "Terminal=false\n"
               << "Type=Application\n"
               << "Categories=Application;IDE;\n";

        file_desktop.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner | QFileDevice::ExeOwner);

        file_desktop.close();
    }

    // cqtdeployer -bin playVideo -qmake ~/Qt/5.15.2/gcc_64/bin/qmake

    // #! /bin/sh.

    QString filename_deploy = cMake_binaryPath + QString("/cqtDeploy.sh");
    QFile file_deploy(filename_deploy);

    if (file_deploy.exists())
        file_deploy.remove();

    if (file_deploy.open(QIODevice::ReadWrite)) {

        QTextStream stream(&file_deploy);
        stream << "#!/bin/sh"
               << "\n";

        stream << "\n";

        stream << "rm -rf " << QDir::homePath() << "/Bureau/0_qt_app/app_" << cMake_projectName << "\n";

        stream << "\n";

        stream << "cqtdeployer -bin "
               << cMake_projectName
               << " -qmake "
               << cMake_qtLibPath
               << "/bin/qmake -targetDir "
               << QDir::homePath()
               << "/Bureau/0_qt_app/app_"
               << cMake_projectName
               << "\n";

        stream << "\n";

        stream << "cp " << filename_desktop << " " << QDir::homePath() << "/Bureau/0_qt_app/\n";

        file_deploy.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner | QFileDevice::ExeOwner);

        file_deploy.close();
    }
#endif
}
