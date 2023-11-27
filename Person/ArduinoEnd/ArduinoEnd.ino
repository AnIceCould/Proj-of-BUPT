#include "ESP8266.h"
#include "SoftwareSerial.h"

//配置ESP8266WIFI设置
#define SSID "wwworld"    //WIFI名称
#define PASSWORD "10011001"//WIFI密码
#define HOST_NAME "api.heclouds.com"  //API主机名称
#define DEVICE_ID ""       //OneNet设备ID
#define HOST_PORT (80)                //API端口
#define INTERVAL_SENSOR 100000 //发送时间间隔
String APIKey = ""; //与设备绑定的APIKey

//定义ESP8266 TX接D3 RX接D2
SoftwareSerial mySerial(3, 2);
ESP8266 wifi(mySerial);

//定义结构数组
struct modes{
  bool type;//当前状态
  bool last;//上一次状态
  unsigned long nows;//状态改变时间
  bool cando;//人数可否改变
};
modes per[2];//分别对应两个传感器：0为10口、1为11口

//三端通讯数据
int maxp = 0;//规定最大人数
int person = 0;//房间内人数


/*
以下为初始化代码
*/
void setup()
{
  mySerial.begin(115200); //初始化软串口
  Serial.begin(9600);     //初始化串口
  pinMode(10, INPUT);//10号为室内的传感器
  pinMode(11, INPUT);//11号为室外的传感器
  per[0].last = 0;
  per[1].last = 0;
  wifi.setOprToStation();//ESP8266初始化
  wifi.joinAP(SSID, PASSWORD);//ESP8266接入WIFI
  mySerial.println("AT+UART_CUR=9600,8,1,0,0");
  mySerial.begin(9600);
  delay(10000);//初始化时间（避免误操作）
}
unsigned long net_time1 = millis(); //数据上传服务器时间
void loop(){
  
/*
以下为传感器代码
*/
  //循环读取当前传感器状态
  if(digitalRead(10)==HIGH) {
    per[0].type = 1;//高
  } else {
    per[0].type = 0;//低
  }
  if(digitalRead(11)==HIGH) {
    per[1].type = 1;
  } else {
    per[1].type = 0;
  }
  //判断是否为新出现的信号
  for(int i = 0;i<2;i++){//使用循环直接判断两个传感器状态
    if(per[i].last == 0 && per[i].type == 1){//上一次为低而这次为高（代表有人经过）
      per[i].cando = 1;//可以改变
      per[i].nows = millis();//取状态改变的时间
      per[i].last = 1;//上一次的状态变成高
    }
    if(per[i].last == 1 && per[i].type == 0){//上一次为高而这次为低（代表经过的人离开）
      per[i].last = 0;//上一次的状态变成低
      per[i].cando = 0;//不可改变（排除干扰信号）
    }
  }
  //判断两个传感器信号先后

    
  if(per[0].cando == 1&&per[1].cando == 1){//两个传感器均要求可以改变人数（有人进出）
    if(per[0].nows<per[1].nows){
      person--;//10号传感器先收到信号（有人出门）
    }
    else {
      person++;//11号传感器先收到信号（有人进门）
    }
    per[0].cando = 0;
    per[1].cando = 0;
  }
/*
以下为processing通信代码
 */
  Serial.write(person);
  maxp = Serial.read(); 
/*
以下为延时代码
*/
  if (net_time1 > millis()){
    net_time1 = millis();
  }

  if (millis() - net_time1 > INTERVAL_SENSOR){//发送数据时间间隔
    if (wifi.createTCP(HOST_NAME, HOST_PORT)) {//建立TCP连接，如果失败，不能发送该数据
/*
以下为发送代码
*/
      //拼接发送data字段字符串
      String jsonToSend = "{\"Number\":";
      jsonToSend += "\"" + (String)person + "\"";
      jsonToSend += ",\"Max\":";
      jsonToSend += "\"" + (String)maxp + "\"";
      jsonToSend += "}";

      //拼接POST请求字符串
      String postString = "POST /devices/";
      postString += DEVICE_ID;
      postString += "/datapoints?type=3 HTTP/1.1";
      postString += "\r\n";
      postString += "api-key:";
      postString += APIKey;
      postString += "\r\n";
      postString += "Host:api.heclouds.com\r\n";
      postString += "Connection:close\r\n";
      postString += "Content-Length:";
      postString += jsonToSend.length();
      postString += "\r\n";
      postString += "\r\n";
      postString += jsonToSend;
      postString += "\r\n";
      postString += "\r\n";
      postString += "\r\n";

      const char *postArray = postString.c_str(); //将str转化为char数组

      wifi.send((const uint8_t *)postArray, strlen(postArray)); //send发送命令
      wifi.releaseTCP();//释放TCP连接
      postArray = NULL; //清空数组，等待下次传输数据
    }
    net_time1 = millis();
  }
}
