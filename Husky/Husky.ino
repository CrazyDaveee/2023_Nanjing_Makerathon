#include <DFRobot_HuskyLens.h>
#include <SoftwareSerial.h>
#include <DFRobot_Servo.h>
DFRobot_HuskyLens huskylens;
Servo servo_11;//                               |-'
Servo servo_12;
SoftwareSerial softSerial(2,3);
void setup(){
  huskylens.beginI2CUntilSuccess();
  huskylens.writeAlgorithm(ALGORITHM_FACE_RECOGNITION);
  huskylens.forgetLearn();
  servo_11.attach(11);//________________________________________更改接口
	servo_12.attach(12);
}
void loop() {
  // put your main code here, to run repeatedly:
  // softSerial.print("|4|1|3|CrazyDave/HUSKYLENS|6|\r");
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
        servo_12.angle(abs((map(huskylens.readBlockParameter(i).yCenter, 0, 240, 150, 90))));//__________
      }
    }
    if(!flag)
    {
      huskylens.learnOnece((tmp + 1));
      // huskylens.takePhotoToSDCard();
	  }
  }
	
}
