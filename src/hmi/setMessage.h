#ifndef SETMESSAGE_H
#define SETMESSAGE_H

#include <QTextEdit>
#include <QWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>

#include "../struct.h"

class cSetMessage : public QDialog
{
    Q_OBJECT

public:
    cSetMessage( QWidget* parent = nullptr);
    ~cSetMessage();

signals:
    void SIGNAL_message(QString message);

public slots:

    void SLOT_qte_textEdit_textChange();

    void SLOT_qpb_abort();
    void SLOT_qpb_accept();

private:

    QTextEdit* qte_textEdit;

    QPushButton* qpb_abort;
    QPushButton* qpb_accept;

    QString message;
};

#endif // SETMESSAGE_H
