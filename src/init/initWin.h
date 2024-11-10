#ifndef INIT_WIN_H_
#define INIT_WIN_H_

#include <QComboBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMainWindow>
#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QSplitter>
#include <QVBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QScrollArea>
#include <QScrollBar>
#include <QCheckBox>

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>

#include <QCloseEvent>

#include "../globalVar.h"

#include "init.h"

class cInitWin : public QDialog {
    Q_OBJECT

public:
    cInitWin(QWidget* parent = nullptr);
    ~cInitWin();

    int get_exitValue() { return exit_Value; }

signals:
    void SIGNAL_close_event();


public slots:
    void SLOT_closeEvent();

    void SLOT_line_edit(QString _string);

    void SLOT_init_finish();

protected:
    void closeEvent(QCloseEvent* e) override;

private:

    int exit_Value;

    QLineEdit* lineEdit;

    // management
    cInit* c_init;

};

#endif // INIT_WIN_H_
