#ifndef SETTINGS_WIN_H_
#define SETTINGS_WIN_H_

#include <QCheckBox>
#include <QComboBox>
#include <QDialog>
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
#include <QVBoxLayout>
#include <QWidget>

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>

#include <QCloseEvent>

#include "../globalVar.h"

#include "../widgets/paraWidget.h"

class cSettingsWin : public QDialog {
    Q_OBJECT

public:
    cSettingsWin(QWidget* parent = nullptr);
    ~cSettingsWin();

    int get_exitValue() { return i_exit_Value; }

signals:
    void SIGNAL_close_event();

public slots:
    void SLOT_closeEvent();

    void SLOT_qcb_app_color_profile_currentIndexChanged(int _index);
    void SLOT_qcb_app_show_console_currentIndexChanged(int _index);
    void SLOT_qsb_app_font_size_valueChanged(int _value);

    void SLOT_qle_default_dev_branch_valueChanged(QString _string);
    void SLOT_qcb_git_log_command_currentIndexChanged(int _index);

    void SLOT_qpb_ok();

    void SLOT_settings_finish();

protected:
    void closeEvent(QCloseEvent* e) override;

private:
    int i_exit_Value;

    QLineEdit* lineEdit;

    QComboBox* qcb_app_color_profile;
    cParaWidget* pw_app_color_profile;

    QComboBox* qcb_app_show_console;
    cParaWidget* pw_app_show_console;

    QSpinBox* qsb_app_font_size;
    cParaWidget* pw_app_font_size;

    QLineEdit* qle_default_dev_branch;
    cParaWidget* pw_default_dev_branch;

    QComboBox* qcb_git_log_command;
    cParaWidget* pw_git_log_command;

    QPushButton* qpb_ok;

    // management
    cSettings* c_settings;
};

#endif // SETTINGS_WIN_H_
