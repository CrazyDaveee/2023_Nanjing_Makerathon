#include <SoftwareSerial.h>
#include "Obloq.h"
#include "Button.h"
//5432
Button button;
//设置软串口
SoftwareSerial softSerial(2,3);


//Iot设备Topic:HkfVZ9BBz
String buttonMessage = "";

void setup()
{
    softSerial.begin(9600);
    //连接WIFI  参数：wifiSsid,WifiPwd
    softSerial.print("|2|1|Test_1|1145141919810\r");
    //连接SIOT平台 参数：SIOT_IP,端口(1883),账号(siot),i密码(dfrobot)
    softSerial.print("|4|1|1|192.168.56.1|1883|siot|dfrobot|\r");
    //订阅 参数:|4|1|2|&YOUR_TOPIC|\r
    softSerial.print("|4|1|2|BOARD_1_MAIN/count_0|\r");
  // softSerial.print("|4|1|2|BOARD_1_MAIN/count_1|\r");
  // softSerial.print("|4|1|2|BOARD_1_MAIN/count_2|\r");
  // softSerial.print("|4|1|2|BOARD_1_MAIN/count_3|\r");
  // softSerial.print("|4|1|2|BOARD_1_MAIN/msg|\r");
}

void loop()
{
  // softSerial.print("|4|1|5|\r");
  delay(100);
  //发送
    softSerial.print("|4|1|3|BOARD_1_MAIN/count_0|6|\r");
    // button.update();
    // if(button.click())
    // {
    //     olq.publish(devTopic,buttonMessage); //向Iot设备发送消息
    //     if(buttonMessage == "1")
    //         buttonMessage = "0";
    //     else
    //         buttonMessage = "1";
    // }
}