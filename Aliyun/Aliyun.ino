#include <SoftwareSerial.h>
#include "Obloq.h"
#include "Button.h"
#define WIFI_SSID         "TP-LINK_lzk"
#define WIFI_PASSWD       "liuzekai1209"

// {
//   "ProductKey": "k0gnsDc6WgS",
//   "DeviceName": "WAkTMGi1bWMeUXa25UDl",
//   "DeviceSecret": "eca8d42f920e434efba9a0c990bfbeff"
// }
#define PRODUCT_KEY       "k0gnsDc6WgS"
#define DEVICE_NAME       "WAkTMGi1bWMeUXa25UDl"
#define DEVICE_SECRET     "eca8d42f920e434efba9a0c990bfbeff"
#define REGION_ID         "cn-shanghai"
#define MQTT_SERVER       PRODUCT_KEY ".iot-as-mqtt." REGION_ID ".aliyuncs.com"
#define MQTT_PORT         1883
#define MQTT_USRNAME      DEVICE_NAME "&" PRODUCT_KEY

#define CLIENT_ID         "00001|securemode=3,signmethod=hmacsha1|"//这里使用技小新可以生成，注意密码和密钥一定要对否则连不上MQTT    "FESA234FBDS24|securemode=3,timestamp=789,signmethod=hmacsha1|"
#define MQTT_PASSWD       "D33DB9F62EAAB68954E4EBCA481ED9FFB1BDAC21"

#define ALINK_BODY_FORMAT         "{\"id\":\"ESP8266\",\"version\":\"1.0\",\"method\":\"thing.event.property.post\",\"params\":%s}"
Button button;
SoftwareSerial softSerial(10,11);
//生成OBLOQ对象，参数：串口指针，wifiSsid,WifiPwd,iotId,iotPwd
//Broker Address：iot-060a8ig5.mqtt.iothub.aliyuncs.com
// Broker Port	  ：1883
// Client ID     ：00001|securemode=3,signmethod=hmacsha1|
// User Name:WAkTMGi1bWMeUXa25UDl&k0gnsDc6WgS
// password:F04E282D9E92364B9C67AB2B946E6EACF0BEEBF1
//pwd  D33DB9F62EAAB68954E4EBCA481ED9FFB1BDAC21
//Iot设备Topic:HkfVZ9BBz
const String devTopic = "eMSaxuVSg";
String buttonMessage = "";

void setup()
{
    button.init(2);
    softSerial.begin(9600);
    softSerial.print("|2|1|TP-LINK_lzk,liuzekai1209|\r");
    softSerial.print("|4|1|1|"MQTT_SERVER"|1883|"MQTT_USRNAME"|"MQTT_PASSWD"|\r");
    softSerial.print("|4|1|2|/sys/k0gnsDc6WgS/WAkTMGi1bWMeUXa25UDl/thing/service/property/set|\r");
    softSerial.print("|4|1|2|/sys/k0gnsDc6WgS/WAkTMGi1bWMeUXa25UDl/thing/service/property/post|\r");
}

void loop()
{

    softSerial.print("|4|1|3|/sys/k0gnsDc6WgS/WAkTMGi1bWMeUXa25UDl/thing/event/property/post|\r");
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