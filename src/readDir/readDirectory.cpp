#include "readDirectory.h"

#include "../globalVar.h"

cReadDirectory::cReadDirectory(QWidget* parent)
    : QThread()
{

}

void cReadDirectory::run()
{
    cReadDir* _readDir = new cReadDir;
    folder->init();
    *folder = _readDir->readDirectory(path, exept_folders);
    quit();
}

cReadDir::cReadDir()
{
    _readInfo.init();
}

bool cReadDir::verifExeptDir(QString _path)
{
    for (int i = 0; i < c_globalVar->_exeptDir.size(); i++) {

        if (_path.contains(c_globalVar->_exeptDir.at(i)))
            return true;
    }
    return false;
}

void cReadDir::readDirPath(QString _path, bool exept)
{
    QDir dir(_path);
    foreach (QFileInfo item, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden | QDir::AllDirs | QDir::Files, QDir::DirsFirst))
    {
        if (item.isDir())
        {
            if (item.absoluteFilePath().size() > dir.path().size())
            {
                if (exept)
                {
                    if (not verifExeptDir(item.absoluteFilePath()))
                    {
                            _readInfo.listDirRead.push_back(item.absoluteFilePath());
                    }
                }
                else
                {
                    _readInfo.listDirRead.push_back(item.absoluteFilePath());
                }
            }
        }
    }
}


sFolder cReadDir::readDirectory(QString _path, bool exept_folders )
{
    sFolder _folder;
    _folder.init();
    _folder.folder_dir = _path;

    _readInfo.init();
    _readInfo.path = _path;
    _readInfo.listDirRead.push_back(_readInfo.path);

    while (_readInfo.nbreDirectory < _readInfo.listDirRead.size()) {
        readDirPath(_readInfo.listDirRead.at(_readInfo.nbreDirectory), exept_folders);
        _readInfo.nbreDirectory++;
    }

    foreach (QString dir, _readInfo.listDirRead) {
        if (dir.size() > _readInfo.path.size()) {

            QString _dstDir = dir;
            _dstDir.replace(_readInfo.path, "");

            sDirInfo _dirInfo;
            _dirInfo.path = _dstDir;
            _dirInfo.path_full = dir;
            _folder.listDir.push_back(_dirInfo);
        }
    }
    return _folder;
}
