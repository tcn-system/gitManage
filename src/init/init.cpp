#include "init.h"

#include "../globalVar.h"

cInit::cInit()
{
    mTimer = new QTimer;
    connect(mTimer, &QTimer::timeout, this, &cInit::SLOT_timer_tick);

    idx_list_seach = 0;
    l_gitProject.clear();

    _srcPath = "";

    e_stat_init = e_stat_init_start;
    tempo_init = 0;

    search_is_finish = false;
}
cInit::~cInit()
{
    if (mTimer->isActive())
        mTimer->stop();

    delete mTimer;
}

void cInit::init()
{
    mTimer->start(10);

    qDebug() << "cInit::init";
}

void cInit::SLOT_timer_tick()
{
    if (tempo_init >= 0)
        tempo_init++;

    switch (e_stat_init) {
    case e_stat_init_start: {

        qDebug() << "e_stat_init_start" << idx_list_seach << c_globalVar->_listFolderSearch.size();

        if (c_globalVar->_listFolderSearch.size() > 0) {

            if (idx_list_seach < c_globalVar->_listFolderSearch.size()) {

                e_stat_init = e_stat_init_search;
                tempo_init = 0;

            } else {

                e_stat_init = e_stat_init_end;
                tempo_init = 0;
            }
        } else {

            e_stat_init = e_stat_init_end;
            tempo_init = 0;
        }
    } break;

    case e_stat_init_search: {
        search_is_finish = false;

        _srcPath = c_globalVar->_listFolderSearch.at(idx_list_seach);

        qDebug() << "e_stat_init_search" << _srcPath;

        emit SIGNAL_line_edit(_srcPath);

        cReadDirectory* readFolder = new cReadDirectory;
        connect(readFolder, &cReadDirectory::finished, this, &cInit::SLOT_readDirectory_finish);
        readFolder->setPath(_srcPath, true);
        readFolder->setFolder(&c_globalVar->s_folderRead);
        readFolder->start();

        e_stat_init = e_stat_init_wait;
        tempo_init = 0;
    } break;

    case e_stat_init_wait: {

        if (search_is_finish == true) {

            search_is_finish = false;

            qDebug() << "e_stat_init_wait";

            if (idx_list_seach < c_globalVar->_listFolderSearch.size()) {
                idx_list_seach++;
            }

            e_stat_init = e_stat_init_start;
            tempo_init = 0;
        }
    } break;

    case e_stat_init_end:
    default: {

        qDebug() << "e_stat_init_end";

        if (tempo_init == 1) {

            tempo_init = -1;
            emit SIGNAL_init_finish();
        }
    } break;
    }
}

void cInit::SLOT_readDirectory_finish()
{
    for (int i = 0; i < c_globalVar->s_folderRead.listDir.size(); i++) {

        QString _pathGit = c_globalVar->s_folderRead.listDir.at(i).path_full;
        QStringList l_pathSplit = _pathGit.split("/");

        if (l_pathSplit.size() > 0) {
            if (not l_pathSplit.at(l_pathSplit.size() - 1).compare(".git")) {
                sGitProject _git;

                _git.init();

                QString path = "";
                for (int i = 0; i < l_pathSplit.size() - 1; i++) {
                    if (i > 0)
                        path += "/";
                    path += l_pathSplit.at(i);
                }

                _git.dirPath = QDir(path);
                _git.nameProject = l_pathSplit.at(l_pathSplit.size() - 2);

                l_gitProject.push_back(_git);
            }
        }
    }

    search_is_finish = true;
}
