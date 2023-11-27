#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QBrush>
#include <QMouseEvent>
#include <QPoint>
#include <QTimer>

#include "qtext.h"
#include "qball.h"
#include "qmember.h"

class GameView:public QGraphicsView
{
public:
    GameView();
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void remake();//重置
    QText* gametext;//计分文本框指针
    QText* modetext;//难度文本框指针
private:
    QGraphicsScene* gamescene;//场景指针
    QBall *ball;//球指针
    QTimer *timer;//计时器指针
    //球员指针
    QMember *lmember1;
    QMember *lmember2;
    QMember *lmember3;
    QMember *rmember1;
    QMember *rmember2;
    QMember *rmember3;
};

#endif // GAMEVIEW_H
