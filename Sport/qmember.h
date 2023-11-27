#ifndef QMEMBER_H
#define QMEMBER_H

#include "qitem.h"
#include <QRandomGenerator>

class QMember:public QItem
{
public:
    QMember(const QString &fileName);
    void advance(int phase);//ai运动
    int ballpath = 0;//0为人类 1为ai（下） 2为ai（中） 3为ai（上）
private:

};

#endif // QMEMBER_H
