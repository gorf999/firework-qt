#include "cbackgroundmusic.h"
#include "compilepreprocessor.h"

#include <qdir.h>

CBackgroundMusic::CBackgroundMusic(QObject *parent) : QObject(parent)
{
    initMediaPlayer();
}

CBackgroundMusic::~CBackgroundMusic()
{
    destroyMediaPlayer();
}

void CBackgroundMusic::initMediaPlayer()
{
    mplayer = new QMediaPlayer(this);
    mplayer->setAudioRole(QAudio::MusicRole);

    playList = new QMediaPlaylist;
#ifdef WINDOWS
    playList->addMedia(QMediaContent(QUrl::fromLocalFile("resource/002.mp3")));
    playList->addMedia(QUrl::fromLocalFile("resource/001.mp3"));
    playList->addMedia(QUrl::fromLocalFile("resource/003.mp3"));
    playList->addMedia(QUrl::fromLocalFile("resource/004.mp3"));
    playList->addMedia(QUrl::fromLocalFile("resource/005.mp3"));
#else
    playList->addMedia(QMediaContent(QUrl::fromLocalFile(QDir::currentPath()+"/resource/001-红霞-过大年.mp3") ) );
    playList->addMedia(QUrl::fromLocalFile(QDir::currentPath()+"/resource/002-六郎-红红火火过大年.mp3") );
    playList->addMedia(QUrl::fromLocalFile(QDir::currentPath()+"/resource/003-左欣怡-欢欢喜喜过大年.mp3"));
    playList->addMedia(QUrl::fromLocalFile(QDir::currentPath()+"/resource/004-邓卓轩-福星高照过大年.mp3"));   //这首歌在window下，qt播放显示错误：“DirectShowPlayerService::doRender: Unresolved error code 0x80040266 ()”，在linux下播放不报错误。
    playList->addMedia(QUrl::fromLocalFile(QDir::currentPath()+"/resource/005-刘德华-李宇春-恭喜发财2016.mp3"));
#endif

    playList->setPlaybackMode(QMediaPlaylist::Loop);
    playList->setCurrentIndex(1);

    mplayer->setPlaylist(playList);
}

void CBackgroundMusic::destroyMediaPlayer()
{
    delete mplayer;
    delete playList;
}

void CBackgroundMusic::slotPlayMediaPlayer()
{
    pauseMediaPlayer=false;
    mplayer->play();
}

void CBackgroundMusic::slotPauseMediaPlayer()
{
    pauseMediaPlayer=true;
    mplayer->pause();
}


