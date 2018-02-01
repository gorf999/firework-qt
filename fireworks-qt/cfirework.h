#ifndef CFIREWORK_H
#define CFIREWORK_H


#include <QObject>
#include <QImage>
#include <QTimerEvent>

class CFirework : public QObject
{
    Q_OBJECT
public:

    struct bullet   //未爆炸前的烟花弹的结构体
    {
        QImage * image;//烟花弹图片
        const char * imageFile;   //1.烟花弹图片文件名.2.因指向的文件名是固定不变的字符串，所以类型前面应加const修饰符
        int imageWidth=20, imageHeight=50;//烟花弹图片的静态宽，高

        int x=0,y=0;//开始发射点
        int maxHeight=768-200;  //上升的最大高度限制

        bool show=true;  //显示开关
    } blt;

    struct firework //爆炸后的烟花结构体
    {
        QImage * image;//烟花图片
        const char * imageFile;   //1.烟花图片文件名.2.因指向的文件名是固定不变的字符串，所以类型前面应加const修饰符
        int imageWidth=240, imageHeight=240;//烟花图片静态宽，高

        int x=0,y=0;//其开始绽放的坐标
        int cen_x=0,cen_y=0;//图片绽放中心

        int curWidth=0, curHeight=0;/**** 1.烟花图片绽放的当前宽、高。2.如果此处不赋初值，就会部分出现有烟花弹而无爆炸的烟花的哑弹现象，
                                    即常说的变量不赋初值程序会出现一些不可预料的现象，此时这些变量在内存中的值或者是负值，或者是超出屏幕边界的大值。
                                    这也正是c++语法复杂的原因,因为c++是语法严格的语言，要求一切是确定的无二意的，但现实世界是复杂的，为了描述复杂的世界，需要复杂的语言语法。
                                    3.此处的赋初值，是在结构体的实现中赋初值，纯结构体的声明与实现是一体的；而类将声明与实现分开了，分别在.h文件与.cpp文件中，类的头文件中变量也能赋初值，因为他们是局部性的；
                                    但切记.h头文件中的全局型变量对象除了静态全局变量外都不能赋初值，因为他们是变量声明而不是变量定义，赋了初值就是变量定义而不是声明了。
                                    *************/
        int maxWidth=240, maxHeight=240;//烟花图片绽放的最大宽、高

        bool show = false;//绽放开关
    } fw;

    enum FireworkState  //烟花状态
    {
        exploded, unexploded
    } fstate;

    static const int fireworkTypes=49;  //烟花种类数

    bool launchFlag=false;    //是否发射
    int selfRefreshTimerId; //发射后的自我刷新计时器，即自我更新坐标、及爆炸后的烟花当前宽度、高度等，该计时器计时间隔应与CMainWindow的屏幕刷新间隔screenRefreshTimerId保持一致。
    int changeRate=2;   //爆炸后的烟花半径增长速度，即每次屏幕刷新后图像的放大速度

    bool pauseFirework = false;

    bool over = false;   //烟花爆炸结束标志

public:
    explicit CFirework(QObject *parent = 0);
    ~CFirework();


    const char * chooseBulletType();
    void chooseBulletMaxHeight();
    const char * chooseFireworkType();

    void startSelfRefreshTimer();
    void timerEvent(QTimerEvent *event);

public slots:
    void slotStartSelfRefresh();
    void slotPauseSelfRefresh();

signals:

public slots:

};

#endif // CFIREWORK_H
