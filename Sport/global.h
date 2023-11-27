#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>

class Global
{
public:
    Global();
};
//全局变量
extern int theY;//球的Y坐标
extern int gametime;//游戏时间
extern int outtime;//胜利时间
extern int myScore;//自己得分
extern int aiScore;//ai得分
extern int gamemode;//游戏难度
extern double numrand;//aichance
extern QString username;//用户名

#endif // GLOBAL_H
