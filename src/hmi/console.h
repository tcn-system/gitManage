#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <QObject>
#include <QPlainTextEdit>
#include <QScrollBar>
#include <QString>
#include <QTimer>

class cConsole : public QPlainTextEdit {
    Q_OBJECT

signals:
    void getData(const QByteArray& data);

public:
    explicit cConsole(QWidget* parent = nullptr);
    ~cConsole();

    void setLocalEchoEnabled(bool set);
    void resetData();

    void startLogFile();
    void stopLogFile();

private slots:
    void updateTimerSlot();

protected:
    void keyPressEvent(QKeyEvent* e) override;
    void mousePressEvent(QMouseEvent* e) override;
    void mouseDoubleClickEvent(QMouseEvent* e) override;
    void contextMenuEvent(QContextMenuEvent* e) override;

private:
    QTimer* mTimer;

    QPalette mPalette;

    QScrollBar* scrollBarV;

    void putDataStr(QString data);
    void putData(const QByteArray& data);

    bool m_localEchoEnabled = false;

    FILE* fileLog;
    bool logInProcess = false;
};

extern cConsole* c_console;

#endif // CONSOLE_H
