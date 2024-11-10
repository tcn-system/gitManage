#ifndef PUSHBTN_H
#define PUSHBTN_H

#include <QLabel>
#include <QWidget>

#include "../struct.h"

class cPushBtn : public QLabel
{
    Q_OBJECT

public:
    cPushBtn(sGitProject _gitProject , QWidget* parent = nullptr);
    ~cPushBtn();

signals:
    void clicked();

protected:
    void mousePressEvent        (QMouseEvent *e);
};

#endif // PUSHBTN_H
