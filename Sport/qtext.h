#ifndef QTEXT_H
#define QTEXT_H

#include <QGraphicsSimpleTextItem>
#include <QBrush>
#include <QFile>
#include <QByteArray>

#include "global.h"

class QText:public QGraphicsSimpleTextItem
{
public:
    QText(int mode);//0为计分表，1为难度表
    void advance(int phase);//更新
    int timenow = 0;//计时次数
private:
    int textmode;//文本类型
    void winorlose(bool wol);//赢或输(0为输1为赢)
    void showup();//显示
};

#endif // QTEXT_H
