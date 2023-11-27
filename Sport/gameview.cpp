#include "gameview.h"
//#include <QDebug>

GameView::GameView()
{
    //界面设置
    this->setWindowTitle("一场比赛");
    this->setFixedSize(1200,500);
    this->setBackgroundBrush(QBrush(QPixmap(":/bis/Image/Background.jpeg")));
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);//刷新
    //场景设置
    gamescene = new QGraphicsScene;
    gamescene->setSceneRect(0,0,this->width()-2,this->height()-2);
    this->setScene(gamescene);
    //计分文本
    gametext = new QText(0);
    gametext->setText("得分:0-0");
    gametext->setBrush(Qt::black);
    gametext->setFont(QFont("微软雅黑",12));
    gamescene->addItem(gametext);
    //难度文本
    modetext = new QText(1);
    modetext->setText("难度为：普通");
    modetext->setBrush(Qt::yellow);
    modetext->setFont(QFont("微软雅黑",15));
    gamescene->addItem(modetext);
    modetext->setPos(1050,-40);
    //球
    ball = new QBall(":/bis/Image/ball.png");
    ball->setPos(this->width()/2,this->height()/2);
    gamescene->addItem(ball);
    //左球员
    lmember1 = new QMember(":/bis/Image/lember.png");
    lmember1->setPos(this->width()/5,this->height()/4);
    gamescene->addItem(lmember1);
    lmember2 = new QMember(":/bis/Image/lember.png");
    lmember2->setPos(this->width()/5,this->height()/2);
    gamescene->addItem(lmember2);
    lmember3 = new QMember(":/bis/Image/lember.png");
    lmember3->setPos(this->width()/5,3*this->height()/4);
    gamescene->addItem(lmember3);
    //右球员
    rmember1 = new QMember(":/bis/Image/rember.png");
    rmember1->setPos(this->width()/5*4,this->height()/4);
    gamescene->addItem(rmember1);
    rmember1->ballpath = 1;
    rmember2 = new QMember(":/bis/Image/rember.png");
    rmember2->setPos(this->width()/5*4,this->height()/2);
    gamescene->addItem(rmember2);
    rmember2->ballpath = 2;
    rmember3 = new QMember(":/bis/Image/rember.png");
    rmember3->setPos(this->width()/5*4,3*this->height()/4);
    gamescene->addItem(rmember3);
    rmember3->ballpath = 3;
    //定时器
    timer = new QTimer;
    connect(timer,SIGNAL(timeout()),gamescene,SLOT(advance()));
    timer->start(10);//0.01s
}
void GameView::mouseMoveEvent(QMouseEvent *event){//鼠标点击后移动
    QPoint p;
    p = event->pos();
    if(p.y() < 350 && p.y() > 150){//限制上下
        lmember1->setY(p.y() - this->height()/4);
        lmember2->setY(p.y());
        lmember3->setY(p.y() + this->height()/4);
    }
}

void GameView::keyPressEvent(QKeyEvent *event){//按键检测
    if(event->key() == 16777221 || event->key() == 16777220){//检测到回车
        if(ball->x() == width()/2 && ball->y() == height()/2){//发球
            ball->ballstart(0);
        }
        /*else {
            ball->ballstart(4);//停止
        }*/
        if(ball->xspeed == 0 && ball->yspeed == 0){
            if(myScore == 3 || aiScore == 3){
                remake();
            }
            ball->setPos(this->width()/2,this->height()/2);//球重置
            //球员重置
            rmember1->setPos(this->width()/5*4,this->height()/4);
            rmember2->setPos(this->width()/5*4,this->height()/2);
            rmember3->setPos(this->width()/5*4,this->height()/4*3);
        }
    }
    if(event->key() == 49){//检测按键1
        gamemode = 1;
        modetext->setPos(1050,-40);
        modetext->timenow = 0;
        remake();
    }
    else if(event->key() == 50){//检测按键2
        gamemode = 2;
        modetext->setPos(1050,-40);
        modetext->timenow = 0;
        remake();
    }
    else if(event->key() == 51){//检测按键3
        gamemode = 3;
        modetext->setPos(1050,-40);
        modetext->timenow = 0;
        remake();
    }
    if(event->key() == 16777216){//按键ESC
        this->close();
    }
}

void GameView::remake(){//重置
    //时间重置
    gametime = 0;
    outtime = 0;
    //计分重置
    myScore = 0;
    aiScore = 0;
    gametext->setPos(0,0);
    //球重置
    ball->setPos(this->width()/2,this->height()/2);
    ball->xspeed = 0;
    ball->yspeed = 0;
    //球员重置
    rmember1->setPos(this->width()/5*4,this->height()/4);
    rmember2->setPos(this->width()/5*4,this->height()/2);
    rmember3->setPos(this->width()/5*4,this->height()/4*3);
}
