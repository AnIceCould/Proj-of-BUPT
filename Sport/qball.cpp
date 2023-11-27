#include "qball.h"

QBall::QBall(const QString &fileName):QItem(fileName)
{
    //ballstart();
    lastpoint.setX(600);//坐标原点
    lastpoint.setY(250);
}

void QBall::advance(int phase){//时钟检测
    gametime++;
    speedcontrol();
    this->setPos(mapToScene(xspeed,yspeed));//移动
    //撞墙检测
    if(this->x()>1200 || this->x()<0){//左右撞墙后回正并发球
        if(myScore != 3 && aiScore != 3){//结束后不再传回
            this->setPos(600,250);
            //ballstart();
        }
        xspeed = 0;
        yspeed = 0;
    }
    if(this->y()>475 || this->y()<25){//上下撞墙后原地反向发球
        ballstart(2);//上下反向发球
    }
    //碰撞检测
    if(this->collidingItems().count() > 0){//碰撞
        //若越过球员则不再碰撞
        if(this->x()<950 && this->x()>250)
            ballstart(1);//反向发球
    }
    //进球检测
    if(this->x()>1050 && win == 0){
        myScore++;
        win = 1;
    }
    if(this->x()<150 && win == 0){
        aiScore++;
        win = 1;
    }
    theY = this->y();
}

void QBall::speedcontrol(){//速度控制
    //左右控制
    if(xspeed > 0.005){
        xspeed = xspeed - 0.005;//正向左移动
    }
    else if(xspeed < -0.005){
        xspeed = xspeed + 0.005;//负向右移动
    }
    else xspeed = 0;
    //上下控制
    if(yspeed > 0.005){
        yspeed = yspeed - 0.005;//正向左移动
    }
    else if(yspeed < -0.005){
        yspeed = yspeed + 0.005;//负向右移动
    }
    else yspeed = 0;
    //极限速度
    if(xspeed > 8){
        xspeed = 4;
        yspeed = QRandomGenerator::global()->generateDouble()*4;
    }
    if(yspeed > 6){
        xspeed = QRandomGenerator::global()->generateDouble()*4 + 2;
        yspeed = 3;
    }

}

void QBall::ballstart(int direction){//发球
    double ra = QRandomGenerator::global()->generateDouble();//随机方向
    double lastxspeed = xspeed;//储存
    double lastyspeed = yspeed;
    if(direction == 0){//随机发球
        win = 0;
        xspeed = QRandomGenerator::global()->generateDouble()*4 + 3;//随机
        yspeed = QRandomGenerator::global()->generateDouble()*4;
        if(ra>0.25 && ra<=0.5){//第一象限
            yspeed = -yspeed;
        }
        else if(ra>0.5 && ra<=0.75){//第四象限
            xspeed = -xspeed;
            yspeed = -yspeed;
        }
        else if(ra>0.75){//第三象限
            xspeed = -xspeed;
        }
    }
    else if(direction == 1){//全反向
        xspeed = -lastxspeed*1.5;
        yspeed = -lastyspeed*2;
    }
    else if(direction == 2){//上下反向
        xspeed = lastxspeed*1.1 + QRandomGenerator::global()->generateDouble()-0.5;
        yspeed = -lastyspeed*1 + QRandomGenerator::global()->generateDouble()-0.5;
    }
    else {//停止
        xspeed = 0;
        yspeed = 0;
    }
    //减少多次碰撞
    this->setPos(mapToScene(xspeed,yspeed));

}

