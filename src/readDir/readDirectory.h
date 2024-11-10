#ifndef READ_DIRECTORY_H_
#define READ_DIRECTORY_H_

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QObject>
#include <QString>
#include <QTextStream>

#include <QThread>

#include "../struct.h"

class cReadDirectory : public QThread {
    Q_OBJECT

public:

    cReadDirectory(QWidget* parent = nullptr);

    void run();

    void setPath( QString _path, bool _exept_folders = true )
    {
        path = _path;
        exept_folders = _exept_folders;
    }
    void setFolder(sFolder* _folder) { folder = _folder; }
    void read_exit()
    {
        if (isRunning()) {
            exit();
        }

        wait();

        quit();
        deleteLater();
    }

private:
    QString path = "";
    bool exept_folders = true;
    sFolder* folder;
};

class cReadDir {

public:
    cReadDir();

    sFolder readDirectory(QString _path, bool exept_folders = true);

private:

    sReadInfo _readInfo;

    void readDirPath(QString _path, bool exept = true);
    bool verifExeptDir(QString _path);
};

#endif // SYNCFOLDER_H_
