#include "settingsWin.h"

#include "../widgets/stringListWidget.h"

cSettingsWin::cSettingsWin(QWidget* parent)
    : QDialog(parent)
{
    // this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    this->setWindowTitle(cMake_projectName + QString(" - page::settings - ") + cMake_projectVersion + " qt" + cMake_qtVersion + " - tcn-system.com");
    this->setWindowIcon(QIcon(_D_ICON_PATH));

    QHBoxLayout* main_layout = new QHBoxLayout;
    {

        QVBoxLayout* init_layout = new QVBoxLayout;
        {
            QLabel* image_label = new QLabel;
            image_label->setPixmap(QPixmap(_D_ICON_PATH));

            lineEdit = new QLineEdit;

            init_layout->addWidget(image_label);
            init_layout->addWidget(lineEdit);
        }
        main_layout->addLayout(init_layout);

        QVBoxLayout* settings_layout = new QVBoxLayout;
        {
            qcb_app_color_profile = new QComboBox;
            qcb_app_color_profile->addItem(" standart ");
            qcb_app_color_profile->addItem(" dark ");
            qcb_app_color_profile->setCurrentIndex(app_color_profile);
            connect(qcb_app_color_profile, SIGNAL(currentIndexChanged(int)), this, SLOT(SLOT_qcb_app_color_profile_currentIndexChanged(int)));
            pw_app_color_profile = new cParaWidget(new QLabel("App color profile"), qcb_app_color_profile);
            settings_layout->addWidget(pw_app_color_profile);

            qcb_app_show_console = new QComboBox;
            qcb_app_show_console->addItem(" OFF ");
            qcb_app_show_console->addItem(" ON  ");
            qcb_app_show_console->setCurrentIndex(app_show_console);
            connect(qcb_app_show_console, SIGNAL(currentIndexChanged(int)), this, SLOT(SLOT_qcb_app_show_console_currentIndexChanged(int)));
            pw_app_show_console = new cParaWidget(new QLabel("App show console"), qcb_app_show_console);
            settings_layout->addWidget(pw_app_show_console);

            qsb_app_font_size = new QSpinBox;
            qsb_app_font_size->setValue(app_font_size);
            qsb_app_font_size->setRange(10, 16);
            connect(qsb_app_font_size, SIGNAL(valueChanged(int)), this, SLOT(SLOT_qsb_app_font_size_valueChanged(int)));
            pw_app_font_size = new cParaWidget(new QLabel("App font size"), qsb_app_font_size);
            settings_layout->addWidget(pw_app_font_size);

            cStringListWdgt* stringList_exeptDir = new cStringListWdgt(&c_globalVar->_exeptDir, QString("_exeptDir"));
            settings_layout->addWidget(stringList_exeptDir);

            cStringListWdgt* stringList_listFolderSearch = new cStringListWdgt(&c_globalVar->_listFolderSearch, QString("_listFolderSearch"));
            settings_layout->addWidget(stringList_listFolderSearch);

            qle_default_dev_branch = new QLineEdit;
            qle_default_dev_branch->setText(default_dev_branch);
            connect(qle_default_dev_branch, SIGNAL(textChanged(QString)), this, SLOT(SLOT_qle_default_dev_branch_valueChanged(QString)));
            pw_default_dev_branch = new cParaWidget(new QLabel("Default dev branch"), qle_default_dev_branch);
            settings_layout->addWidget(pw_default_dev_branch);

            qcb_git_log_command = new QComboBox;
            qcb_git_log_command->addItem(" OFF ");
            qcb_git_log_command->addItem(" ON  ");
            qcb_git_log_command->setCurrentIndex(git_log_command);
            connect(qcb_git_log_command, SIGNAL(currentIndexChanged(int)), this, SLOT(SLOT_qcb_git_log_command_currentIndexChanged(int)));
            pw_git_log_command = new cParaWidget(new QLabel("git log command"), qcb_git_log_command);
            settings_layout->addWidget(pw_git_log_command);

            settings_layout->addStretch(1);

            qpb_ok = new QPushButton(" OK ");
            connect(qpb_ok, SIGNAL(pressed()), this, SLOT(SLOT_qpb_ok()));

            settings_layout->addWidget(qpb_ok);
        }
        main_layout->addLayout(settings_layout);
    }

    setLayout(main_layout);

    i_exit_Value = 0;

    c_settings = new cSettings;
    connect(c_settings, &cSettings::SIGNAL_settings_finish, this, &cSettingsWin::SLOT_settings_finish);

    c_settings->init();

    lineEdit->setText("Settings Projet");
}

cSettingsWin::~cSettingsWin()
{
    qDebug() << "cSettingsWin::~cSettingsWin";

    SLOT_closeEvent();
}
void cSettingsWin::closeEvent(QCloseEvent* e)
{
    qDebug() << "cSettingsWin::closeEvent" << e;

    SLOT_closeEvent();

    i_exit_Value = 1;
    e->accept();
}
void cSettingsWin::SLOT_closeEvent()
{
    if (c_settings != nullptr) {
        delete c_settings;
    }
}

void cSettingsWin::SLOT_qcb_app_color_profile_currentIndexChanged(int _index)
{
    app_color_profile = (eProfileChoose)_index;
}
void cSettingsWin::SLOT_qcb_app_show_console_currentIndexChanged(int _index)
{
    app_show_console = (bool)_index;
}
void cSettingsWin::SLOT_qsb_app_font_size_valueChanged(int _value)
{
    app_font_size = _value;
}
void cSettingsWin::SLOT_qle_default_dev_branch_valueChanged(QString _string)
{
    default_dev_branch = _string;
}
void cSettingsWin::SLOT_qcb_git_log_command_currentIndexChanged(int _index)
{
    git_log_command = (bool)_index;
}

void cSettingsWin::SLOT_qpb_ok()
{
    i_exit_Value = 2;

    c_settings->_write_App_Parametre_();

    close();
}

void cSettingsWin::SLOT_settings_finish()
{
    i_exit_Value = 3;

    close();
}
