#include "console.h"

#include "../globalVar.h"

cConsole* c_console;

cConsole::cConsole(QWidget* parent)
    : QPlainTextEdit(parent)
{
    this->setWindowTitle(cMake_projectName + QString(" - page::console - ") + cMake_projectVersion + " qt" + cMake_qtVersion + " - tcn-system.com");
    this->setWindowIcon(QIcon(_D_ICON_PATH));

    document()->setMaximumBlockCount(5000);
    // mPalette = palette();
    // mPalette.setColor(QPalette::Base, QColor(_D_White));
    // mPalette.setColor(QPalette::Text, QColor(_D_Black));
    // setPalette(mPalette);

    scrollBarV = verticalScrollBar();

    fileLog = new FILE;

    mTimer = new QTimer;
    connect(mTimer, &QTimer::timeout, this, &cConsole::updateTimerSlot);

    mTimer->start(10);

    // double _resize = 0.8;
    // this->resize(c_globalVar->sizescreen.width() * _resize, c_globalVar->sizescreen.height() * _resize);

}
cConsole::~cConsole()
{
    if (mTimer->isActive())
        mTimer->stop();

    delete mTimer;
}

void cConsole::putDataStr(QString data)
{
    putData(data.toUtf8());
}
void cConsole::putData(const QByteArray& data)
{
    //    if (this->toPlainText().size() > 100000)
    //        clear();

    insertPlainText(data);

    if (logInProcess)
        fprintf(fileLog, "%s", data.constData());

    scrollBarV->setValue(scrollBarV->maximum());
}
void cConsole::resetData()
{
    clear();
}

void cConsole::setLocalEchoEnabled(bool set)
{
    m_localEchoEnabled = set;
}

void cConsole::startLogFile()
{
    QDateTime dateTime = QDateTime::currentDateTime();
    QString str;
    std::string filename;

    str = QString(c_globalVar->fileManager->logsDir().path() + "/file_" + dateTime.toString("yyyy-MM-dd-hh-mm-ss") + ".txt");
    filename = str.toStdString();

    fileLog = fopen(filename.c_str(), "wb");
    logInProcess = true;
}
void cConsole::stopLogFile()
{
    if (logInProcess)
        fclose(fileLog);
}

void cConsole::keyPressEvent(QKeyEvent* e)
{
    switch (e->key()) {
    case Qt::Key_Backspace:
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
        break;
    default:
        if (m_localEchoEnabled)
            QPlainTextEdit::keyPressEvent(e);
        emit getData(e->text().toLocal8Bit());
    }
}

void cConsole::mousePressEvent(QMouseEvent* e)
{
    Q_UNUSED(e)
    setFocus();
}

void cConsole::mouseDoubleClickEvent(QMouseEvent* e)
{
    Q_UNUSED(e)
}

void cConsole::contextMenuEvent(QContextMenuEvent* e)
{
    Q_UNUSED(e)
}

void cConsole::updateTimerSlot()
{
    while (c_globalVar->_debugInConsole.size() > 0) {
        putDataStr(c_globalVar->_debugInConsole.at(0));
        c_globalVar->_debugInConsole.pop_front();
    }
}
