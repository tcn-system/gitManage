#ifndef LABELCLICKWIDGET_H
#define LABELCLICKWIDGET_H

#include <QDialog>
#include <QLabel>


class cLabelClickWidget: public QLabel
{
    Q_OBJECT

public:

    cLabelClickWidget                (QWidget *parent = 0);
    ~cLabelClickWidget               ();

    bool get_stat() const { return _stat; }

protected:
    void mousePressEvent        (QMouseEvent *e);

signals:
    void clicked                (bool _stat);

private:

    QString                     _styleSheet = "";
    bool                        _stat = false;

};

#endif // LABELCLICKWIDGET_H
