#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <QObject>
#include <QSettings>

class cSettings : public QObject {
    Q_OBJECT

public:
    cSettings();
    ~cSettings();

    void init();

    bool _read_App_Parametre_();
    bool _write_App_Parametre_(bool _first_write = false);

signals:

    void SIGNAL_settings_finish();

private slots:

private:
};

#endif // SETTINGS_H_
