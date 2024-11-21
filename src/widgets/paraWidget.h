#ifndef PARAWIDGET_H
#define PARAWIDGET_H

#include <QHBoxLayout>
#include <QWidget>
#include <QVBoxLayout>
#include <QFrame>

enum eAlignWidget {

    e_align_horizontal,
    e_align_vertical

};


class cParaWidget_x2 : public QWidget {
    Q_OBJECT

public:
    cParaWidget_x2(QWidget* _label , QWidget* _parametre , eAlignWidget e_align = e_align_horizontal , QWidget* parent = nullptr);
    ~cParaWidget_x2();


};

class cParaWidget_x4 : public QWidget {
    Q_OBJECT

public:
    cParaWidget_x4(QWidget* _label_1 , QWidget* _parametre_1 , QWidget* _label_2 , QWidget* _parametre_2 , eAlignWidget e_align = e_align_horizontal , QWidget* parent = nullptr);
    ~cParaWidget_x4();


};


#endif // PARAWIDGET_H
