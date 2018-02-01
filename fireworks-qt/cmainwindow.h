#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QMainWindow>
#include <qmediaplayer.h>
#include <qmediaplaylist.h>

#include "cfirework.h"
#include "claunchingpad.h"
#include "cbackgroundmusic.h"

namespace Ui {
class CMainWindow;
}

class CMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int fireworkRandomCount=0;  //设置同时发射的烟花数
    QVector <CFirework * >  fireworkVector;

    int stageStartTimerId;  //开始阶段计时器id.
    int beginBackgroundMusicTimerId;    //开始背景音乐计时器id.

    int stageMiddleTimerId; //中间阶段计时器id.
    int screenRefreshTimerId;//屏幕刷新计时器id.
    int changeRate=2;   //爆炸后的烟花半径增长速度，即每次屏幕刷新后图像的放大速度
    int launchTimerId;//发射计时器id.


    int stageEndTimerId;    //结束阶段计时器id.
    int delayTimerId;   //结束阶段开始后等待最后的烟花播放完毕才的计时器id.

    enum ProgramStage {stageStart, stageMiddle, stageEnd} goStage=stageStart; //程序阶段，开始阶段显示开始图片，中间阶段显示烟花，结束阶段显示结束图片。

    bool pauseProgram=false;    //暂停程序标志

    CBackgroundMusic * backgroundMusic; //背景音乐

public:
    explicit CMainWindow(QWidget *parent = 0);
    ~CMainWindow();

    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

    void chooseWindowBackgound();   //在开始、中间、结束三个不同的阶段显示不同的窗口背景。

    void setFireworkRandomNumber(); //设置同时播放的烟花数
    void launchFirework();  //发射烟花


private:
    Ui::CMainWindow *ui;

signals:
    void signalPlayBackgroundMusic();
    void signalPauseBackgroundMusic();
    void signalPlayFirework();
    void signalPauseFirework();

};

#endif // CMAINWINDOW_H
