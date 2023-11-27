#include "setnamewindow.h"

SetNameWindow::SetNameWindow(QWidget *parent)
    : QMainWindow{parent}
{
    setFixedSize(260,150);
    this->setWindowTitle("您的名称是");
    //标签
    nameLable = new QLabel(this);
    nameLable->move(30,20);
    nameLable->resize(200,20);
    nameLable->setText("请输入名称（这将记录在排行榜中）：");
    //编辑框
    nameEdit = new QLineEdit(this);
    nameEdit->move(50,50);
    nameEdit->resize(160,30);
    //继续按钮
    nextButton = new QPushButton("开始",this);
    nextButton->move(30,100);
    nextButton->resize(80,25);
    connect(nextButton,&QPushButton::clicked,this,[=](){
        //开始游戏
        if(nameEdit->text() != ""){
            username = nameEdit->text();
            gameview = new GameView;
            this->hide();
            gameview->show();
        }
        else {
            QMessageBox::warning(this,"提示","请输入您的名称");
        }

    });
    //返回按钮
    backButton = new QPushButton("返回",this);
    backButton->move(150,100);
    backButton->resize(80,25);
    connect(backButton,&QPushButton::clicked,this,[=](){
        //切换窗口
        this->hide();
        parent->show();
    });
}
