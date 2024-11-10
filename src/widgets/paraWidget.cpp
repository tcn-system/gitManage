#include "paraWidget.h"

#include "../globalVar.h"

cParaWidget::cParaWidget(QWidget* _label, QWidget* _parametre, eAlignWidget e_align, QWidget* parent)
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
    _style_qframe += "border-radius: 10px;";
    _style_qframe += "}\n";

    _style_qlabel += "QLabel {";
    _style_qlabel += "background-color: " + c_tcnStyle->_to_rgba(c_tcnStyle->_c_tcn_light_blue) + ";";
    //    _style_qlabel += "border: 1px solid;";
    _style_qlabel += "border-color: " + c_tcnStyle->_to_rgba(c_tcnStyle->_c_tcn_light_blue) + ";";
    _style_qlabel += "color: " + c_tcnStyle->_to_rgba(c_tcnStyle->_c_tcn_black) + ";";
    //    _style_qlabel += "border-radius: 10px;";
    _style_qlabel += "}\n";

    _frame->setStyleSheet(_style_qframe);
    _label->setStyleSheet(_style_qlabel);

    _frame->setContentsMargins(0, 0, 0, 0);

    if (e_align == e_align_horizontal) {
        QHBoxLayout* _Layout = new QHBoxLayout;

        _Layout->addWidget(_label);
        _Layout->addWidget(_parametre);

        _Layout->setSpacing(0);
        _Layout->setContentsMargins(0, 0, 0, 0);

        _frame->setLayout(_Layout);
    } else {
        QVBoxLayout* _Layout = new QVBoxLayout;
        _Layout->addWidget(_label);
        _Layout->addWidget(_parametre);

        _Layout->setSpacing(0);
        _Layout->setContentsMargins(0, 0, 0, 0);

        _frame->setLayout(_Layout);
    }
    _frame->setFrameStyle(QFrame::Box | QFrame::Sunken);

    QHBoxLayout* _layout = new QHBoxLayout;

    _layout->addWidget(_frame);

    // _layout->setSpacing(0);
    // _layout->setContentsMargins(0, 0, 0, 0);

    setLayout(_layout);
}

cParaWidget::~cParaWidget()
{
}
