#ifndef DEFINE_H_
#define DEFINE_H_

#include <QList>
#include <QString>
#include <QStringList>

#define _D_ICON_PATH ":/images/tcnSystemIcon.png"
#define _D_PROJET_PATH_FILE "/tcn-system/" + cMake_projectName

#define _D_STOP -1

#define _D_QS_INT(X) QString::number(X)
#define _D_QS_DOUBLE(X) QString::number(X, 'f', 3)
#define _D_QS_DOUBLE_1(X) QString::number(X, 'f', 1)

#define _D_QS_HEX_02(X)  QString("%1").arg(X, 2, 16, QChar('0'))
#define _D_QS_HEX_04(X)  QString("%1").arg(X, 4, 16, QChar('0'))
#define _D_QS_HEX_08(X)  QString("%1").arg(X, 8, 16, QChar('0'))

#define _D_QS_INT_02(X)  QString("%1").arg(X, 2, 10, QChar('0'))
#define _D_QS_INT_04(X)  QString("%1").arg(X, 4, 10, QChar('0'))

const QStringList _D_exeptDir = {

    "/0_Build",
    "/0_build",
    "/1_archive",
    "/1_Archive" ,
    "/Debug" ,
    "/Release" ,
    "/.vscode",
    "/.cache" ,
    "/.metadata" ,
    "/Packages" ,
    "/Programmes" ,
    "/Windows" ,
    "/Utilisateur"
};

const QStringList _D_listFolderSearch = {

#if defined (_WIN32) || defined (_WIN64)

    "D:/OSCAR_NG",
    "D:/POLYCLIM_NG",
    "C:/Users/thcousin/Desktop/Data_tcn/tcn_qt_git",

#else

    "/home/tcousin/Bureau/tcn_soft_git"

#endif

};


#endif // DEFINE_H_
