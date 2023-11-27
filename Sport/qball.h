#ifndef QBALL_H
#define QBALL_H

#include "qitem.h"
#include <QRandomGenerator>
#include <QMessageBox>

//足球类
class QBall:public QItem
{
public:
    QBall(const QString &fileName);
    void advance(int phase);//移动
    void ballstart(int direction);//发球 0为随机 1为全反向 2为上下反向
    int win = 0;//有一方进球
    double xspeed;//x速度
    double yspeed;//y速度

private:
    void speedcontrol();//速度控制
    QPointF lastpoint;//前一碰撞点
};

#endif // QBALL_H
