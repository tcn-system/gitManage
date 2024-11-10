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


class cParaWidget : public QWidget {
    Q_OBJECT

public:
    cParaWidget(QWidget* _label , QWidget* _parametre , eAlignWidget e_align = e_align_horizontal , QWidget* parent = nullptr);
    ~cParaWidget();


};


#endif // PARAWIDGET_H
