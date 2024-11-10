#include "setMessage.h"

#include "../globalVar.h"

cSetMessage::cSetMessage(QWidget* parent)
    : QDialog(parent)
{
    this->setWindowTitle(cMake_projectName + QString(" - page::message - ") + cMake_projectVersion + " qt" + cMake_qtVersion + " - tcn-system.com");
    this->setWindowIcon(QIcon(_D_ICON_PATH));

    QVBoxLayout* v_layout = new QVBoxLayout;
    {
        qte_textEdit = new QTextEdit;
        connect(qte_textEdit , SIGNAL(textChanged()) , this , SLOT(SLOT_qte_textEdit_textChange()));
        v_layout->addWidget(qte_textEdit);

        QHBoxLayout* btn_layout = new QHBoxLayout;
        {
            qpb_abort = new QPushButton("abort");
            connect(qpb_abort, SIGNAL( clicked() ), this, SLOT(SLOT_qpb_abort()));
            btn_layout->addWidget(qpb_abort);

            qpb_accept = new QPushButton("accept");
            connect(qpb_accept, SIGNAL(clicked()), this, SLOT(SLOT_qpb_accept()));
            btn_layout->addWidget(qpb_accept);
        }
        v_layout->addLayout(btn_layout);
    }

    setLayout(v_layout);

    double _resize = 0.5;
    this->resize(sizescreen.width() * _resize, sizescreen.height() * _resize);
}
cSetMessage::~cSetMessage()
{

}

void cSetMessage::SLOT_qte_textEdit_textChange()
{

}

void cSetMessage::SLOT_qpb_abort()
{
    done(0);
}
void cSetMessage::SLOT_qpb_accept()
{
    QString message = qte_textEdit->toPlainText();

    if(message.size() > 0)
    {
        emit SIGNAL_message(message);
         done(1);
    }
    else
        done(0);
}
