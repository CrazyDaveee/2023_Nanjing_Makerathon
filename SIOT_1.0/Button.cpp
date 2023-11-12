#include "Button.h"

void Button::init(int pin)
{
    this->pin = pin;
    this->setup();
}

void Button::setup()
{
    if(isPullUp)
    {
        pinMode(pin, INPUT_PULLUP);
    }
    else
    {
        pinMode(pin, INPUT);

    }
}
void Button::update()
{
    unsigned long timeInterval = 0;
    if((digitalRead(pin)!=normalVoltage)&&!isPress)
    {
        isPress = true;
        currentTime = millis();
    }
    else if (isPress)
    {
        timeInterval = millis()-currentTime;
        if (timeInterval > keyPressTime)
        {
            if(digitalRead(pin)!=normalVoltage)
            {
                hasPress = true;
            }
            else
            {
                currentState = false;
                isPress = false;
                hasPress = false;
                hasClick = false;
            }
        }
        else if(timeInterval < keyPressTime && timeInterval>=10)
        {
            if(digitalRead(pin)!=normalVoltage)
            {
                currentState = true;
            }
            else
            {
                currentState = false;
                isPress = false;
            }
        }
    }
    isClick = false;
    if (currentState) {
        hasClick = true;
    }
    else if(hasClick) {
        isClick = true;
        hasClick = false;
    }
}

bool Button::click()
{
    if(isClick)
    {
        isClick = false;
        return true;
    }
    return false;
}

bool Button::press()
{
    if(hasPress)
        return true;
    else
        return false;
}

void Button::setKeyPressTime(int value)
{
    this->keyPressTime = value;
}

Button::Button()
{
    isPress = false;
    currentTime = 0;
    hasPress = false;
    normalVoltage = 0;
    isPullUp = true;
    currentState = false;
    isClick = false;
    hasClick = false;
    keyPressTime = 1000;
}

