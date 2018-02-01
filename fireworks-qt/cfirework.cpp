#include "cfirework.h"

#include <QTime>
#include <qdir.h>

CFirework::CFirework(QObject *parent) : QObject(parent)
{

    chooseBulletType();

    blt.image = new QImage(blt.imageFile);
    chooseBulletMaxHeight();

    fw.image = new QImage(fw.imageFile);

}

CFirework::~CFirework() //注意：1、析构函数不能带参数；2、也不用显示指明从父类的的析构函数继承。
{
    delete fw.image;
    delete blt.image;
    killTimer(selfRefreshTimerId);
}


//随机选择烟花弹的最大上升高度。
void CFirework::chooseBulletMaxHeight()
{
    int i;
    qsrand(QTime::currentTime().msec()+QTime::currentTime().second()*10000);
    i=fw.imageHeight/2+qrand()%(fw.imageHeight);
    blt.maxHeight=i;

}

const char * CFirework::chooseFireworkType()    //注意：因返回值是字符串常量，所以指向这些字符串的char *前，要加上const限定符。
{
    QTime time;
    time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    int i= qrand()%fireworkTypes;
    switch(i){
    case 0:
        blt.imageFile="./resource/bullet00.jpg";
        fw.imageFile="./resource/firework00.jpg";
        return "./resource/firework00.jpg";
        break;
    case 1:
        blt.imageFile="resource/bullet01.jpg";
        fw.imageFile="resource/firework01.jpg";
        return "resource/firework01.jpg";
        break;
    case 2:
        blt.imageFile="resource/bullet02.jpg";
        fw.imageFile="resource/firework02.jpg";
        return "resource/firework02.jpg";
        break;
    case 3:
        blt.imageFile="resource/bullet03.jpg";
        fw.imageFile="resource/firework03.jpg";
        return "resource/firework03.jpg";
        break;
    case 4:
        blt.imageFile="resource/bullet04.jpg";
        fw.imageFile="resource/firework04.jpg";
        return "resource/firework04.jpg";
        break;
    case 5:
        blt.imageFile="resource/bullet05.jpg";
        fw.imageFile="resource/firework05.jpg";
        return "resource/firework05.jpg";
        break;
    case 6:
        blt.imageFile="resource/bullet06.jpg";
        fw.imageFile="resource/firework06.jpg";
        return "resource/firework06.jpg";
        break;
    case 7:
        blt.imageFile="resource/bullet00.jpg";
        fw.imageFile="resource/firework07.jpg";
        return "resource/firework07.jpg";
        break;
    case 8:
        blt.imageFile="resource/bullet01.jpg";
        fw.imageFile="resource/firework08.jpg";
        return "resource/firework08.jpg";
        break;
    case 9:
        blt.imageFile="resource/bullet02.jpg";
        fw.imageFile="resource/firework09.jpg";
        return "resource/firework09.jpg";
        break;
    case 10:
        blt.imageFile="resource/bullet03.jpg";
        fw.imageFile="resource/firework10.jpg";
        return "resource/firework10.jpg";
        break;
    case 11:
        blt.imageFile="resource/bullet04.jpg";
        fw.imageFile="resource/firework11.jpg";
        return "resource/firework11.jpg";
        break;
    case 12:
        blt.imageFile="resource/bullet05.jpg";
        fw.imageFile="resource/firework12.jpg";
        return "resource/firework12.jpg";
        break;
    case 13:
        blt.imageFile="resource/bullet06.jpg";
        fw.imageFile="resource/firework13.jpg";
        return "resource/firework13.jpg";
        break;
    case 14:
        blt.imageFile="resource/bullet00.jpg";
        fw.imageFile="resource/firework14.jpg";
        return "resource/firework14.jpg";
        break;
    case 15:
        blt.imageFile="resource/bullet01.jpg";
        fw.imageFile="resource/firework15.jpg";
        return "resource/firework15.jpg";
        break;
    case 16:
        blt.imageFile="resource/bullet02.jpg";
        fw.imageFile="resource/firework16.jpg";
        return "resource/firework16.jpg";
        break;
    case 17:
        blt.imageFile="resource/bullet03.jpg";
        fw.imageFile="resource/firework17.jpg";
        return "resource/firework17.jpg";
        break;
    case 18:
        blt.imageFile="resource/bullet04.jpg";
        fw.imageFile="resource/firework18.jpg";
        return "resource/firework18.jpg";
        break;
    case 19:
        blt.imageFile="resource/bullet05.jpg";
        fw.imageFile="resource/firework19.jpg";
        return "resource/firework19.jpg";
        break;
    case 20:
        blt.imageFile="resource/bullet06.jpg";
        fw.imageFile="resource/firework20.jpg";
        return "resource/firework20.jpg";
        break;
    case 21:
        blt.imageFile="resource/bullet00.jpg";
        fw.imageFile="resource/firework21.jpg";
        return "resource/firework21.jpg";
    case 22:
        blt.imageFile="resource/bullet01.jpg";
        fw.imageFile="resource/firework22.jpg";
        return "resource/firework22.jpg";
    case 23:
        blt.imageFile="resource/bullet02.jpg";
        fw.imageFile="resource/firework23.jpg";
        return "resource/firework23.jpg";
    case 24:
        blt.imageFile="resource/bullet03.jpg";
        fw.imageFile="resource/firework24.jpg";
        return "resource/firework24.jpg";
    case 25:
        blt.imageFile="resource/bullet04.jpg";
        fw.imageFile="resource/firework25.jpg";
        return "resource/firework25.jpg";
    case 26:
        blt.imageFile="resource/bullet05.jpg";
        fw.imageFile="resource/firework26.jpg";
        return "resource/firework26.jpg";
    case 27:
        blt.imageFile="resource/bullet06.jpg";
        fw.imageFile="resource/firework27.jpg";
        return "resource/firework27.jpg";
    case 28:
        blt.imageFile="resource/bullet00.jpg";
        fw.imageFile="resource/firework28.jpg";
        return "resource/firework28.jpg";
    case 29:
        blt.imageFile="resource/bullet01.jpg";
        fw.imageFile="resource/firework29.jpg";
        return "resource/firework29.jpg";
    case 30:
        blt.imageFile="resource/bullet02.jpg";
        fw.imageFile="resource/firework30.jpg";
        return "resource/firework30.jpg";
    case 31:
        blt.imageFile="resource/bullet03.jpg";
        fw.imageFile="resource/firework31.jpg";
        return "resource/firework31.jpg";
    case 32:
        blt.imageFile="resource/bullet04.jpg";
        fw.imageFile="resource/firework32.jpg";
        return "resource/firework32.jpg";
    case 33:
        blt.imageFile="resource/bullet05.jpg";
        fw.imageFile="resource/firework33.jpg";
        return "resource/firework33.jpg";
    case 34:
        blt.imageFile="resource/bullet06.jpg";
        fw.imageFile="resource/firework34.jpg";
        return "resource/firework34.jpg";
    case 35:
        blt.imageFile="resource/bullet00.jpg";
        fw.imageFile="resource/firework35.jpg";
        return "resource/firework35.jpg";
    case 36:
        blt.imageFile="resource/bullet01.jpg";
        fw.imageFile="resource/firework36.jpg";
        return "resource/firework36.jpg";
    case 37:
        blt.imageFile="resource/bullet02.jpg";
        fw.imageFile="resource/firework37.jpg";
        return "resource/firework37.jpg";
    case 38:
        blt.imageFile="resource/bullet03.jpg";
        fw.imageFile="resource/firework38.jpg";
        return "resource/firework38.jpg";
    case 39:
        blt.imageFile="resource/bullet04.jpg";
        fw.imageFile="resource/firework39.jpg";
        return "resource/firework39.jpg";
    case 40:
        blt.imageFile="resource/bullet05.jpg";
        fw.imageFile="resource/firework40.jpg";
        return "resource/firework40.jpg";
    case 41:
        blt.imageFile="resource/bullet06.jpg";
        fw.imageFile="resource/firework41.jpg";
        return "resource/firework41.jpg";
    case 42:
        blt.imageFile="resource/bullet00.jpg";
        fw.imageFile="resource/firework42.jpg";
        return "resource/firework42.jpg";
    case 43:
        blt.imageFile="resource/bullet01.jpg";
        fw.imageFile="resource/firework43.jpg";
        return "resource/firework43.jpg";
    case 44:
        blt.imageFile="resource/bullet02.jpg";
        fw.imageFile="resource/firework44.jpg";
        return "resource/firework44.jpg";
    case 45:
        blt.imageFile="resource/bullet03.jpg";
        fw.imageFile="resource/firework45.jpg";
        return "resource/firework45.jpg";
    case 46:
        blt.imageFile="resource/bullet04.jpg";
        fw.imageFile="resource/firework46.jpg";
        return "resource/firework46.jpg";
    case 47:
        blt.imageFile="resource/bullet05.jpg";
        fw.imageFile="resource/firework47.jpg";
        return "resource/firework47.jpg";
    case 48:
        blt.imageFile="resource/bullet06.jpg";
        fw.imageFile="resource/firework48.jpg";
        return "resource/firework48.jpg";
    default:
        blt.imageFile="resource/bullet00.jpg";
        fw.imageFile="resource/firework00.jpg";
        return "resource/firework00.jpg";
        break;
    }
}

const char * CFirework::chooseBulletType()    //注意：因返回值是字符串常量，所以指向这些字符串的char *前，要加上const限定符。
{
    chooseFireworkType();
    return blt.imageFile;
}

void CFirework::startSelfRefreshTimer()
{
    selfRefreshTimerId = startTimer(20,Qt::CoarseTimer); /***1.启动烟花刷新计时器。2.此处定时器的类型定位coarse型，即其精度对程序表现影响很大，
    非常粗的verycoarse型表现不好。3、此处的刷新时间的确定，应根据LED显示器的刷新频率为60HZ，即LED显示器16.67毫秒刷新一次屏幕来确定的，不宜偏离16.67太远。
    ************************************************************************************/

    launchFlag=true;
}


void CFirework::slotStartSelfRefresh()
{
    pauseFirework =false;
}



void CFirework::slotPauseSelfRefresh()
{
    pauseFirework = true;
}


void CFirework::timerEvent(QTimerEvent *event)
{
    if(pauseFirework==false)
    {
        if(event->timerId() == selfRefreshTimerId)
        {
            if(blt.show == true)
            {
                if(blt.y > blt.maxHeight)
                {
                    blt.y-=changeRate*2;
                } else
                {
                    blt.show = false;
                    fw.x = blt.x;
                    fw.y = blt.y - blt.imageHeight/2;
                    fw.show=true;
                }
            }

            if(fw.show == true)
            {
                if( fw.curWidth < fw.maxWidth || fw.curHeight < fw.maxHeight )
                {

                    fw.curWidth+=changeRate;
                    fw.curHeight+=changeRate;

                    /*************
           （1）鉴于系统放大图像时总是保持左上角坐标不变，向右下角放大图像，为显示图像是由中心向四周放大，
            每次放大后应向相反方向移动图像的坐标，才能保证新图与旧图的中心一致,反向移动距离为放大距离changeRate的一半。
           （2）移动绘图的中心这句提出要求，changeRate应当大于等于2，且最好是偶数。
            *************/
                    fw.x-=changeRate/2;
                    fw.y-=changeRate/2;

                } else
                {
                    over=true;
                }
            }
        }
    }
}
