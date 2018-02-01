#include "claunchingpad.h"

#include <QTime>

CLaunchingPad::CLaunchingPad(QObject *parent) : QObject(parent)
{
    chooseLaunchCoordinate();
}

//将烟花弹的发射坐标的范围随机限制在屏幕底部两边各减去烟花图片宽度一半的的范围内。
void  CLaunchingPad::chooseLaunchCoordinate()
{
    int i;
    qsrand(QTime::currentTime().msec()+QTime::currentTime().second()*1000);
    i=fireworkMaxRadius+qrand()%(1366-fireworkMaxRadius*2);
    x=i;
    y=768-68;
}

