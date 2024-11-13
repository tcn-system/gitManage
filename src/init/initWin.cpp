#include "initWin.h"

#include <QScreen>

#include "../globalVar.h"

cInitWin::cInitWin(QWidget* parent)
    : QDialog(parent)
{
    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    this->setWindowTitle(cMake_projectName + QString(" - page::init - ") + cMake_projectVersion + " qt" + cMake_qtVersion + " - tcn-system.com");
    this->setWindowIcon(QIcon(_D_ICON_PATH));

    QVBoxLayout* init_layout = new QVBoxLayout;
    {
        QLabel* image_label = new QLabel;
        image_label->setPixmap(QPixmap(_D_ICON_PATH));

        lineEdit = new QLineEdit;

        init_layout->addWidget(image_label);
        init_layout->addWidget(lineEdit);
    }

    setLayout(init_layout);


//    double _resize = 0.7;
//    this->resize(sizescreen.width() * _resize, sizescreen.height() * _resize);

    exit_Value = 0;

    c_init = new cInit;
    connect(c_init, &cInit::SIGNAL_init_finish , this , &cInitWin::SLOT_init_finish);
    connect(c_init, &cInit::SIGNAL_line_edit , this , &cInitWin::SLOT_line_edit);

    c_init->init();

    lineEdit->setText("Init Projet");
}

cInitWin::~cInitWin()
{
    SLOT_closeEvent();
}
void cInitWin::closeEvent(QCloseEvent* e)
{
    qDebug() << "cInitWin::closeEvent" << e;

    SLOT_closeEvent();

    e->accept();
}
void cInitWin::SLOT_closeEvent()
{
    if(c_init != nullptr)
    {
        delete c_init;
    }
}

void cInitWin::SLOT_line_edit(QString _string)
{
    lineEdit->setText(_string);
}

void cInitWin::SLOT_init_finish()
{
    exit_Value = 3;
    close();
}

