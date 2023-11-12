/*!
 * MindPlus
 * uno
 *
 */
#include <SimpleList.h>
#include <DFRobot_URM10.h>
#include <DFRobot_Servo.h>
#include <DFRobot_HuskyLens.h>
#include <DFRobot_LiquidCrystal_I2C.h>
#include <DFRobot_IRremote.h>
#define ultrasonic_wave1 

// 动态变量
volatile float     mind_n_RenJiShu, mind_n_tmp1, mind_n_ChaoShengBo1, mind_n_ChaoShengBo2,
                   mind_n_ChaoShengBo3, mind_n_ChaoShengBo4, mind_n_tmp2;
SimpleList<String> mind_l_Queue, mind_l_TongPaiXu, mind_l_sorted;
// 函数声明
void DF_HuskyLensRenTiGenZong();
void DF_ChuShiHua();
void DF_Sort();
void DF_RenLiuJianCe__JuLi(float mind_n_distance);
void DF_BianLisortedBingXianShiZaiChuanKouZhong();
void DF_Get();
void DF_BianLiQueueBingXianShiZaiChuanKouZhong();
void DF_ChaoShengBoShuJuCeShi();
// 创建对象
DFRobot_HuskyLens         huskylens;
Servo                     servo_11;
Servo                     servo_10;
DFRobot_LiquidCrystal_I2C lcd1602;
DFRobot_URM10             urm10;


// 主程序开始
void setup() {
	Serial.begin(9600);
	servo_11.attach(11);
	servo_10.attach(10);
  lcd1602.begin(0x3E);
	mind_l_Queue.clear();
	mind_l_TongPaiXu.clear();
	mind_l_Queue.push_back("0");
	mind_l_Queue.push_back("0");
	mind_l_Queue.push_back("0");
	mind_l_Queue.push_back("0");
	mind_n_tmp1 = 0;
	mind_n_ChaoShengBo1 = 0;
	mind_n_ChaoShengBo2 = 0;
	mind_n_ChaoShengBo3 = 0;
	mind_n_ChaoShengBo4 = 0;
	mind_n_ChaoShengBo2 = 0;
	mind_n_ChaoShengBo3 = 0;
	DF_ChuShiHua();
}
void loop() {
	lcd1602.printLine(uint32_t(1), (String(mind_n_ChaoShengBo1) + String((String("     ") + String(mind_n_ChaoShengBo2)))));
	lcd1602.printLine(uint32_t(2), (String(mind_n_ChaoShengBo3) + String((String("     ") + String(mind_n_ChaoShengBo4)))));
	mind_n_ChaoShengBo1 = (urm10.getDistanceCM(3, 2));
	mind_n_ChaoShengBo2 = (urm10.getDistanceCM(5, 4));
	mind_n_ChaoShengBo3 = (urm10.getDistanceCM(7, 6));
	mind_n_ChaoShengBo4 = (urm10.getDistanceCM(9, 8));
	if ((mind_n_ChaoShengBo1<=10)) {
		mind_l_Queue.replace(1-1, (String(((String(mind_l_Queue[1-1]).toInt()) + 1))));
		DF_Sort();
		while (!(!((urm10.getDistanceCM(3, 2))<=10))) {}
	}
	if ((mind_n_ChaoShengBo2<=10)) {
		mind_l_Queue.replace(2-1, (String(((String(mind_l_Queue[2-1]).toInt()) + 1))));
		DF_Sort();
		while (!(!((urm10.getDistanceCM(5, 4))<=10))) {}
	}
	if ((mind_n_ChaoShengBo3<=10)) {
		mind_l_Queue.replace(3-1, (String(((String(mind_l_Queue[3-1]).toInt()) + 1))));
		DF_Sort();
		while (!(!((urm10.getDistanceCM(7, 6))<=10))) {}
	}
	if ((mind_n_ChaoShengBo4<=10)) {
		mind_l_Queue.replace(4-1, (String(((String(mind_l_Queue[4-1]).toInt()) + 1))));
		DF_Sort();
		while (!(!((urm10.getDistanceCM(9, 8))<=10))) {}
	}
	Serial.println("----------------------------");
	Serial.println(mind_l_Queue[1-1]);
	Serial.println(mind_l_Queue[2-1]);
	Serial.println(mind_l_Queue[3-1]);
	Serial.println(mind_l_Queue[4-1]);
	Serial.println("----------------------------");
	Serial.println("|||||||||||||||||||");
	Serial.println(mind_l_sorted[1-1]);
	Serial.println(mind_l_sorted[2-1]);
	Serial.println(mind_l_sorted[3-1]);
	Serial.println(mind_l_sorted[4-1]);
	Serial.println("|||||||||||||||||||");
	DF_Get();
}


// 自定义函数
void DF_HuskyLensRenTiGenZong() {
	huskylens.request();
	if (huskylens.isLearned(mind_n_RenJiShu)) {
		servo_11.angle(abs((map(huskylens.readBlockParameter(mind_n_RenJiShu).xCenter, 0, 320, 180, 0))));
		servo_10.angle(abs((map(huskylens.readBlockParameter(mind_n_RenJiShu).yCenter, 0, 240, 0, 90))));
	}
	else {
		mind_n_RenJiShu += 1;
		huskylens.learnOnece(mind_n_RenJiShu);
		if (huskylens.isLearned(mind_n_RenJiShu)) {
			if (huskylens.isAppear(mind_n_RenJiShu,HUSKYLENSResultBlock)) {
				servo_11.angle(abs((map(huskylens.readBlockParameter(mind_n_RenJiShu).xCenter, 0, 320, 180, 0))));
				servo_10.angle(abs((map(huskylens.readBlockParameter(mind_n_RenJiShu).yCenter, 0, 240, 0, 90))));
			}
			else {
				servo_11.angle(abs(90));
				servo_10.angle(abs(0));
			}
		}
		else {
			mind_n_RenJiShu -= 1;
			servo_11.angle(abs(90));
			servo_10.angle(abs(0));
		}
	}
}
void DF_Sort() {
	mind_l_sorted.clear();
	mind_l_TongPaiXu.clear();
	mind_n_tmp1 = 0;
	for (int index = 0; index < 50; index++) {
		mind_l_TongPaiXu.push_back("0");
	}
	for (int index = 0; index < 4; index++) {
		mind_n_tmp1 += 1;
		mind_l_TongPaiXu.replace((String(mind_l_Queue[mind_n_tmp1-1]).toInt())-1, (String(mind_n_tmp1)));
	}
	mind_n_tmp1 = 50;
	mind_n_tmp2 = 0;
	for (int index = 0; index < 49; index++) {
		mind_n_tmp1 -= 1;
		if ((!((String(mind_l_TongPaiXu[mind_n_tmp1-1]).toInt())==0))) {
			mind_l_sorted.push_back(mind_l_TongPaiXu[mind_n_tmp1-1]);
		}
	}
}
