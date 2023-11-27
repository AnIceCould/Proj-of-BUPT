#include "qitem.h"

QItem::QItem(const QString &fileName)
{
    pixmap.load(fileName);//读取图片
}

//图片碰撞体积
QRectF QItem::boundingRect() const{
    return QRectF(-pixmap.width()/2,-pixmap.height()/2,pixmap.width(),pixmap.height());
}

//图片绘制
void QItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawPixmap(-pixmap.width()/2,-pixmap.height()/2,pixmap);
}

