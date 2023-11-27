#ifndef QITEM_H
#define QITEM_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include "global.h"

//显示物体的基类
class QItem:public QGraphicsItem
{
public:
    QItem(const QString &fileName);//绑定图片
    QRectF boundingRect() const;//碰撞体积
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);//显示

private:
    QPixmap pixmap;//图片

};

#endif // QITEM_H
