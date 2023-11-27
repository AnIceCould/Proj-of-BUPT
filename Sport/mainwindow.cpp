/*登陆窗口*/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(260,200);
    //结束按钮
    connect(ui->exitButton,&QPushButton::clicked,this,[=](){
        this->close();
    });
    //开始按钮
    connect(ui->startButton,&QPushButton::clicked,this,[=](){
        //切换窗口
        setwindow = new SetNameWindow(this);
        this->hide();
        if(getwindow != NULL){
            getwindow->hide();
        }
        setwindow->show();
    });
    //排行榜按钮
    connect(ui->rankButton,&QPushButton::clicked,this,[=](){
        //切换窗口
        getwindow = new GetScoreWindow(this);
        //this->hide();
        getwindow->show();
    });
    //操作说明
    connect(ui->actionUpdate,&QAction::triggered,this,[=](){
        QMessageBox::information(this,"游戏介绍",
                                 "鼠标控制上下移动\n"
                                 "回车发球\n"
                                 "1(简单)2(普通)3(困难)设置难度\n"
                                 "ESC结束游戏"
                                 );
    });
    //信息
    connect(ui->actionMessage,&QAction::triggered,this,[=](){
        QMessageBox::information(this,"作品信息","程序设计综合实验\n作品名：桌面球\n作者：见昊男");
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

