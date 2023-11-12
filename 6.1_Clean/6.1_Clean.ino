#include <DFRobot_LiquidCrystal_I2C.h>
#include <ArduinoSort.h>
#include <DFRobot_HuskyLens.h>
#include <DFRobot_Servo.h>
#include <DFRobot_NeoPixel.h>
#include <DFRobot_URM10.h>
#include <DFRobot_SSD1306_I2C.h>
// 创建对象
DFRobot_SSD1306_I2C oled12864;
DFRobot_HuskyLens huskylens;//                 |-.
Servo servo_11;//                               |-'
Servo servo_12;
DFRobot_NeoPixel neoPixel_8;
DFRobot_URM10 urm10;

//创建变量
int Hyper_Wave[4];
int Sorted[4];
short dic[200];

//函数声明
void Sorrt_And_Change_The_Light();
void cleaner()
{
  oled12864.setCursorLine(1);
	  oled12864.printLine("                 ");
    oled12864.setCursorLine(2);
	  oled12864.printLine("                  ");
    oled12864.setCursorLine(3);
	  oled12864.printLine("             ");
    oled12864.setCursorLine(4);
	  oled12864.printLine("                  ");
}
// 主程序开始
void setup() {
  //串口设置波特率
  Serial.begin(9600);
  //oled
	oled12864.begin(0x3c);
  oled12864.setCursorLine(1);
  oled12864.printLine("Hello,CrazyDave!");
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
  oled12864.setCursorLine(2);
	oled12864.printLine("Testing screen...");
  delay(1000);
  cleaner();
  Sorrt_And_Change_The_Light();
  delay(1000);
  cleaner();
  oled12864.setCursorLine(1);
	oled12864.printLine("OK!");
  delay(1000);
  cleaner();
  //初始化完成
  Serial.println("hello");
	oled12864.setCursorLine(1);
	oled12864.printLine("Setup successful");
  delay(1000);
  oled12864.setCursorLine(2);
	oled12864.printLine("Programme will");
  oled12864.setCursorLine(3);
	oled12864.printLine("start in 3 sec!");
  delay(3000);
  //OLED进入状态
  oled12864.setCursorLine(1);
	oled12864.printLine("Itm1 health:"+String((10-Hyper_Wave[0])*10)+"%");
  oled12864.setCursorLine(2);
	oled12864.printLine("Itm2 health:"+String((10-Hyper_Wave[1])*10)+"%");
  oled12864.setCursorLine(3);
	oled12864.printLine("Itm3 health:"+String((10-Hyper_Wave[2])*10)+"%");
  oled12864.setCursorLine(4);
	oled12864.printLine("Itm4 health:"+String((10-Hyper_Wave[3])*10)+"%");
}
void loop() {
  //ID:0
	if (urm10.getDistanceCM(2, 3)<6) {
    Hyper_Wave[0]++;
    Sorrt_And_Change_The_Light();
    while (urm10.getDistanceCM(2, 3)<6) {}//trig2 echo3 绿2蓝3
  }
  //ID:1
	if (analogRead(A1)<100) {
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
        oled12864.setCursorLine(2);
	      oled12864.printLine("WARNING:");
        oled12864.setCursorLine(3);
	      oled12864.printLine("Item"+String(Sorted[i])+" need to be");
        oled12864.setCursorLine(4);
	      oled12864.printLine("CHECKED!");
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
    oled12864.setCursorLine(1);
	oled12864.printLine("Itm1 health:"+String((10-Hyper_Wave[0])*10)+"%");
  oled12864.setCursorLine(2);
	oled12864.printLine("Itm2 health:"+String((10-Hyper_Wave[1])*10)+"%");
  oled12864.setCursorLine(3);
	oled12864.printLine("Itm3 health:"+String((10-Hyper_Wave[2])*10)+"%");
  oled12864.setCursorLine(4);
	oled12864.printLine("Itm4 health:"+String((10-Hyper_Wave[3])*10)+"%");
    // //遍历数组并测试
    // for(int i = 0;i<4;i++)
    // {
    //   Serial.println(Sorted[i]);
    // }
}