#include "qtext.h"

QText::QText(int mode)
{
    textmode = mode;
}
void QText::advance(int phase){//更新
    if(textmode == 0){
        if(myScore == 0){
            if(aiScore == 0) this->setText("得分:0-0");
            else if(aiScore == 1) this->setText("得分:0-1");
            else if(aiScore == 2) this->setText("得分:0-2");
            else if(aiScore == 3){
                this->setText("得分:0-3\n你输了！\nEnter键开始下一局\nEsc结束游戏");
                winorlose(0);
            }
        }
        if(myScore == 1){
            if(aiScore == 0) this->setText("得分:1-0");
            else if(aiScore == 1) this->setText("得分:1-1");
            else if(aiScore == 2) this->setText("得分:1-2");
            else if(aiScore == 3){
                this->setText("得分:1-3\n你输了！\nEnter键开始下一局\nEsc结束游戏");
                winorlose(0);
            }
        }
        if(myScore == 2){
            if(aiScore == 0) this->setText("得分:2-0");
            else if(aiScore == 1) this->setText("得分:2-1");
            else if(aiScore == 2) this->setText("得分:2-2");
            else if(aiScore == 3){
                this->setText("得分:2-3\n你输了！\nEnter键开始下一局\nEsc结束游戏");
                winorlose(0);
            }
        }
        if(myScore == 3){
            if(aiScore == 0){
                this->setText("得分:3-0\n你赢了！\nEnter键开始下一局\nEsc结束游戏");
                winorlose(1);
            }
            else if(aiScore == 1){
                this->setText("得分:3-1\n你赢了！\nEnter键开始下一局\nEsc结束游戏");
                winorlose(1);
            }
            else if(aiScore == 2){
                this->setText("得分:3-2\n你赢了！\nEnter键开始下一局\nEsc结束游戏");
                winorlose(1);
            }
        }
    }
    else if(textmode == 1){
        if(gamemode == 1){
            this->setText("难度为：简单");
            this->setBrush(Qt::green);
            showup();
        }
        else if(gamemode == 2){
            this->setText("难度为：普通");
            this->setBrush(Qt::yellow);
            showup();
        }
        else if(gamemode == 3){
            this->setText("难度为：困难");
            this->setBrush(Qt::red);
            showup();
        }
    }

}

void QText::winorlose(bool wol){//赢或输
    if(wol && outtime == 0){//赢
        //类型转换
        //时间
        outtime = gametime/100;
        QString str1;
        str1 = QString::number(outtime);
        char* ch1;
        QByteArray ba1 = str1.toLatin1();
        ch1=ba1.data();
        //名字
        QString str2;
        str2 = username;
        char* ch2;
        QByteArray ba2 = str2.toLatin1();
        ch2=ba2.data();
        //写文件
        QFile file("G:/IceCould/Total/Software/Code/Sport/data/score.ini");//写入的文件
        file.open(QIODevice::Append);
        //file.write("$");
        file.write(ch2);
        file.write(" ");
        //file.write("^");
        file.write(ch1);
        file.write(" ");
        if(gamemode == 1) file.write("Easy");
        else if(gamemode == 2) file.write("Normal");
        else if(gamemode == 3) file.write("Hard");
        file.write("\n");
        file.close();
    }
    else{//输

    }
    this->setPos(500,100);
}

void QText::showup(){//显示
    if(timenow >= 0){
        if(timenow <= 100){
            this->setPos(this->x(),this->y()+0.4);
            timenow++;
        }
        else if(timenow <= 600){
            timenow++;
        }
        else if(timenow <= 800){
            this->setPos(this->x(),this->y()-0.2);
            timenow++;
        }
        else timenow = -1;
    }
}
