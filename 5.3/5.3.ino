#include <DFRobot_LiquidCrystal_I2C.h>
#include <ArduinoSort.h>
#include <DFRobot_HuskyLens.h>
#include <DFRobot_Servo.h>
#include <DFRobot_NeoPixel.h>
#include <DFRobot_URM10.h>
#include <DFRobot_SSD1306_I2C.h>
//读数字引脚n：digitalRead(n)
//串口输出初始化:Serial.begin(9600);
//串口输出：Serial.println(n);
//反向sortarray:sortArrayReverse(n,n);
//正向sortarray:sortArray(n,n);

//____________________________________________更改接口
// DFRobot_LiquidCrystal_I2C lcd1602;//           |
DFRobot_HuskyLens huskylens;//                 |-.
Servo servo_11;//                               |-'
Servo servo_12;
DFRobot_NeoPixel neoPixel_8;
DFRobot_URM10 urm10;
DFRobot_SSD1306_I2C oled12864;//                               |
//____________________________________________更改接口
int Hyper_Wave[4];
int Sorted[4];
short dic[200];

void Sorrt_And_Change_The_Light();

void setup() {
  neoPixel_8.begin(8, 7);
  oled12864.begin(0x3c);
  // lcd1602.begin(0x3E);
  Serial.begin(9600);
  huskylens.beginI2CUntilSuccess();
  huskylens.writeAlgorithm(ALGORITHM_FACE_RECOGNITION);
  Serial.println("hello");
  huskylens.forgetLearn();
  servo_11.attach(11);//________________________________________更改接口
	servo_12.attach(12);//________________________________________更改接口
  int i = 3;
  while(i>=0)
  {
    Hyper_Wave[i]=0;
    i--;
  }
  Sorrt_And_Change_The_Light();
}

void loop() {
  oled12864.setCursorLine(1);
	  oled12864.printLine(String(1));
    oled12864.setCursorLine(2);
	  oled12864.printLine(String(2));
    oled12864.setCursorLine(3);
	  oled12864.printLine(String(3));
    oled12864.setCursorLine(4);
	  oled12864.printLine(String(4));
	if (urm10.getDistanceCM(2, 3)<6) {
    Hyper_Wave[0]++;
    Sorrt_And_Change_The_Light();
    
    while (urm10.getDistanceCM(2, 3)<6) {}//trig2 echo3 绿2蓝3
	}

	if (analogRead(A1)<100) {
    Hyper_Wave[1]++;
    Sorrt_And_Change_The_Light();
    
    while (analogRead(A1)<100) {}
	}

	// servo_11.angle(abs(114));//______________
  // servo_12.angle(abs(114));//__________
	if (!digitalRead(4)) {
    Hyper_Wave[2]++;
    Sorrt_And_Change_The_Light();
     
    while (!digitalRead(4)) {}
	}
  if (!digitalRead(5)) {/////////////////////////////////////////////////Changable
    Hyper_Wave[3]++;
    Sorrt_And_Change_The_Light();
    
    while (!digitalRead(5)) {}
	}////////////////////////////////////////////////////////////////////////////
  huskylens.request();
  if (huskylens.isAppearDirect(HUSKYLENSResultBlock)) {
    int tmp=huskylens.readLearnedIDCount();
    bool flag = 0;
    for(int i = 1;i<=tmp;i++)
    {
      if(huskylens.isAppear(i,HUSKYLENSResultBlock))
      {
        flag=1;
        //舵机
        Serial.println(String(abs((map(huskylens.readBlockParameter(i).xCenter, 0, 320, 180, 0)))));
        servo_11.angle(abs((map(huskylens.readBlockParameter(i).xCenter, 0, 320, 180, 0))));//______________
        servo_12.angle(abs((map(huskylens.readBlockParameter(i).yCenter, 0, 240, 90, 150))));//__________
      }
    }
    if(!flag)
    {
      huskylens.learnOnece((tmp + 1));
      huskylens.takePhotoToSDCard();
	  }
  }
	

  if (digitalRead(13)) {
      Hyper_Wave[map(analogRead(A0), 0, 1023, 0, 4)]=0;
      Sorrt_And_Change_The_Light();
	}
	// lcd1602.printLine(uint32_t(1), (String(Hyper_Wave[0])+String(Hyper_Wave[1])));
  // lcd1602.printLine(uint32_t(2), (String(Hyper_Wave[2])+String(Hyper_Wave[3])));
}
// void Turn_the_light_for_fixer_on()
// {
  
// }
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
    // neoPixel_8.clear();
    // neoPixel_8.setRangeColor(0, 3, 0x00FF00);
    for(int i = 0;i<4;i++)
    {
      if(Hyper_Wave[Sorted[i]]>5)
      {
        digitalWrite(6, HIGH);//red
        digitalWrite(7, LOW);
        
        neoPixel_8.setRangeColor(Sorted[i], Sorted[i], 0xFF0000);//red
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
	  oled12864.printLine(String(Hyper_Wave[0]));
    oled12864.setCursorLine(2);
	  oled12864.printLine(String(Hyper_Wave[1]));
    oled12864.setCursorLine(3);
	  oled12864.printLine(String(Hyper_Wave[2]));
    oled12864.setCursorLine(4);
	  oled12864.printLine(String(Hyper_Wave[3]));
    // //遍历数组并测试
    // for(int i = 0;i<4;i++)
    // {
    //   Serial.println(Sorted[i]);
    // }
}