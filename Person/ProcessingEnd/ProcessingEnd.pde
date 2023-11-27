import controlP5.*;
import processing.serial.*;
ControlP5 cp5;
Serial port;

int maxp = 0;
int num = 0;

void setup(){
  size(320,600);
  port=new Serial(this,"COM5",9600);//创建一个新的串口
  //创建按钮
  cp5=new ControlP5(this);
  cp5.addButton("maxAddOne").setPosition(100,50).setSize(100,50);//最大人数加一按钮
  cp5.addButton("maxSubtractOne").setPosition(100,110).setSize(100,50);//最大人数减一按钮
}

void draw(){
  textSize(15);//文本字体大小
  background(#ffffff);//背景颜色设置
  fill(#000000);
  //创建标签
  text("Now Number:", 50,280);
  text(num,160,300);
  text("Max Number:",50,320);
  text(maxp,160,340);
  //读入当前人数数据
  if(port.available()>0){
    num=port.read();
  }
  port.write(maxp);
}

//最大人数加一
void maxAddOne(){
  maxp++;
}

//最大人数减一
void maxSubtractOne(){
  maxp--;
}
