#include "settings.h"

#include "../globalVar.h"

cSettings::cSettings()
{
}
cSettings::~cSettings()
{
}

void cSettings::init()
{
    qDebug() << "cSettings::init";
}

bool cSettings::_read_App_Parametre_()
{
    QString fileIni = c_globalVar->fileManager->parameterDir().path() + "/app_parametres.ini";

    QFile _file(fileIni);

    if (_file.exists()) {

        QSettings _settings(fileIni, QSettings::IniFormat);

        app_color_profile = (eProfileChoose)_settings.value("generale/color_profile", 0).toInt();
        app_show_console = _settings.value("generale/show_console", 0).toBool();
        app_font_size = _settings.value("generale/font_size", 0).toInt();

        c_globalVar->_exeptDir = _settings.value("generale/_exeptDir").value<QStringList>();
        c_globalVar->_listFolderSearch = _settings.value("generale/_listFolderSearch").value<QStringList>();

        default_dev_branch = _settings.value("git/default_dev_branch").toString();
        git_log_command = _settings.value("git/git_log_command", 0).toBool();

        return true;
    }

    return false;
}
bool cSettings::_write_App_Parametre_(bool _first_write)
{
    QString fileIni = c_globalVar->fileManager->parameterDir().path() + "/app_parametres.ini";

    QSettings _settings(fileIni, QSettings::IniFormat);

    QFile _file(fileIni);

    if (_file.exists())
        _file.remove();

    _settings.beginGroup("generale");

    _settings.setValue("color_profile", app_color_profile);
    _settings.setValue("show_console", app_show_console);
    _settings.setValue("font_size", app_font_size);

    if (_first_write) {
        _settings.setValue("_exeptDir", _D_exeptDir);
        c_globalVar->_exeptDir = _D_exeptDir;
        _settings.setValue("_listFolderSearch", _D_listFolderSearch);
        c_globalVar->_listFolderSearch = _D_listFolderSearch;
    } else {
        _settings.setValue("_exeptDir", c_globalVar->_exeptDir);
        _settings.setValue("_listFolderSearch", c_globalVar->_listFolderSearch);
    }

    _settings.endGroup();

    _settings.beginGroup("git");

    _settings.setValue("default_dev_branch", default_dev_branch);
    _settings.setValue("git_log_command", git_log_command);

    _settings.endGroup();

    return true;
}
