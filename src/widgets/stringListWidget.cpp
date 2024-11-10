
#include "stringListWidget.h"

#include "../globalVar.h"

cStringListWdgt::cStringListWdgt(QStringList* _stringList, QString _name, QWidget* parent)
    : QWidget(parent)
{
    qsl_stringList = _stringList;

    QVBoxLayout* main_layout = new QVBoxLayout;

    QGroupBox* _groupBox = new QGroupBox(_name);
    {
        QVBoxLayout* v_layout = new QVBoxLayout;

        qtw_tableWidget = new QTableWidget;

        qtw_tableWidget->clear();

        qtw_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

        qtw_tableWidget->horizontalHeader()->setVisible(false);
        qtw_tableWidget->verticalHeader()->setVisible(false); // pour masquer les titres de ligne
        qtw_tableWidget->setFocusPolicy(Qt::NoFocus); // pour interdire le focus (permet d'enlever les pointillés quand on clique sur une case)

        qtw_tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded /*ScrollBarAlwaysOn*/);
        qtw_tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

        v_layout->addWidget(qtw_tableWidget);

        qpb_save = new QPushButton("save");
        connect(qpb_save, SIGNAL(pressed()), this, SLOT(SLOT_qpb_save()));

        v_layout->addWidget(qpb_save);

        _groupBox->setLayout(v_layout);
    }

    main_layout->addWidget(_groupBox);

    setLayout(main_layout);

    load_table();
}
cStringListWdgt::~cStringListWdgt()
{
}

void cStringListWdgt::load_table()
{
    qtw_tableWidget->clearContents();

    qtw_tableWidget->setColumnCount(1);
    qtw_tableWidget->setRowCount(qsl_stringList->size() + 1);

    for (int _idx = 0; _idx < qsl_stringList->size(); _idx++) {

        qtw_tableWidget->setItem(_idx, 0, new QTableWidgetItem(qsl_stringList->at(_idx)));
    }

    qtw_tableWidget->resizeColumnsToContents();
}

void cStringListWdgt::SLOT_qpb_save()
{
    QStringList _stringList;
    _stringList.clear();

    for (int i = 0; i < qtw_tableWidget->rowCount(); i++) {

        QTableWidgetItem* _item = qtw_tableWidget->item(i, 0);
        if (_item) {
            QString _text = _item->text();
            if (_text.size() > 0)
                _stringList.push_back(_text);
        }
    }

    qDebug() << "list" << _stringList;

    qsl_stringList->clear();
    for (int i = 0; i < _stringList.size(); i++) {
        qsl_stringList->push_back(_stringList.at(i));
    }

    load_table();

    emit SIGNAL_save();
}
