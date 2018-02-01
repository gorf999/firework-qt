#ifndef CBACKGROUNDMUSIC_H
#define CBACKGROUNDMUSIC_H

#include <QObject>
#include <qmediaplayer.h>
#include <qmediaplaylist.h>

class CBackgroundMusic : public QObject
{
    Q_OBJECT

public:
    QMediaPlayer * mplayer;
    QMediaPlaylist * playList;

    bool pauseMediaPlayer=false;

public:
    explicit CBackgroundMusic(QObject *parent = 0);
    ~CBackgroundMusic();

    void initMediaPlayer();
    void destroyMediaPlayer();

signals:

public slots:
    void slotPlayMediaPlayer();
    void slotPauseMediaPlayer();
};

#endif // CBACKGROUNDMUSIC_H
