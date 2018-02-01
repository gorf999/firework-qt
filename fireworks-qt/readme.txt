程序说明

作者：张龙
时间：2018年2月1日。
版权：LGPL 3.0

0、简介
    过年放烟花的程序，使用qt5.8开发，在deepin os (linux) 15.5及windows7(64位)下测试通过。

1、使用说明
左键双击暂停程序播放，右键双击退出程序。

2、四个功能类：
（1）CMainwindow，流程主控类与主显示类。
    程序流程分三个阶段：开始，中间，结束。其中用多个计时器来控制各个流程的自动切换。
    开始阶段：显示开始背景10秒钟。
    中间阶段：每5秒钟随机生成12个以内的烟花对象，加入QVector<CFirework> fireworkVector容器；每20毫秒刷新一次屏幕显示。
    结束阶段：延时5秒钟播放完剩余烟花后，显示结束背景12秒。
（2）CLaunchingPad，发射台类。
    生成一个发射台对象，该对象随机选择确定发射台的位置，赋给一个烟花对象。
（3）CFirework，烟花类。
    每个烟花对象自动每20毫秒生成一次烟花运动后的数据。
（4）CBackgroundMusic，背景音乐类。
    生成一个背景音乐对象。

3、音乐：
    （1）001.mp3, 001-红霞-过大年.mp3， 2.98M。
    （2）002.mp3, 002-六郎-红红火火过大年.mp3, 9.93M。
    （3）003.mp3, 003-左欣怡-欢欢喜喜过大年.mp3, 8.0M。
    （4）004.mp3, 004-邓卓轩-福星高照过大年.mp3, 7.91M。 //这首歌在window下，qt播放显示错误：“DirectShowPlayerService::doRender: Unresolved error code 0x80040266 ()”，在linux下播放不报错误。
    （5）005.mp3，005-刘德华-李宇春-恭喜发财2016.mp3，4.44M。

4、qt在windows与linux下编程时的部分区别20180125
（1）linux下用qtcreator编着程序时，资源文件（如*.jpg）放在与生成的可执行程序同一目录下即可，编程时直接使用文件名，不用加目录路径即可。如：new QImage("resource/firework01.jpg");
（2）windows下用qtcreator编着程序时，资源文件（如*.jpg）不能放在与生成的可执行程序同一目录下即debug或release目录，应放在上一级目录下，才能在编程时直接使用文件名，不用加目录路径即可。如：new QImage("resource/firework01.jpg");
 因为QCoreApplication::applicationDirPath()指向debug目录D:\MyDeveloping\build-fireworks-qt-Desktop_Qt_5_8_0_MinGW_32bit-Debug\debug，
 而QDir::currentPath()指向D:\MyDeveloping\build-fireworks-qt-Desktop_Qt_5_8_0_MinGW_32bit-Debug。
(3)因为qt的linux版编译主目录下没有debug与realease目录，可执行程序直接在编译主目录里，而windows版的可执行程序在debug或release目录下。

5、20180128，linux下用到了Qt的MultiMedia库，但deepin os 15.5的相应库未放在系统默认路径，可使用如下步骤建立链接：
sudo ln -s /usr/lib/x86_64-linux-gnu/libpulse.so.0.20.1  /usr/lib/libpulse.so
sudo ln -s /usr/lib/x86_64-linux-gnu/libpulse-mainloop-glib.so.0.0.5  /usr/lib/libpulse-mainloop-glib.so
