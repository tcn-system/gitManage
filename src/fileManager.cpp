#include "fileManager.h"

cFileManager::cFileManager(const QDir& root)
    : storageRoot(root)
{
}

const QDir& cFileManager::root() const
{
    return storageRoot;
}

QDir cFileManager::logsDir() const
{
    return storageRoot.path() + "/log";
}
QDir cFileManager::parameterDir() const
{
    return storageRoot.path() + "/parameter";
}

bool cFileManager::verifyAllDirCreate() const
{
    QDir ldir;

    ldir = logsDir();
    if (!ldir.exists()) {
        ldir.mkpath(".");
    }
    ldir = parameterDir();
    if (!ldir.exists()) {
        ldir.mkpath(".");
    }
    return false;
}
