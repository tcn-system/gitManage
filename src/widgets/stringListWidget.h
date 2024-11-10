#ifndef STRINGLISTWDGT_H
#define STRINGLISTWDGT_H

#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>

#include <QCloseEvent>

#include <QHeaderView>
#include <QTableWidget>
#include <QTableWidgetItem>

#include <QPushButton>

class cStringListWdgt : public QWidget {
    Q_OBJECT

public:
    cStringListWdgt(QStringList* _stringList, QString _name, QWidget* parent = nullptr);
    ~cStringListWdgt();

signals:

    void SIGNAL_save();

public slots:

    void SLOT_qpb_save();

private:
    QStringList* qsl_stringList = nullptr;

    QTableWidget* qtw_tableWidget = nullptr;

    QPushButton* qpb_save;

    void load_table();
};

#endif // STRINGLISTWDGT_H
