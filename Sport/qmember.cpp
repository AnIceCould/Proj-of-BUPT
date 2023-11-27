#include "qmember.h"

QMember::QMember(const QString &fileName):QItem(fileName)
{

}

void QMember::advance(int phase){//时钟检测ai运动
    int pos;
	if(this->ballpath == 1){//下
		pos = this->y()+125;
		if(pos > theY){
            if(gamemode == 3 || gamemode == 2 || (gamemode == 1 && numrand < 9))
			pos--;
            if(gamemode == 3 || (gamemode == 2 && numrand < 2))
				if(pos - theY > 1) pos = pos - 2;
		}
		else {
            if(gamemode == 3 || gamemode == 2 || (gamemode == 1 && numrand < 9))
			pos++;
            if(gamemode == 3 || (gamemode == 2 && numrand < 2))
				if(theY - pos > 1) pos = pos + 2;
		}
		this->setY(pos - 125);
	}
	else if(this->ballpath == 2){//中
		numrand = QRandomGenerator::global()->generateDouble()*10;
		pos = this->y();
		if(pos > theY){
            if(gamemode == 3 || gamemode == 2 || (gamemode == 1 && numrand < 9))
			pos--;
            if(gamemode == 3 || (gamemode == 2 && numrand < 2))
				if(pos - theY > 1) pos = pos - 2;
		}
		else {
            if(gamemode == 3 || gamemode == 2 || (gamemode == 1 && numrand < 9))
			pos++;
            if(gamemode == 3 || (gamemode == 2 && numrand < 2))
				if(theY - pos > 1) pos = pos + 2;
		}
		this->setY(pos);
	}
	else if(this->ballpath == 3){//上
		pos = this->y()-125;
		if(pos > theY){
            if(gamemode == 3 || gamemode == 2 || (gamemode == 1 && numrand < 9))
			pos--;
            if(gamemode == 3 || (gamemode == 2 && numrand < 2))
				if(pos - theY > 1) pos = pos - 2;
		}
		else {
            if(gamemode == 3 || gamemode == 2 || (gamemode == 1 && numrand < 9))
			pos++;
            if(gamemode == 3 || (gamemode == 2 && numrand < 2))
				if(theY - pos > 1) pos = pos + 2;
		}
		this->setY(pos + 125);
	}
}
