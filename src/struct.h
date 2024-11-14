#ifndef STRUCT_H_
#define STRUCT_H_

#include <QDir>

#include "define.h"
#include "enum.h"

struct sDirInfo {

    QString path_full;
    QString path;

    sDirInfo()
    {
        init();
    }
    void init()
    {
        path_full = "";
        path = "";
    }
};
struct sFolder {

    QString folder_dir;

    QList<sDirInfo> listDir;

    sFolder()
    {
        init();
    }
    void init()
    {
        folder_dir = "";

        listDir.clear();
    }
};

struct sReadInfo {

    QString path;

    int nbreDirectory;

    QStringList listDirRead;

    void init()
    {
        path = "";

        nbreDirectory = 0;

        listDirRead.clear();
    }
};

struct sGitBranch {

    QString nameBranch;

    void init()
    {
        nameBranch = "";
    }
};

struct sGitRemote {

    QString nameRemote;
    QString pathRemote;

    void init()
    {
        nameRemote = "";
        pathRemote = "";
    }
};

struct sGitProject {

    QDir dirPath;
    QString nameProject;

    bool is_up_to_date;
    int nbre_commit;

    int idx_branch_in_process;
    QList<sGitBranch> l_branch;
    QString main_master_branch_name;

    int idx_branch_remote_in_process;
    QList<sGitBranch> l_branch_remote;


    sGitRemote l_remotePush;
    sGitRemote l_remoteFetch;

    void init()
    {
        dirPath = QDir("");
        nameProject = "";

        is_up_to_date = false;
        nbre_commit = -1;

        idx_branch_in_process = -1;
        l_branch.clear();
        main_master_branch_name = "";

        idx_branch_remote_in_process = -1;
        l_branch_remote.clear();

        l_remotePush.init();
        l_remoteFetch.init();
    }
};

#endif // STRUCT_H
