#include "pushBtn.h"

#include "../globalVar.h"

cPushBtn::cPushBtn(sGitProject _gitProject , QWidget *parent) :
    QLabel(parent)
{

    QString _color;
    int _col = 2;

    switch(_col)
    {
    case 0:  _color = "rgb(255,0,0)";       break;
    case 1:  _color = "rgb(0,255,0)";       break;
    case 2:  _color = "rgb(0,0,255)";       break;
    case 3:  _color = "rgb(127,127,127)";   break;
    }

    QString _style = "";

    _style += "QLabel {";
    _style += "background-color: " + c_tcnStyle->_to_rgba(c_tcnStyle->_profile_color[e_profile_background]) + ";";
    _style += "border: 4px solid " + c_tcnStyle->_to_rgba(c_tcnStyle->_profile_color[e_profile_border]) + ";";
    _style += "color: " + c_tcnStyle->_to_rgba(c_tcnStyle->_profile_color[e_profile_text]) + ";";
    _style += "border-radius: 10px;";
    _style += "min-height: 2.0em;";
    _style += "margin: 2px 2px 2px 10px;";
    _style += "}\n";
    _style += "QLabel:hover {";
    _style += "background-color: " + c_tcnStyle->_to_rgba(c_tcnStyle->_c_tcn_orange) + ";";
    _style += "border: 4px solid " + c_tcnStyle->_to_rgba(c_tcnStyle->_c_tcn_blue) + ";";
    _style += "color: " + c_tcnStyle->_to_rgba(c_tcnStyle->_c_tcn_blue) + ";";
    _style += "}\n";


    setStyleSheet(_style);

    setText(  "<div style='color: " + _color + "'><center>"
            + _gitProject.nameProject
            + "</center></div>"
            + "<div style='color: black'><center>"
            + _gitProject.dirPath.path()
            + "</center></div>" );

    setMinimumHeight(100);
}

cPushBtn::~cPushBtn()
{
}

void cPushBtn::mousePressEvent(QMouseEvent *e)
{
    Q_UNUSED(e);


    emit clicked();
}
