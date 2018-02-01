#include "cmainwindow.h"
#include "ui_cmainwindow.h"


#include <qdir.h>
#include <QMouseEvent>
#include <qpainter.h>
#include <qpalette.h>
#include <QTime>


CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMainWindow)
{
    ui->setupUi(this);

    //setWindowFlags(Qt::CustomizeWindowHint); //此函数可以隐藏窗口的标题条，但是同时最小化、最大化、关闭按钮也没了。

    chooseWindowBackgound();

    stageStartTimerId = startTimer(10000,Qt::CoarseTimer);   //片头播放10秒钟。
    beginBackgroundMusicTimerId=startTimer(2000,Qt::CoarseTimer);//片头图片显示2秒钟后开始背景音乐

    this->setWindowTitle("新 年 快 乐");
    this->setFixedSize(1366, 768);

    backgroundMusic = new CBackgroundMusic();
    connect(this,SIGNAL(signalPlayBackgroundMusic()),backgroundMusic, SLOT(slotPlayMediaPlayer()));
    connect(this,SIGNAL(signalPauseBackgroundMusic()),backgroundMusic, SLOT(slotPauseMediaPlayer()));

}

CMainWindow::~CMainWindow()
{
    delete ui;
    killTimer(screenRefreshTimerId);
    killTimer(launchTimerId);

    delete backgroundMusic;
}

void CMainWindow::paintEvent(QPaintEvent *event)
{

    QPainter painter;
    painter.begin(this);
    painter.setCompositionMode(QPainter::CompositionMode_Lighten);

    for(QVector<CFirework*>::iterator iter=fireworkVector.begin(); iter<fireworkVector.end(); iter++)
    {
        if((* iter)->blt.show == true)  //注意：1、if判断语句中一定使用“ == ”双等于号才是判断是否相等操作，而“ = ”单等于号是赋值操作。2、如果此处错误的使用了单等于号，qt5.8编译器不会报错。
        {
            painter.drawImage((* iter)->blt.x, (* iter)->blt.y, *((* iter)->blt.image));
        }

        if((* iter)->fw.show == true)
        {
            painter.drawImage((* iter)->fw.x, (* iter)->fw.y, (* iter)->fw.image->scaled((* iter)->fw.curWidth,(* iter)->fw.curHeight));
        }

    }

    painter.end();

}

void CMainWindow::timerEvent(QTimerEvent *event)
{
    switch (goStage)
    {
    case stageStart:
        if(event->timerId() == beginBackgroundMusicTimerId)
        {
            emit signalPlayBackgroundMusic();
        }
        if(event->timerId()==stageStartTimerId)
        {
            goStage=stageMiddle;
            chooseWindowBackgound();
            stageMiddleTimerId = startTimer(7200000,Qt::CoarseTimer);  //烟花最长播放两小时，而后自动结束。
            screenRefreshTimerId = startTimer(20,Qt::CoarseTimer); //1.启动屏幕刷新计时器。2.此处定时器的类型定位coarse型，即其精度对程序表现影响很大，非常粗的verycoarse型表现不好。3、此处的刷新时间的确定，应根据LED显示器的刷新频率为60HZ，即LED显示器16.67毫秒刷新一次屏幕来确定的，不宜偏离16.67太远。
            launchTimerId = startTimer(3000,Qt::CoarseTimer);   //启动发射计时器
        }
        break;
    case stageMiddle:
        if(pauseProgram==false)
        {
            //1、屏幕刷新
            if(event->timerId() == screenRefreshTimerId)
            {
                for(QVector<CFirework*>::iterator iter=fireworkVector.begin(); iter<fireworkVector.end(); iter++)
                {

                    if( (* iter)->over == true)
                    {
                        delete * iter;
                        fireworkVector.erase(iter);
                    }

                }
                repaint();  /*注意：任何时候屏幕刷新函数 repaint()都不能放在上面的for循环体内，否则的话就会出现更新每个循环变量更新后都刷新一次的现象，
                            事实上应当是在所有循环变量(即所有的烟花的新数据)都准备好后才统一刷新一次屏幕;如果不注意放在了循环体内，屏幕上就会出现各烟花弹交替上升而不时同时上升的现象，
                            而且因刷新次数太多，导致系统开销太大，屏幕会出现卡顿现象。
                            */
            }


            //2、发射烟花弹
            if(event->timerId() == launchTimerId)
            {
                launchFirework();
            }


            //3.中间阶段结束
            if(event->timerId()==stageMiddleTimerId)
            {
                goStage=stageEnd;
                delayTimerId=startTimer(5000,Qt::CoarseTimer);
                stageEndTimerId = startTimer(12000,Qt::CoarseTimer);  //设置片尾播放计时器为片尾播放5秒钟，而后程序自动结束。
            }
        }
        break;

    case stageEnd:
        //1、结束阶段延时以便剩余的烟花播放完毕
        if(event->timerId() == screenRefreshTimerId)
        {
            for(QVector<CFirework*>::iterator iter=fireworkVector.begin(); iter<fireworkVector.end(); iter++)
            {

                if( (* iter)->over == true)
                {
                    disconnect(this,SIGNAL(signalPlayFirework()),(* iter),SLOT(slotStartSelfRefresh()));
                    disconnect(this,SIGNAL(signalPauseFirework()),(* iter),SLOT(slotPauseSelfRefresh()));
                    delete * iter;
                    fireworkVector.erase(iter);
                }

            }
            repaint();
        }

        //2、结束阶段延时完毕后更改背景。
        if(event->timerId()==delayTimerId)
        {
            chooseWindowBackgound();
            backgroundMusic->slotPauseMediaPlayer();
        }
        //3、结束程序
        if(event->timerId()==stageEndTimerId)
            this->close();
    default:
        break;
    }
}

void CMainWindow::chooseWindowBackgound()
{
    switch (goStage) {
    case stageStart:
    {
        QPalette palette01 = this->palette();
        QBrush brush01(QImage("resource/start.jpg").scaled(1366,768));
        palette01.setBrush(QPalette::Background, brush01);
        this->setPalette(palette01);
        this->setAutoFillBackground(true);
    }   /* 注意：在case的子句中定义了局部变量的话，如本句中的palette01与brush01,必须用花括号｛｝把所有该case的子句括起来，因为编译器担心不括起来的话，
        此类局部变量可能会被后面的case语句使用而让程序出错。 */
        break;
    case stageMiddle:
    {
        QPalette palette02 = this->palette();
        palette02.setColor(QPalette::Background,Qt::black);
        this->setPalette(palette02);
    }
        break;
    case stageEnd:
    {
        /*表单方式显示窗口背景不支持本地文件
            this->setStyleSheet("background-image:url(:/resource/start.jpg)");
        */
        QPalette palette03 = this->palette();
        QBrush brush03(QImage("resource/end.jpg").scaled(1366,768));
        palette03.setBrush(QPalette::Background, brush03);
        this->setPalette(palette03);
        this->setAutoFillBackground(true);
    }
        break;
    default:
        break;
    }
}

//程序控制，鼠标左键双击暂停，右键双击退出程序。
void CMainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(goStage == stageMiddle)
    {
        if(event->button() == Qt::LeftButton)
        {
            if(pauseProgram==false)
            {
                emit signalPauseBackgroundMusic();
                emit signalPauseFirework();
                pauseProgram=true;
            } else
            {
                emit signalPlayBackgroundMusic();
                emit signalPlayFirework();
                pauseProgram=false;
            }
        }

        if(event->button()==Qt::RightButton)
        {
            goStage=stageEnd;
            delayTimerId = startTimer(5000,Qt::CoarseTimer);
            stageEndTimerId = startTimer(15000,Qt::CoarseTimer);  //设置片尾播放计时器为片尾播放15秒钟，而后程序自动结束。
        }
    }
}

//设置同时发射的烟花数在12以内随机确定
void CMainWindow::setFireworkRandomNumber()
{
    QTime time;
    time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    fireworkRandomCount = qrand() % 12;
}

void CMainWindow::launchFirework()
{
    setFireworkRandomNumber();

    for(int i=0; i<fireworkRandomCount; i++)
    {
        CLaunchingPad lpad;

        CFirework * tmpFw = new CFirework();
        tmpFw->blt.x=lpad.x;
        tmpFw->blt.y=lpad.y;

        connect(this,SIGNAL(signalPlayFirework()),tmpFw,SLOT(slotStartSelfRefresh()));
        connect(this,SIGNAL(signalPauseFirework()),tmpFw,SLOT(slotPauseSelfRefresh()));

        tmpFw->startSelfRefreshTimer();
        emit signalPlayFirework();

        fireworkVector.append(tmpFw);

    }
}
