#include "paraWidget.h"

#include "../globalVar.h"

cParaWidget_x2::cParaWidget_x2(QWidget* _label, QWidget* _parametre, eAlignWidget e_align, QWidget* parent)
    : QWidget(parent)
{

    QFrame* _frame = new QFrame;

    QString _style_qframe = "";
    QString _style_qlabel = "";

    _style_qframe += "QFrame {";
    _style_qframe += "background-color: " + c_tcnStyle->_to_rgba(c_tcnStyle->_c_tcn_light_blue) + ";";
    _style_qframe += "border: 2px solid;";
    _style_qframe += "border-color: " + c_tcnStyle->_to_rgba(c_tcnStyle->_c_tcn_black) + ";";
    _style_qframe += "color: " + c_tcnStyle->_to_rgba(c_tcnStyle->_c_tcn_black) + ";";
    _style_qframe += "border-radius: 5px;";
    _style_qframe += "}\n";

    _style_qlabel += "QLabel {";
    _style_qlabel += "background-color: " + c_tcnStyle->_to_rgba(c_tcnStyle->_c_tcn_light_blue) + ";";
    //    _style_qlabel += "border: 0px solid;";
    _style_qlabel += "border-color: " + c_tcnStyle->_to_rgba(c_tcnStyle->_c_tcn_light_blue) + ";";
    _style_qlabel += "color: " + c_tcnStyle->_to_rgba(c_tcnStyle->_c_tcn_black) + ";";
    //    _style_qlabel += "border-radius: 5px;";
    _style_qlabel += "}\n";

    _frame->setStyleSheet(_style_qframe);

    _label->setStyleSheet(_style_qlabel);

    _frame->setContentsMargins(0, 0, 0, 0);

    if (e_align == e_align_horizontal) {
        QHBoxLayout* _Layout = new QHBoxLayout;

        _Layout->addStretch(1);
        _Layout->addWidget(_label);
        _Layout->addStretch(1);
        _Layout->addWidget(_parametre);
        _Layout->addStretch(1);

        _Layout->setSpacing(0);
        _Layout->setContentsMargins(0, 0, 0, 0);

        _frame->setLayout(_Layout);
    }
    else {
        QVBoxLayout* _Layout = new QVBoxLayout;

        _Layout->addStretch(1);
        _Layout->addWidget(_label);
        _Layout->addStretch(1);
        _Layout->addWidget(_parametre);
        _Layout->addStretch(1);

        _Layout->setSpacing(0);
        _Layout->setContentsMargins(0, 0, 0, 0);

        _frame->setLayout(_Layout);
    }

    _frame->setFrameStyle(QFrame::Box | QFrame::Sunken);
    //_frame->setMinimumHeight(_parametre->height());

    QHBoxLayout* frame_layout = new QHBoxLayout;

    frame_layout->addWidget(_frame);

    // _layout->setSpacing(0);
    // _layout->setContentsMargins(0, 0, 0, 0);

    //this->setMinimumHeight(_parametre->height());

    setLayout(frame_layout);
}

cParaWidget_x2::~cParaWidget_x2()
{
}


cParaWidget_x4::cParaWidget_x4(QWidget* _label_1, QWidget* _parametre_1, QWidget* _label_2, QWidget* _parametre_2, eAlignWidget e_align, QWidget* parent)
    : QWidget(parent)
{

    QFrame* _frame = new QFrame;

    QString _style_qframe = "";
    QString _style_qlabel = "";

    _style_qframe += "QFrame {";
    _style_qframe += "background-color: " + c_tcnStyle->_to_rgba(c_tcnStyle->_c_tcn_light_blue) + ";";
    _style_qframe += "border: 2px solid;";
    _style_qframe += "border-color: " + c_tcnStyle->_to_rgba(c_tcnStyle->_c_tcn_black) + ";";
    _style_qframe += "color: " + c_tcnStyle->_to_rgba(c_tcnStyle->_c_tcn_black) + ";";
    _style_qframe += "border-radius: 5px;";
    _style_qframe += "}\n";

    _style_qlabel += "QLabel {";
    _style_qlabel += "background-color: " + c_tcnStyle->_to_rgba(c_tcnStyle->_c_tcn_light_blue) + ";";
    //    _style_qlabel += "border: 0px solid;";
    _style_qlabel += "border-color: " + c_tcnStyle->_to_rgba(c_tcnStyle->_c_tcn_light_blue) + ";";
    _style_qlabel += "color: " + c_tcnStyle->_to_rgba(c_tcnStyle->_c_tcn_black) + ";";
    //    _style_qlabel += "border-radius: 5px;";
    _style_qlabel += "}\n";

    _frame->setStyleSheet(_style_qframe);

    _label_1->setStyleSheet(_style_qlabel);
    _label_2->setStyleSheet(_style_qlabel);

    _frame->setContentsMargins(0, 0, 0, 0);

    if (e_align == e_align_horizontal) {

        QHBoxLayout* _Layout = new QHBoxLayout;

        _Layout->addStretch(1);
        _Layout->addWidget(_label_1);
        _Layout->addStretch(1);
        _Layout->addWidget(_parametre_1);
        _Layout->addStretch(1);
        _Layout->addWidget(_label_2);
        _Layout->addStretch(1);
        _Layout->addWidget(_parametre_2);
        _Layout->addStretch(1);

        _Layout->setSpacing(0);
        _Layout->setContentsMargins(0, 0, 0, 0);

        _frame->setLayout(_Layout);
    }
    else {

        QVBoxLayout* _Layout = new QVBoxLayout;

        _Layout->addStretch(1);
        _Layout->addWidget(_label_1);
        _Layout->addStretch(1);
        _Layout->addWidget(_parametre_1);
        _Layout->addStretch(1);
        _Layout->addWidget(_label_2);
        _Layout->addStretch(1);
        _Layout->addWidget(_parametre_2);
        _Layout->addStretch(1);

        _Layout->setSpacing(0);
        _Layout->setContentsMargins(0, 0, 0, 0);

        _frame->setLayout(_Layout);
    }

    _frame->setFrameStyle(QFrame::Box | QFrame::Sunken);

    QHBoxLayout* frame_layout = new QHBoxLayout;

    frame_layout->addWidget(_frame);

    // _layout->setSpacing(0);
    // _layout->setContentsMargins(0, 0, 0, 0);

    setLayout(frame_layout);
}

cParaWidget_x4::~cParaWidget_x4()
{
}
