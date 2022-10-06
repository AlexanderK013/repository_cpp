/*
 Joginder
 hobbyprojects
 22-05-2022
 Ultrasonic_Level_Monitor_4pin_OLED.ino
 */
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "pitches.h"
#include "FastLED.h"

// ------------- Tank details ------------//
//int Tank_height = 50; // Distance from the installed face of the transducer, down to the bottom of the tank
//int Fill_height = 40; // Distance from the bottom of the tank,up to the maximum desired liquid height
int Tank_height = 25; // Distance from the installed face of the transducer, down to the bottom of the tank
int Fill_height = 20; // Distance from the bottom of the tank,up to the maximum desired liquid height
//----------------------------------------//
int cm;
long t;
int distance_Measured;
int distance_Sensor_to_Fill;

unsigned char a = 0;
unsigned int level = 0;
unsigned int temp = 10;
int tankLevel;
//int trigPin = 11;
//int echoPin = 10;

int MuteSwitch = A5;
int alarm_output = 2;
//vars ping ping ping ping ping ping ping ping ping ping ping

int pingPin = 4; //пин для выхода trig *First parcel

int inPin = 2; //пин для выхода echo
//vars Level Level Level Level Level Level Level Level Level Level Level
const unsigned int DIM1 = 7; // 6;//
//55555
//int arLevels[DIM1] = { 12, 25, 35, 45, 55, 65, 75 }; //51
//int arLevels[DIM1] = { 1, 2, 3, 4, 5, 6, 7 }; //51
int arLevels[DIM1] = { 0, 15, 50, 86, 120, 150, 180 }; //51, 185
enum class Level {
	Level_stop = 1,
	Level2 = 2,
	Level3 = 3,
	Level4 = 4,
	Level5 = 5,
	Level6 = 6,
	Level_empty = 7
};
Level LevelCur;
//vars OLED OLED OLED OLED OLED OLED OLED OLED OLED OLED OLED

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
double count = 0;

/*
 * PIN connection:
 * pin connection see: https://www.arduino.cc/en/Reference/Wire
 * for UNO: SDA to A4, SCL to A5
 * for Mega2560: SDA to 20, SCL to 21
 * for Leonardo: SDA to 2, SCL to 3
 * for Due: SDA to 20, SCL to 21
 * VCC to 5V
 * GND to GND :-)
 */

// this is the Width and Height of Display which is 128 xy 32
#define LOGO16_GLCD_HEIGHT 32
#define LOGO16_GLCD_WIDTH  128

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
//vars leds leds leds leds leds leds leds leds leds leds leds

#define LED_PIN 6
#define LED_NUM 7//6//
CRGB leds[LED_NUM];
byte counter;
//vars piezo piezo piezo piezo piezo piezo piezo piezo piezo piezo piezo
//Пин, к которому подключен пьезодинамик.
int piezoPin = 11; //3;
float division_factor = .5; //1;//2;//5;//25;//
int melody[] = { //Сигнал горна "тревога"0,
		NOTE_DS7,
		NOTE_F7, 0, 0,
		NOTE_C7, 0, 0,
		NOTE_D7, 0, 0, 0, 0, 0,
		NOTE_F7,
		NOTE_DS7,
		NOTE_F7,
		NOTE_D7,
		NOTE_F7 };
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {

4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2 }; //Сигнал горна "тревога"
void loopFastLED() {
	//	counter++;
	counter = level - 1;
	//if (counter > LED_NUM)
	//counter = 0;
	for (int dot = counter; dot < LED_NUM; dot++) {
		leds[dot] = CRGB::Blue;
		//FastLED.show();Yellow Red Blue
		//CRGB Struct Reference	https://fastled.io/docs/3.1/struct_c_r_g_b.html
	}
	for (int dot = 0; dot < counter; dot++) {
		leds[dot] = CRGB::Yellow;
		// FastLED.show();
	}
	if (level == (int) Level::Level_empty||level == (int) Level::Level_stop)		//Level_stop
		leds[LED_NUM - 1] = CRGB::Red;
	else
		leds[LED_NUM - 1] = CRGB::Green;

	FastLED.show();
	//delay(500);
}

void setup() {
	Serial.begin(9600);
	pinMode(inPin, INPUT);
	pinMode(pingPin, OUTPUT);
	digitalWrite(pingPin, LOW);
	// pinMode(trigPin, OUTPUT);
	//pinMode(echoPin, INPUT);
	//pinMode(alarm_output, OUTPUT);
	//pinMode(MuteSwitch,INPUT_PULLUP);
	//digitalWrite(alarm_output, LOW);

	delay(10);

	//oled_init
	// by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize with the I2C addr 0x3C (for the 128x32)
	display.display();
	delay(2000);
	// Clear the buffer.
	display.clearDisplay();

	FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, LED_NUM);
	FastLED.setBrightness(50);

	distance_Sensor_to_Fill = Tank_height - Fill_height;
}
//
void Determine_current_level_number() {
	//27-08-202214:24
	//cm-arLevels
	if (cm < arLevels[(int) Level::Level_stop]) {
		level = (int) Level::Level_stop;
	} else if ((cm >= arLevels[(int) Level::Level_stop])
			&& (cm < arLevels[(int) Level::Level2])) {
		level = (int) Level::Level2;
	} else if ((cm >= arLevels[(int) Level::Level2])
			&& (cm < arLevels[(int) Level::Level3])) {
		level = (int) Level::Level3;
	} else if ((cm >= arLevels[(int) Level::Level3])
			&& (cm < arLevels[(int) Level::Level4])) {
		level = (int) Level::Level4;
	} else if ((cm >= arLevels[(int) Level::Level4])
			&& (cm < arLevels[(int) Level::Level5])) {
		level = (int) Level::Level5;
	} else if ((cm >= arLevels[(int) Level::Level5])
			&& (cm < arLevels[(int) Level::Level6])) {
		level = (int) Level::Level6;
	} else if ((cm >= arLevels[(int) Level::Level6])
			&& (cm < arLevels[(int) Level::Level_empty])) {
		level = (int) Level::Level_empty;
	} else {
		level = (int) Level::Level_empty;
	}
	Serial.print("level:");
	Serial.println(level);
	//switch (Level) {//Level
	//case task;break;
	//}
}
void Determine_distance_to_water() {  //27-08-202214:24
	long duration, tmp1;  //cm,объявляем переменные
	//посылаем датчику сигнал начала замера (высокий уровень на 10 мкс)
	digitalWrite(pingPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(pingPin, LOW);
	//делаем паузу чтобы датчик успел среагировать
	delayMicroseconds(500);
	//засекаем время в микросекундах
	tmp1 = micros();
	//ждем пока сигнал на выходе echo не станет низкий
	while (digitalRead(inPin) == HIGH) {
		//если долго нет ответа от датчика, значит препятствий в зоне видимости нет, выходим по таймауту
		if (micros() - tmp1 > 15000)
			break;
	}
	//вычисляем время "полета" ультразвукового сигнала
	duration = micros() - tmp1;
	cm = microsecondsToCentimeters(duration);	//переводим время в сантиметры
	Serial.print("Distance: ");
	//если помех не обнаружено сообщаем что расстояние более 1.5 метра
	if (duration > 15000)
		Serial.println(">1.5m");
	else
		Serial.println(cm);	//иначе выводим расстояние до помехи в сантиметрах
	delay(1000);
}
long microsecondsToCentimeters(long microseconds) {
	//скорость звука 340 м/с или 29,412 микросекунд/см, а поскольку звук летит до помехи и обратно, делим результат на двое
	return microseconds / 29.412 / 2;
}

void loop() {  ////27-08-202214:24

	Determine_distance_to_water();
	Determine_current_level_number();
	displayLevel();
//
	if (level != temp) {  //
		temp = level;
		loopFastLED();
		//displayLevel();
		//loop_melody();
	}
		//if (level == (int) Level::Level_empty||level == (int) Level::Level_stop)		//Level_stop
	if (level == (int) Level::Level_stop)//ToDo
	loop_melody();
	if (level == 0)
		alarmEmpty();

	if (level == 4)
		alarmFull();

	//delay(300);
}
void loop_melody() {

	int arrSizelength = sizeof(melody) / sizeof(melody[0]);
	// iterate over the notes of the melody:

	for (int thisNote = 0; thisNote < arrSizelength; thisNote++) {

		// to calculate the note duration, take one second divided by the note type.

		//e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.

		int noteDuration = 1000 / noteDurations[thisNote];
		noteDuration = noteDuration * division_factor;

		tone(piezoPin, melody[thisNote], noteDuration);

		// to distinguish the notes, set a minimum time between them.

		// the note's duration + 30% seems to work well:

		int pauseBetweenNotes = noteDuration * 1.30;

		delay(pauseBetweenNotes);

		// stop the tone playing:

		noTone(piezoPin);

	}
}
void alarmFull() {
}

void alarmEmpty() {
}
/*
 * robojaxText(String text, int x, int y,int size, boolean d)
 * text is the text string to be printed
 * x is the integer x position of text
 * y is the integer y position of text
 * z is the text size, 1, 2, 3 etc
 * d is either "true" or "false". Not sure, use true
 */
void robojaxText(String text, int x, int y, int size, boolean d) {

	display.setTextSize(size);
	display.setTextColor(WHITE);
	display.setCursor(x, y);
	display.println(text);
	if (d) {
		display.display();
	}

	//delay(100);
}

void displayLevel() {
	//int sensorValue = analogRead(A1);
	// print out the value you read:
	//if(sensorValue>0)
	Serial.println(level);
	// String vString =  String(count, 3);// using a float and the
	String vString = String(level);	//cm level
	String cmString = String(cm);	//cm level

	display.clearDisplay();
	//robojaxText("Voltage:          ", 4, 3, 1, false);
	robojaxText(vString, 1, 0, 3, false);
	robojaxText(cmString, 63, 0, 3, false);
	//robojaxText("V", 110, 3, 1, false);
	//robojaxText("Temprature: 32C", 4, 11, 1, false);
	//robojaxText("Capacity:   92.86L", 4, 21, 1, false);
	//display.drawLine(1, 37, 100, 37, WHITE);
	//display.drawRect(1, 1, 126,31, WHITE);
	//display.drawCircle(63,31, 31, WHITE);
	//display.startscrollright(0x00, 0x0F);

	//

	display.display();
	//count +=0.173;
	// delay(2000);
	//delay(300);
}

void write_data(unsigned char Data) {
}

void Clock(void) {
}

void startBit(void) {
}

void stopBit(void) {
}

void write_cmd(unsigned char comm) {
}

