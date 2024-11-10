#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <QtCore/QDate>
#include <QtCore/QDir>

class cFileManager {
public:
    cFileManager(const QDir& root);

    const QDir& root() const;

    QDir logsDir() const;
    QDir parameterDir() const;

    bool verifyAllDirCreate() const;

private:
    QDir storageRoot;
};

#endif // FILE_MANAGER_H
