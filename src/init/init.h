#ifndef INIT_H_
#define INIT_H_

#include <QObject>
#include <QTimer>

#include "../readDir/readDirectory.h"


enum eStatInit {

    e_stat_init_start,

    e_stat_init_search,
    e_stat_init_wait,

    e_stat_init_end,

};

class cInit : public QObject {
    Q_OBJECT

public:
    cInit();
    ~cInit();

    void init();

signals:

    void SIGNAL_line_edit(QString _string);

    void SIGNAL_init_finish();

private slots:

    void SLOT_readDirectory_finish();

    void SLOT_timer_tick();

private:
    QTimer* mTimer;

    int idx_list_seach;
    QString _srcPath;

    eStatInit e_stat_init;
    int tempo_init;

    bool search_is_finish;
};

#endif // INIT_H_
