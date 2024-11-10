#include "tcnStyle.h"

#include "define.h"

cTcnStyle* c_tcnStyle;

cTcnStyle::cTcnStyle(QApplication* _app, eProfileChoose _choose_profile, int _app_font_size)
{
    app = _app;

    _f_font_size = _app_font_size;
    _f_font_family = "Arial";

    _c__white = QColor(255, 255, 255, 255);
    _c__black = QColor(0, 0, 0, 255);
    _c__green = QColor(0, 255, 0, 255);
    _c__red = QColor(255, 0, 0, 255);
    _c__blue = QColor(0, 0, 255, 255);

    _c_tcn_white = QColor(240, 240, 240, 255);
    _c_tcn_black = QColor(15, 15, 15, 255);
    _c_tcn_dark = QColor(50, 65, 75, 255);

    _c_tcn_blue = QColor(20, 140, 210, 255);
    _c_tcn_dark_blue = QColor(100, 100, 100, 255);
    _c_tcn_light_blue = QColor(173, 216, 230, 255);

    _c_tcn_grey = QColor(127, 127, 127, 255);
    _c_tcn_light_grey = QColor(200, 200, 200, 255);

    _c_tcn_green = QColor(0, 204, 102, 255);
    _c_tcn_dark_green = QColor(0, 150, 80, 255);
    _c_tcn_light_green = QColor(144, 238, 144, 255);

    _c_tcn_red = QColor(250, 50, 50, 255);
    _c_tcn_dark_red = QColor(200, 50, 50, 255);

    _c_tcn_orange = QColor(250, 100, 50, 255);
    _c_tcn_yellow = QColor(255, 255, 0, 255);
    _c_tcn_purple = QColor(233, 92, 176, 255);
    _c_tcn_purple_a127 = QColor(233, 92, 176, 127);

    _c_tcn_light_orange = QColor(255, 255, 224, 255);
    //    _c_tcn_orange = QColor(255, 165, 0, 255);

    for (int i = 0; i < 10; i++)
        _profile_color[i] = QColor(0, 0, 0, 0);

    switch (_choose_profile) {
        //    case e_profile_choose_none:

    case e_profile_choose_standard:
        // profile standard
        _profile_color[e_profile_background] = _c_tcn_white; // background
        _profile_color[e_profile_border] = _c_tcn_black; // border
        _profile_color[e_profile_text] = _c_tcn_black; // text
        break;
    case e_profile_choose_dark:
        // profile dark
        _profile_color[e_profile_background] = _c_tcn_black;
        _profile_color[e_profile_border] = _c_tcn_white;
        _profile_color[e_profile_text] = _c_tcn_white;
        break;
    }
}
cTcnStyle::~cTcnStyle()
{
}

QString cTcnStyle::styleSheet_QMainWindow()
{
    QString _style = "";

    _style += "QMainWindow {";
    _style += "background-color: " + _to_rgba(_profile_color[e_profile_background]) + ";";
    _style += "color: " + _to_rgba(_profile_color[e_profile_text]) + ";";
    _style += "font: " + QString::number(_f_font_size) + "pt \"" + _f_font_family + "\";";
    //_style += "margin: 6px 6px 6px 6px;";
    _style += "}\n";

    return _style;
}
QString cTcnStyle::styleSheet_QWidget()
{
    QString _style = "";

    _style += "QWidget {";
    _style += "background-color: " + _to_rgba(_profile_color[e_profile_background]) + ";";
    _style += "color: " + _to_rgba(_profile_color[e_profile_text]) + ";";
    _style += "font: " + QString::number(_f_font_size) + "pt \"" + _f_font_family + "\";";
    //    _style += "padding: 2px 2px 2px 2px;";
    //    _style += "margin: 2px 2px 2px 2px;";
    _style += "}\n";

    return _style;
}
QString cTcnStyle::styleSheet_QLineEdit()
{
    QString _style = "";

    _style += "QLineEdit {";
    _style += "background-color: " + _to_rgba(_profile_color[e_profile_background]) + ";";
    _style += "border: 4px solid " + _to_rgba(_profile_color[e_profile_border]) + ";";
    _style += "color: " + _to_rgba(_profile_color[e_profile_text]) + ";";
    _style += "border-radius: 10px;";
    _style += "min-height: 1.5em;";
    _style += "margin: 2px 2px 2px 10px;";
    //    _style += "padding: 2px 2px 2px 10px;";
    //    _style += "font-weight: 500;";
    _style += "}\n";

    return _style;
}
QString cTcnStyle::styleSheet_QSplitter()
{
    QString _style = "";

    _style += "QSplitter {";
    _style += "background-color: " + _to_rgba(_profile_color[e_profile_background]) + ";";
    _style += "border: 1px solid " + _to_rgba(_profile_color[e_profile_border]) + ";";
    _style += "color: " + _to_rgba(_profile_color[e_profile_text]) + ";";
    _style += "border-radius: 2px;";
    _style += "margin: 2px;";
    _style += "}\n";

    _style += "QSplitter:handle {";
    _style += "background-color: " + _to_rgba(_c_tcn_light_grey) + ";";
    _style += "border: 4px solid " + _to_rgba(_c_tcn_black) + ";";
    _style += "color: " + _to_rgba(_c_tcn_black) + ";";
    _style += "border-radius: 2px;";
    _style += "margin: 2px;";
    _style += "}\n";

    _style += "QSplitter:handle:hover {";
    _style += "background-color: " + _to_rgba(_c_tcn_white) + ";";
    _style += "border: 4px solid " + _to_rgba(_c_tcn_blue) + ";";
    _style += "color: " + _to_rgba(_c_tcn_black) + ";";
    _style += "border-radius: 2px;";
    _style += "margin: 2px;";
    _style += "}\n";

    _style += "QSplitter:handle:pressed {";
    _style += "background-color: " + _to_rgba(_c_tcn_blue) + ";";
    _style += "border: 4px solid " + _to_rgba(_c_tcn_black) + ";";
    _style += "color: " + _to_rgba(_c_tcn_black) + ";";
    _style += "border-radius: 2px;";
    _style += "margin: 2px;";
    _style += "}\n";

    return _style;
}
QString cTcnStyle::styleSheet_QGroupBox()
{
    QString _style = "";

    _style += "QGroupBox {";
    _style += "background-color: " + _to_rgba(_profile_color[e_profile_background]) + ";";
    _style += "border: 4px solid " + _to_rgba(_profile_color[e_profile_border]) + ";";
    _style += "color: " + _to_rgba(_profile_color[e_profile_text]) + ";";
    _style += "border-radius: 10px;";
    _style += "margin-top: 3px;";
    _style += "padding-top: 5px;";
    _style += "padding-bottom: 5px;";
    _style += "font-weight: 500;";
    _style += "}\n";

    _style += "QGroupBox:title {";
    //_style += "background-color: " + _to_rgba(_c_tcn_green) + ";";
    _style += "subcontrol-origin: margin;";
    _style += "left: 7px;";
    _style += "padding: 0px 5px 0px 5px;";
    _style += "}\n";

    return _style;
}

QString cTcnStyle::styleSheet_QPushButton(eQPb_check _eQpb)
{
    QString _style = "";

    _style += "QPushButton {";
    switch (_eQpb) {
    case e_qpb_not_update:
        _style += "background-color: " + _to_rgba(_c_tcn_orange) + ";";
        _style += "border: 4px solid " + _to_rgba(_c_tcn_black) + ";";
        _style += "color: " + _to_rgba(_c_tcn_black) + ";";
        break;
    case e_qpb_check:
        _style += "background-color: " + _to_rgba(_c_tcn_blue) + ";";
        _style += "border: 4px solid " + _to_rgba(_c_tcn_black) + ";";
        _style += "color: " + _to_rgba(_c_tcn_black) + ";";
        break;
    default:
        _style += "background-color: " + _to_rgba(_c_tcn_light_grey) + ";";
        _style += "border: 4px solid " + _to_rgba(_c_tcn_black) + ";";
        _style += "color: " + _to_rgba(_c_tcn_black) + ";";
        break;
    }

    _style += "border-radius: 10px;";
    _style += "min-height: 1.5em;";
    _style += "font-weight: 500;";
    _style += "margin: 2px 2px 2px 2px;";
    _style += "padding: 2px 2px 2px 2px;";
    _style += "}\n";

    _style += "QPushButton:disabled {";
    _style += "background-color: " + _to_rgba(_c_tcn_white) + ";";
    _style += "border: 4px solid " + _to_rgba(_c_tcn_light_grey) + ";";
    _style += "color: " + _to_rgba(_c_tcn_light_grey) + ";";
    _style += "}\n";

    _style += "QPushButton:hover {";
    _style += "background-color: " + _to_rgba(_c_tcn_white) + ";";
    _style += "border: 4px solid " + _to_rgba(_c_tcn_blue) + ";";
    _style += "color: " + _to_rgba(_c_tcn_blue) + ";";
    _style += "}\n";

    _style += "QPushButton:pressed {";
    _style += "background-color: " + _to_rgba(_c_tcn_blue) + ";";
    _style += "border: 4px solid " + _to_rgba(_c_tcn_white) + ";";
    _style += "color: " + _to_rgba(_c_tcn_white) + ";";
    _style += "}\n";

    return _style;
}
QString cTcnStyle::styleSheet_QScrollBar()
{
    QString _style = "";

    _style += "QScrollBar:horizontal {";
    _style += "background-color: " + _to_rgba(_c_tcn_light_grey) + ";";
    _style += "height: 16px;";
    _style += "margin: 2px 16px 2px 16px;";
    _style += "padding: 1px 1px 1px 1px;";
    _style += "border: 1px solid " + _to_rgba(_c_tcn_black) + ";";
    _style += " border-radius: 4px;";
    _style += " min-width: 8px;";
    _style += "}\n";

    _style += "QScrollBar:vertical {";
    _style += "background-color: " + _to_rgba(_c_tcn_light_grey) + ";";
    _style += "width: 16px;";
    _style += "margin: 16px 2px 16px 2px;";
    _style += "padding: 1px 1px 1px 1px;";
    _style += "border: 1px solid " + _to_rgba(_c_tcn_black) + ";";
    _style += " border-radius: 4px;";
    _style += " min-height: 8px;";
    _style += "}\n";

    _style += "QScrollBar:handle:horizontal {";
    _style += "background-color: " + _to_rgba(_c_tcn_blue) + ";";
    _style += "border: 1px solid " + _to_rgba(_c_tcn_black) + ";";
    _style += "border-radius: 4px;";
    _style += " min-width: 8px;";
    _style += "}\n";

    _style += "QScrollBar:handle:vertical {";
    _style += "background-color: " + _to_rgba(_c_tcn_blue) + ";";
    _style += "border: 1px solid " + _to_rgba(_c_tcn_black) + ";";
    _style += "border-radius: 4px;";
    _style += " min-height: 8px;";
    _style += "}\n";

    _style += "QScrollBar:handle:horizontal:hover {";
    _style += "background-color: " + _to_rgba(_c_tcn_white) + ";";
    _style += "border: 1px solid " + _to_rgba(_c_tcn_black) + ";";
    _style += "border-radius: 4px;";
    _style += " min-width: 8px;";
    _style += "}\n";

    _style += "QScrollBar:handle:vertical:hover {";
    _style += "background-color: " + _to_rgba(_c_tcn_white) + ";";
    _style += "border: 1px solid " + _to_rgba(_c_tcn_black) + ";";
    _style += "border-radius: 4px;";
    _style += " min-height: 8px;";
    _style += "}\n";

    _style += "QScrollBar:add-line:horizontal {     margin: 0px 0px 0px 0px;        border-image: url(\":/qss_icons/rc/right_arrow_disabled.png\");    width: 10px;    height: 10px;        subcontrol-position: right;        subcontrol-origin: margin;    }"
              "QScrollBar:add-line:horizontal:hover, QScrollBar::add-line:horizontal:on {        border-image: url(\":/qss_icons/rc/right_arrow.png\");    height: 10px;    width: 10px;        subcontrol-position: right;        subcontrol-origin: margin;    }"
              "QScrollBar:add-line:vertical {    margin: 3px 0px 3px 0px;        border-image: url(\":/qss_icons/rc/down_arrow_disabled.png\");    height: 10px;    width: 10px;        subcontrol-position: bottom;        subcontrol-origin: margin;    }"
              "QScrollBar:add-line:vertical:hover, QScrollBar::add-line:vertical:on {        border-image: url(\":/qss_icons/rc/down_arrow.png\");    height: 10px;    width: 10px;        subcontrol-position: bottom;        subcontrol-origin: margin;    }"
              "QScrollBar:sub-line:horizontal {    margin: 0px 3px 0px 3px;        border-image: url(\":/qss_icons/rc/left_arrow_disabled.png\");    height: 10px;    width: 10px;        subcontrol-position: left;        subcontrol-origin: margin;    }"
              "QScrollBar:sub-line:horizontal:hover, QScrollBar::sub-line:horizontal:on {        border-image: url(\":/qss_icons/rc/left_arrow.png\");    height: 10px;    width: 10px;        subcontrol-position: left;        subcontrol-origin: margin;    }"
              "QScrollBar:sub-line:vertical {    margin: 3px 0px 3px 0px;        border-image: url(\":/qss_icons/rc/up_arrow_disabled.png\");    height: 10px;    width: 10px;        subcontrol-position: top;        subcontrol-origin: margin;    }"
              "QScrollBar:sub-line:vertical:hover, QScrollBar::sub-line:vertical:on {        border-image: url(\":/qss_icons/rc/up_arrow.png\");    height: 10px;    width: 10px;        subcontrol-position: top;        subcontrol-origin: margin;    }";

    _style += "QScrollBar:up-arrow:horizontal, QScrollBar::down-arrow:horizontal    {   background: none;   } \n"
              "QScrollBar:up-arrow:vertical, QScrollBar::down-arrow:vertical        {   background: none;   } \n"
              "QScrollBar:add-page:horizontal, QScrollBar::sub-page:horizontal      {   background: none;   } \n"
              "QScrollBar:add-page:vertical, QScrollBar::sub-page:vertical          {   background: none;   } \n";
    _style += "\n";

    return _style;
}
QString cTcnStyle::styleSheet_QDoubleSpinBox()
{
    QString _style = "";

    _style += "QDoubleSpinBox {";
    _style += "background-color: " + _to_rgba(_c_tcn_light_grey) + ";";
    _style += "border: 4px solid " + _to_rgba(_c_tcn_black) + ";";
    _style += "color: " + _to_rgba(_c_tcn_black) + ";";
    _style += "border-radius: 10px;";
    _style += "min-height: 1.5em;";
    _style += "font-weight: 500;";
    _style += "margin: 2px 2px 2px 2px;";
    _style += "padding: 2px 2px 2px 2px;";
    _style += "}\n";

    _style += "QDoubleSpinBox:disabled {";
    _style += "background-color: " + _to_rgba(_c_tcn_white) + ";";
    _style += "border: 4px solid " + _to_rgba(_c_tcn_light_grey) + ";";
    _style += "color: " + _to_rgba(_c_tcn_light_grey) + ";";
    _style += "}\n";

    _style += "QDoubleSpinBox:selected {";
    _style += "background-color: " + _to_rgba(_c_tcn_light_grey) + ";";
    _style += "border: 4px solid " + _to_rgba(_c_tcn_black) + ";";
    _style += "color: " + _to_rgba(_c_tcn_black) + ";";
    _style += "}\n";

    _style += "QDoubleSpinBox:pressed {";
    _style += "background-color: " + _to_rgba(_c_tcn_blue) + ";";
    _style += "border: 4px solid " + _to_rgba(_c_tcn_white) + ";";
    _style += "color: " + _to_rgba(_c_tcn_black) + ";";
    _style += "}\n";

    _style += "QDoubleSpinBox:hover {";
    _style += "background-color: " + _to_rgba(_c_tcn_white) + ";";
    _style += "border: 4px solid " + _to_rgba(_c_tcn_blue) + ";";
    _style += "color: " + _to_rgba(_c_tcn_blue) + ";";
    _style += "}\n";

    _style += "QDoubleSpinBox::up-button {";
    _style += "background-color: " + _to_rgba(_c_tcn_black) + ";";
    //    _style += "padding: 2px 2px 2px 2px;";
    //    _style += "margin: 2px 2px 2px 2px;";
    _style += "subcontrol-origin: border;";
    _style += "subcontrol-position: top right;";
    _style += "width: 16px;";
    _style += "border-image: url(\":/qss_icons/rc/up_arrow.png\") 1;";
    _style += "border-width: 1px;";
    _style += "border-top-width: 0;";
    _style += "}\n";
    _style += "QDoubleSpinBox::up-button:hover {";
    _style += "background-color: " + _to_rgba(_c_tcn_blue) + ";";
    _style += "}\n";

    _style += "QDoubleSpinBox::down-button {";
    _style += "background-color: " + _to_rgba(_c_tcn_black) + ";";
    //    _style += "padding: 2px 2px 2px 2px;";
    //    _style += "margin: 2px 2px 2px 2px;";
    _style += "subcontrol-origin: border;";
    _style += "subcontrol-position: bottom right;";
    _style += "width: 16px;";
    _style += "border-image: url(\":/qss_icons/rc/down_arrow.png\") 1;";
    _style += "border-width: 1px;";
    _style += "border-top-width: 0;";
    _style += "}\n";
    _style += "QDoubleSpinBox::down-button:hover {";
    _style += "background-color: " + _to_rgba(_c_tcn_blue) + ";";
    _style += "}\n";

    return _style;
}
QString cTcnStyle::styleSheet_QSpinBox()
{
    QString _style = "";

    _style += "QSpinBox {";
    _style += "background-color: " + _to_rgba(_c_tcn_light_grey) + ";";
    _style += "border: 4px solid " + _to_rgba(_c_tcn_black) + ";";
    _style += "color: " + _to_rgba(_c_tcn_black) + ";";
    _style += "border-radius: 10px;";
    _style += "min-height: 1.5em;";
    _style += "font-weight: 500;";
    //    _style += "margin: 2px 2px 2px 17px;";
    //    _style += "padding: 2px 2px 2px 17px;";
    _style += "}\n";

    _style += "QSpinBox:disabled {";
    _style += "background-color: " + _to_rgba(_c_tcn_white) + ";";
    _style += "border: 4px solid " + _to_rgba(_c_tcn_light_grey) + ";";
    _style += "color: " + _to_rgba(_c_tcn_light_grey) + ";";
    _style += "}\n";

    _style += "QSpinBox:selected {";
    _style += "background-color: " + _to_rgba(_c_tcn_light_grey) + ";";
    _style += "border: 4px solid " + _to_rgba(_c_tcn_black) + ";";
    _style += "color: " + _to_rgba(_c_tcn_black) + ";";
    _style += "}\n";

    _style += "QSpinBox:pressed {";
    _style += "background-color: " + _to_rgba(_c_tcn_blue) + ";";
    _style += "border: 4px solid " + _to_rgba(_c_tcn_white) + ";";
    _style += "color: " + _to_rgba(_c_tcn_black) + ";";
    _style += "}\n";

    _style += "QSpinBox:hover {";
    _style += "background-color: " + _to_rgba(_c_tcn_white) + ";";
    _style += "border: 4px solid " + _to_rgba(_c_tcn_blue) + ";";
    _style += "color: " + _to_rgba(_c_tcn_blue) + ";";
    _style += "}\n";

    _style += "QSpinBox::up-button {";
    _style += "background-color: " + _to_rgba(_c_tcn_black) + ";";
    //    _style += "padding: 2px 2px 2px 2px;";
    //    _style += "margin: 2px 2px 2px 2px;";
    _style += "subcontrol-origin: border;";
    _style += "subcontrol-position: top right;";
    _style += "width: 16px;";
    _style += "border-image: url(\":/qss_icons/rc/up_arrow.png\") 1;";
    _style += "border-width: 1px;";
    _style += "border-top-width: 0;";
    _style += "}\n";
    _style += "QSpinBox::up-button:hover {";
    _style += "background-color: " + _to_rgba(_c_tcn_blue) + ";";
    _style += "}\n";

    _style += "QSpinBox::down-button {";
    _style += "background-color: " + _to_rgba(_c_tcn_black) + ";";
    //    _style += "padding: 2px 2px 2px 2px;";
    //    _style += "margin: 2px 2px 2px 2px;";
    _style += "subcontrol-origin: border;";
    _style += "subcontrol-position: bottom right;";
    _style += "width: 16px;";
    _style += "border-image: url(\":/qss_icons/rc/down_arrow.png\") 1;";
    _style += "border-width: 1px;";
    _style += "border-top-width: 0;";
    _style += "}\n";
    _style += "QSpinBox::down-button:hover {";
    _style += "background-color: " + _to_rgba(_c_tcn_blue) + ";";
    _style += "}\n";

    return _style;
}
QString cTcnStyle::styleSheet_QDateTimeEdit()
{
    QString _style = "";

    _style += "QDateTimeEdit {";
    _style += "background-color: " + _to_rgba(_c_tcn_light_grey) + ";";
    _style += "border: 4px solid " + _to_rgba(_c_tcn_black) + ";";
    _style += "color: " + _to_rgba(_c_tcn_black) + ";";
    _style += "border-radius: 10px;";
    _style += "min-height: 1.5em;";
    _style += "font-weight: 500;";
    _style += "}\n";

    _style += "QDateTimeEdit:disabled {";
    _style += "background-color: " + _to_rgba(_c_tcn_white) + ";";
    _style += "border: 4px solid " + _to_rgba(_c_tcn_black) + ";";
    _style += "color: " + _to_rgba(_c_tcn_black) + ";";
    _style += "}\n";

    _style += "QDateTimeEdit:hover {";
    _style += "background-color: " + _to_rgba(_c_tcn_white) + ";";
    _style += "border: 4px solid " + _to_rgba(_c_tcn_blue) + ";";
    _style += "color: " + _to_rgba(_c_tcn_blue) + ";";
    _style += "}\n";

    //    _style += "QDateTimeEdit:selected {";
    //    _style += "background-color: " + _to_rgba(_c_tcn_blue) + ";";
    //    _style += "border: 4px solid " + _to_rgba(_c_tcn_white) + ";";
    //    _style += "color: " + _to_rgba(_c_tcn_white) + ";";
    //    _style += "}\n";

    return _style;
}
QString cTcnStyle::styleSheet_QPlainTextEdit()
{
    QString _style = "";

    _style += "QPlainTextEdit {";
    _style += "background-color: " + _to_rgba(_c_tcn_light_grey) + ";";
    _style += "border: 4px solid " + _to_rgba(_c_tcn_black) + ";";
    _style += "color: " + _to_rgba(_c_tcn_black) + ";";
    _style += "border-radius: 10px;";
    //_style += "min-height: 1.5em;";
    //_style += "font-weight: 500;";
    _style += "}\n";

    return _style;
}

QString cTcnStyle::styleSheet_QTabWidget()
{
    QString _style = "";

    _style += "QTabWidget:pane {";
    _style += "background-color: " + _to_rgba(_c_tcn_light_grey) + ";";
    _style += "border: 4px solid " + _to_rgba(_c_tcn_black) + ";";
    _style += "color: " + _to_rgba(_c_tcn_black) + ";";
    _style += "border-radius: 10px;";
    _style += "margin: 2px 2px 2px 2px;";
    _style += "padding: 2px 2px 2px 2px;";
    _style += "}\n";

    return _style;
}
QString cTcnStyle::styleSheet_QTabBar()
{
    QString _style = "";

    _style += "QTabBar:tab {";
    _style += "}\n";

    _style += "QTabBar:tab:top {";
    _style += "background-color: " + _to_rgba(_c_tcn_light_grey) + ";";
    _style += "border: 4px solid " + _to_rgba(_c_tcn_black) + ";";
    _style += "color: " + _to_rgba(_c_tcn_black) + ";";
    _style += "border-radius: 10px;";
    _style += "min-width: 7em;";
    _style += "min-height: 2.5em;";
    _style += "font-weight: 500;";
    _style += "margin: 2px 2px 2px 2px;";
    _style += "padding: 2px 2px 2px 2px;";
    _style += "}\n";

    _style += "QTabBar:tab:top:selected {";
    _style += "background-color: " + _to_rgba(_c_tcn_blue) + ";";
    _style += "border: 4px solid " + _to_rgba(_c_tcn_black) + ";";
    _style += "color: " + _to_rgba(_c_tcn_black) + ";";
    _style += "}\n";

    _style += "QTabBar:tab:top:hover {";
    _style += "background-color: " + _to_rgba(_c_tcn_white) + ";";
    _style += "border: 4px solid " + _to_rgba(_c_tcn_blue) + ";";
    _style += "color: " + _to_rgba(_c_tcn_blue) + ";";
    _style += "}\n";

    return _style;
}
QString cTcnStyle::styleSheet_QCheckBox()
{
    QString _style = "";

    _style += "QCheckBox {";
    _style += "background-color: " + _to_rgba(_profile_color[e_profile_background]) + ";";
    //_style += "border: 2px solid;";
    //_style += "border-color: yellow;";
    _style += "color: " + _to_rgba(_profile_color[e_profile_text]) + ";";
    _style += "border-radius: 10px;";
    _style += "}\n";

    _style += "QCheckBox::indicator {";
    _style += "background-color: " + _to_rgba(_c_tcn_light_grey) + ";";
    _style += "}\n";

    _style += "QCheckBox::indicator:checked {";
    _style += "background-color: " + _to_rgba(_c_tcn_blue) + ";";
    _style += "}\n";

    return _style;
}
QString cTcnStyle::styleSheet_QComboBox()
{
    QString _style = "";

    _style += "QComboBox {";
    _style += "background-color: " + _to_rgba(_c_tcn_light_grey) + ";";
    _style += "border: 4px solid " + _to_rgba(_c_tcn_black) + ";";
    _style += "color: " + _to_rgba(_c_tcn_black) + ";";
    _style += "border-radius: 10px;";
    _style += "min-height: 1.5em;";
    // _style += "margin: 2px 2px 2px 10px;";
    // _style += "padding: 2px 2px 2px 10px;";
    //    _style += "selection-background-color: " + _to_rgba(_c_tcn_blue) + ";";
    //    //_style += "selection-border: 4px solid " + _to_rgba(_c_tcn_blue) + ";";
    //    _style += "selection-color: " + _to_rgba(_c_tcn_white) + ";";
    _style += "}\n";

    //    _style += "QComboBox QAbstractItemView {";
    //    _style += "background-color: " + _to_rgba(_c_tcn_white) + ";";
    //    _style += "border: 4px solid " + _to_rgba(_c_tcn_blue) + ";";
    //    _style += "color: " + _to_rgba(_c_tcn_black) + ";";
    //    _style += "border-radius: 10px;";
    //    _style += "min-height: 1.5em;";
    //    //    _style += "selection-background-color: " + _to_rgba(_c_tcn_light_grey) + ";";
    //    //    _style += "selection-color: " + _to_rgba(_c_tcn_blue) + ";";
    //    _style += "}\n";

    //    _style += "QComboBox QAbstractItemView::item:selected {";
    //    _style += "background-color: " + _to_rgba(_c_tcn_black) + ";";
    //    _style += "border: 4px solid " + _to_rgba(_c_tcn_blue) + ";";
    //    _style += "color: " + _to_rgba(_c_tcn_white) + ";";
    //    _style += "border-radius: 10px;";
    //    _style += "min-height: 1.5em;";
    //    //    _style += "selection-background-color: " + _to_rgba(_c_tcn_light_grey) + ";";
    //    //    _style += "selection-color: " + _to_rgba(_c_tcn_blue) + ";";
    //    _style += "}\n";

    _style += "QComboBox:pressed:hover {";
    _style += "background-color: " + _to_rgba(_c_tcn_blue) + ";";
    _style += "border: 4px solid " + _to_rgba(_c_tcn_black) + ";";
    _style += "color: " + _to_rgba(_c_tcn_black) + ";";
    _style += "border-radius: 10px;";
    _style += "}\n";

    _style += "QComboBox:hover {";
    _style += "background-color: " + _to_rgba(_c_tcn_white) + ";";
    _style += "border: 4px solid " + _to_rgba(_c_tcn_blue) + ";";
    _style += "color: " + _to_rgba(_c_tcn_blue) + ";";
    _style += "border-radius: 10px;";
    _style += "}\n";

    _style += "QComboBox:item {";
    _style += "background-color: " + _to_rgba(_c_tcn_light_grey) + ";";
    //    _style += "border: 4px solid " + _to_rgba(_c_tcn_blue) + ";";
    //    _style += "color: " + _to_rgba(_c_tcn_blue) + ";";
    //    _style += "border-radius: 10px;";
    _style += "}\n";

    _style += "QComboBox:item:selected {";
    _style += "background-color: " + _to_rgba(_c_tcn_white) + ";";
    _style += "border: 4px solid " + _to_rgba(_c_tcn_blue) + ";";
    _style += "color: " + _to_rgba(_c_tcn_blue) + ";";
    _style += "border-radius: 4px;";
    //_style += "min-height: 1.5em;";
    _style += "}\n";

    _style += "QComboBox:item:checked {";
    //    _style += "background-color: " + _to_rgba(_c_tcn_white) + ";";
    //    _style += "border: 4px solid " + _to_rgba(_c_tcn_blue) + ";";
    //    _style += "color: " + _to_rgba(_c_tcn_blue) + ";";
    //    _style += "border-radius: 10px;";
    _style += "}\n";

    //    _style += "QComboBox::down-arrow {";
    //    _style += "background-color: " + _to_rgba(_c_tcn_black) + ";";
    //    //    _style += "padding: 2px 2px 2px 2px;";
    //    _style += "margin: 3px 0px 3px 0px;"; /* top | right | bottom | left */
    //    _style += "subcontrol-origin: border;";
    //    _style += "subcontrol-position: bottom right;";
    //    _style += "width: 16px;";
    //    _style += "border-image: url(\":/qss_icons/rc/down_arrow.png\") 1;";
    //    _style += "border-width: 1px;";
    //    _style += "border-top-width: 0;";
    //    _style += "}\n";
    //    _style += "QComboBox::down-arrow:hover {";
    //    _style += "background-color: " + _to_rgba(_c_tcn_blue) + ";";
    //    _style += "}\n";

    return _style;
}
QString cTcnStyle::styleSheet_QProgressBar()
{
    QString _style = "";

    _style += "QProgressBar {";
    _style += "background-color: " + _to_rgba(_c_tcn_light_grey) + ";";
    _style += "border: 2px solid " + _to_rgba(_c_tcn_black) + ";";
    _style += "color: " + _to_rgba(_c_tcn_black) + ";";
    _style += "border-radius: 4px;";
    _style += "min-height: 1.5em;";
    _style += "text-align: center;";
    _style += "margin: 2px 2px 2px 2px;";
    _style += "padding: 2px 2px 2px 2px;";
    _style += "}\n";

    _style += "QProgressBar:chunk {";
    _style += "background-color: " + _to_rgba(_c_tcn_white) + ";";
    _style += "border: 4px solid " + _to_rgba(_c_tcn_blue) + ";";
    _style += "color: " + _to_rgba(_c_tcn_blue) + ";";
    _style += "border-radius: 4px;";
    _style += "}\n";

    _style += "QProgressBar:chunk:disabled {";
    _style += "background-color: " + _to_rgba(_c_tcn_white) + ";";
    _style += "border: 4px solid " + _to_rgba(_c_tcn_black) + ";";
    _style += "color: " + _to_rgba(_c_tcn_black) + ";";
    _style += "border-radius: 4px;";
    _style += "}\n";

    return _style;
}

QString cTcnStyle::styleSheet_QTextEdit()
{
    QString _style = "";

    _style += "QTextEdit {";
    _style += "background-color: " + _to_rgba(_profile_color[e_profile_background]) + ";";
    _style += "border: 2px solid;";
    _style += "border-color: yellow;";
    _style += "color: " + _to_rgba(_profile_color[e_profile_text]) + ";";
    _style += "border-radius: 10px;";
    _style += "}\n";

    return _style;
}

QString cTcnStyle::styleSheet_QFrame()
{
    QString _style = "";

    _style += "QFrame {";
    _style += "background-color: " + _to_rgba(_profile_color[e_profile_background]) + ";";
    _style += "border: 2px solid;";
    _style += "border-color: yellow;";
    _style += "color: " + _to_rgba(_profile_color[e_profile_text]) + ";";
    _style += "border-radius: 10px;";
    _style += "}\n";

    return _style;
}

QString cTcnStyle::_to_rgba(QColor _color)
{
    return QString("rgba(%1,%2,%3,%4)").arg(_color.red()).arg(_color.green()).arg(_color.blue()).arg(_color.alpha());
}

bool cTcnStyle::load_tcnStyle()
{
    QString _ss = "";

    _ss += styleSheet_QMainWindow();
    _ss += styleSheet_QWidget();
    _ss += styleSheet_QLineEdit();
    _ss += styleSheet_QGroupBox();
    _ss += styleSheet_QSplitter();

    _ss += styleSheet_QPushButton();
    _ss += styleSheet_QDoubleSpinBox();
    _ss += styleSheet_QSpinBox();
    _ss += styleSheet_QDateTimeEdit();
    _ss += styleSheet_QScrollBar();
    _ss += styleSheet_QPlainTextEdit();

    _ss += styleSheet_QTabWidget();
    _ss += styleSheet_QTabBar();

    _ss += styleSheet_QCheckBox();
    _ss += styleSheet_QComboBox();
    _ss += styleSheet_QProgressBar();

    _ss += styleSheet_QTextEdit();

    //_ss += styleSheet_QFrame();

    app->setStyleSheet(_ss);

    return false;
}
