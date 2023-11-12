
#ifndef _BUTTON_H_
#define _BUTTON_H_
#include "Arduino.h"

class Button
{
private:
    bool isPress;
    bool hasPress;
    unsigned long currentTime;
    int  keyPressTime;
    //Settings
public:
    int pin;                      //输入引脚
    int normalVoltage;            //常态电平
    bool isPullUp;                //是否使用内部上拉
    //Property
    bool currentState;
    bool isClick;
    bool hasClick;
    //Actions

    //Override:
    void init(int pin);
    void setup();
    void setKeyPressTime(int value);
    void update();
    bool click();
    bool press();

    
    Button();
};
#endif