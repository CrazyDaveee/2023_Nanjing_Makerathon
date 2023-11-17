#include <DFRobot_LiquidCrystal_I2C.h>
#include <ArduinoSort.h>
#include <DFRobot_HuskyLens.h>
#include <DFRobot_Servo.h>
#include <DFRobot_NeoPixel.h>
#include <DFRobot_URM10.h>
#include <DFRobot_SSD1306_I2C.h>
// 创建对象
DFRobot_LiquidCrystal_I2C lcd1602;
DFRobot_HuskyLens huskylens;//                 |-.
Servo servo_11;//                               |-'
Servo servo_12;
DFRobot_NeoPixel neoPixel_8;
DFRobot_URM10 urm10;
SoftwareSerial softSerial(8,9);
//创建变量
int Hyper_Wave[4];
int Sorted[4];
short dic[200];

//函数声明
void Sorrt_And_Change_The_Light();
void cleaner()
{
  lcd1602.printLine(uint32_t(1),"                         ");
  lcd1602.printLine(uint32_t(2),"                         ");
}
// 主程序开始
void setup() {
  //OBLOQ
  softSerial.begin(9600);
  softSerial.print("|1|3|2000|\r");
  //连接WIFI  参数：wifiSsid,WifiPwd
  softSerial.print("|2|1|CrazyDave,1145141919810|\r");
  // //连接SIOT平台 参数：SIOT_IP,端口(1883),账号(siot),i密码(dfrobot)
  softSerial.print("|4|1|1|10.78.195.79|1883|siot|dfrobot|\r");
  // //订阅 参数:|4|1|2|&YOUR_TOPIC|\r
  softSerial.print("|4|1|BOARD_1_MAIN/count|\r");
  delay(100);
  softSerial.print("|4|1|BOARD_1_MAIN/msg|\r");
  delay(100);
  //oled
	lcd1602.begin(0x3E);
  lcd1602.printLine(uint32_t(1),"Hello,CrazyDave");
  lcd1602.printLine(uint32_t(2),"Setup...");
  delay(1000);
  //灯带
  neoPixel_8.begin(8, 7);
  //二哈
  // huskylens.beginI2CUntilSuccess();
  // huskylens.writeAlgorithm(ALGORITHM_FACE_RECOGNITION);
  // huskylens.forgetLearn();
  //伺服电机
  servo_11.attach(11);//________________________________________更改接口
	servo_12.attach(12);//________________________________________更改接口
  //数组清零
  int i = 3;
  while(i>=0)
  {
    Hyper_Wave[i]=0;
    i--;
  }
  cleaner();
  lcd1602.printLine(uint32_t(1),"Testing...");
  delay(500);
  cleaner();
  Sorrt_And_Change_The_Light();
  delay(500);
  cleaner();
  lcd1602.printLine(uint32_t(1),"OK!");
  delay(1000);
  cleaner();
  //初始化完成
  lcd1602.printLine(uint32_t(1),"https://github.c");
	lcd1602.printLine(uint32_t(2),"om/CrazyDaveee");
  while(!digitalRead(10)){ }

  //LCD进入状态
  lcd1602.printLine(uint32_t(1),"Itm1:"+String((10-Hyper_Wave[0])*10)+"%");
	lcd1602.printLine(uint32_t(2),"Itm2:"+String((10-Hyper_Wave[1])*10)+"%");
  
  // lcd1602.printLine(uint32_t(1),"Itm3:"+String((10-Hyper_Wave[2])*10)+"%");
	// lcd1602.printLine(uint32_t(2),"Itm4:"+String((10-Hyper_Wave[3])*10)+"%");
  
}
void loop() {
  //ID:0
	if (urm10.getDistanceCM(2, 3)<6) {
    Hyper_Wave[0]++;
    Sorrt_And_Change_The_Light();
    while (urm10.getDistanceCM(2, 3)<6) {}//trig2 echo3 绿2蓝3
  }
  //ID:1
	if (analogRead(A1)<10) {
    Hyper_Wave[1]++;
    Sorrt_And_Change_The_Light();
    
    while (analogRead(A1)<100) {}
	}
  //ID:2
	if (!digitalRead(4)) {
    Hyper_Wave[2]++;
    Sorrt_And_Change_The_Light();
     
    while (!digitalRead(4)) {}
	}
  //ID:3
  if (!digitalRead(5)) {
    Hyper_Wave[3]++;
    Sorrt_And_Change_The_Light();
    
    while (!digitalRead(5)) {}
	}
  //CLEAN
  if (digitalRead(13)) {
    Hyper_Wave[map(analogRead(A0), 0, 1023, 0, 4)]=0;
    Sorrt_And_Change_The_Light();
	}
  if(analogRead(A2)>500)
    {
      lcd1602.printLine(uint32_t(1),"Itm1:"+String((10-Hyper_Wave[0])*10)+"%");
	    lcd1602.printLine(uint32_t(2),"Itm2:"+String((10-Hyper_Wave[1])*10)+"%");
    }
    else
    {
      lcd1602.printLine(uint32_t(1),"Itm3:"+String((10-Hyper_Wave[2])*10)+"%");
	    lcd1602.printLine(uint32_t(2),"Itm4:"+String((10-Hyper_Wave[3])*10)+"%");
    }
}
void Sorrt_And_Change_The_Light()
{
  //拷贝数组并将数组下标和内容记录到dic数组
    for(int i = 0;i<4;i++){
      Sorted[i]=Hyper_Wave[i];
      dic[Hyper_Wave[i]]=i;
    }
    //排序
    sortArrayReverse(Sorted, 4);
    //将排序后数组与排序前原始数组下标对应
    for(int i = 0;i<4;i++){
      Sorted[i]=dic[Sorted[i]];
    }
    neoPixel_8.clear();
    neoPixel_8.setRangeColor(0, 3, 0x00FF00);
    for(int i = 0;i<4;i++)
    {
      if(Hyper_Wave[Sorted[i]]>=10)
      {
        digitalWrite(6, HIGH);//red
        digitalWrite(7, LOW);
        neoPixel_8.setRangeColor(Sorted[i], Sorted[i], 0xFF0000);//red
        cleaner();
        softSerial.print("|4|1|3|BOARD_1_MAIN/msg|Itm"+String(Sorted[i])+" LOW HEALTH!|\r");
        lcd1602.printLine(uint32_t(1),"WARNING!");
        lcd1602.printLine(uint32_t(2),"Itm"+String(Sorted[i])+" LOW HEALTH!");
        delay(3000);
        cleaner();
        break;
      }
      else
      {
        digitalWrite(6, LOW);
        digitalWrite(7, HIGH);
        neoPixel_8.setRangeColor(Sorted[i], Sorted[i],0x00FF00);//green
      }
    }
    softSerial.print("|4|1|3|BOARD_1_MAIN/count|"+String(Hyper_Wave[0]+Hyper_Wave[1]+Hyper_Wave[2]+Hyper_Wave[3])+"|\r");
    
    // //遍历数组并测试
    // for(int i = 0;i<4;i++)
    // {
    //   Serial.println(Sorted[i]);
    // }
}