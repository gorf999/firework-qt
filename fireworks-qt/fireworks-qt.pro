#-------------------------------------------------
#
# Project created by QtCreator 2018-01-24T18:59:05
#
#-------------------------------------------------

#-------------------------------------------------
# 注意：下面的“QT += ......”中如果不先行加入相应的库的话，有三种已知后果：
#1、编辑某个.cpp或.h要加入该库中的头文件时不支持逐步提示相应的头文件名功能，如不加入multimedia库，则不会提示qmediaplayer.h文件。
#2、自行加入相应的头文件，编辑时不支持相应的函数逐步提示功能。
#3、即使自行加入了相应的头文件，编译时也提示不认识相应的类，如不加入multimedia库，则不认QMediaPlayer类。
# 也就是说，如果程序中用到某类此处没有的库的话，要现先在此*.pro文件中加入相应的库，而后在qr creator编辑*.cpp,*.h时才能使用相应库中的类。
#-----------------------------------------------
QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fireworks-qt
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        cmainwindow.cpp \
    cfirework.cpp \
    claunchingpad.cpp \
    cbackgroundmusic.cpp

HEADERS  += cmainwindow.h \
    cfirework.h \
    claunchingpad.h \
    cbackgroundmusic.h \
    compilepreprocessor.h

FORMS    += cmainwindow.ui

DISTFILES += \
    readme.txt
