#ifndef CLAUNCHINGPAD_H
#define CLAUNCHINGPAD_H

#include <QObject>

class CLaunchingPad : public QObject
{
    Q_OBJECT


public:
        int x = 0, y = 0;    //发射台坐标
        const int fireworkMaxRadius = 120;

public:
    explicit CLaunchingPad(QObject *parent = 0);
    void chooseLaunchCoordinate();

signals:

public slots:
};

#endif // CLAUNCHINGPAD_H
