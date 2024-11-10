
#include "labelClickWidget.h"

#include "../globalVar.h"

cLabelClickWidget::cLabelClickWidget(QWidget *parent) :
    QLabel(parent)
{
    _stat = false;

    _styleSheet = "QLabel {";
    _styleSheet += "background-color: " + c_tcnStyle->_to_rgba(c_tcnStyle->_c_tcn_blue) + ";";
    _styleSheet += "}\n";

    //this->setText("UnCheck");
    this->setStyleSheet(_styleSheet);

    this->setMaximumWidth(30);
    this->setMaximumHeight(30);
}

cLabelClickWidget::~cLabelClickWidget()
{
}

void cLabelClickWidget::mousePressEvent(QMouseEvent *e)
{
    Q_UNUSED(e);

    if( _stat == true )
    {
        _styleSheet = "QLabel {";
        _styleSheet += "background-color: " + c_tcnStyle->_to_rgba(c_tcnStyle->_c_tcn_blue) + ";";
        _styleSheet += "}\n";

        //this->setText("UnCheck");
        this->setStyleSheet(_styleSheet);

        _stat = false;
    }
    else
    {
        _styleSheet = "QLabel {";
        _styleSheet += "background-color: " + c_tcnStyle->_to_rgba(c_tcnStyle->_c_tcn_dark_green) + ";";
        _styleSheet += "}\n";

        //this->setText("Check");
        this->setStyleSheet(_styleSheet);

        _stat = true;
    }

    emit clicked(_stat);
}
