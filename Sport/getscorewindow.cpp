#include "getscorewindow.h"

GetScoreWindow::GetScoreWindow(QWidget *parent)
    : QMainWindow{parent}
{
    //分数结构
    /*struct scroe{
        char name[10];
        char rank[10];
    };
    scroe paiming[100];*/

    setFixedSize(500,400);
    this->setWindowTitle("历史排行榜");
    //编辑框
    rankEdit = new QTextEdit(this);
    rankEdit->move(50,30);
    rankEdit->setFont(QFont("微软雅黑",12));
    rankEdit->resize(400,300);
    //返回按钮
    reButton = new QPushButton("返回",this);
    reButton->move(200,350);
    reButton->resize(100,25);
    connect(reButton,&QPushButton::clicked,this,[=](){
        //切换窗口
        this->hide();
        parent->show();
    });
    QFile file("G:/IceCould/Total/Software/Code/Sport/data/score.ini");
    file.open(QIODevice::ReadOnly);
    QByteArray array = file.readAll();
    rankEdit->setText(array);
    /*char* data = array.data();
    //数据处理
    int i = 0;//字符串位数
    int j = 0;//结构位数
    while(data[i] != '#'){
        if(data[i] == '$'){//读取名字
            i++;
            int k = 0;//名字位数
            i++;
            while(data[i] != '^'){
                paiming[j].name[k++] = data[i++];
            }
            k = 0;
            i++;
            while(data[i] != '*'){
                paiming[j].rank[k++] = data[i++];
            }
            i++;
            i++;
            j++;
        }
        else break;
    }
    qDebug()<<paiming[0].rank;*/
}
