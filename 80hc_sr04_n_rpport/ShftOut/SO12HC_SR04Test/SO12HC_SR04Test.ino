/*
  Shift Register Example
 for 74HC595 shift register

 This sketch turns reads serial input and uses it to set the pins
 of a 74HC595 shift register.

 Hardware:
 * 74HC595 shift register attached to pins 2, 3, and 4 of the Arduino,
 as detailed below.
 * LEDs attached to each of the outputs of the shift register

 Created 22 May 2009
 Created 23 Mar 2010
 by Tom Igoe

 */
//#include <avr/interrupt.h>
#define DEBUG_PRINT     0
//#define DEBUG_PRINT     1

#define NUM_SENS     80        // number of sensors
#define NUM_SENS_HAS     2        // number of sensorsHAS 2 1
byte ArraySENS[NUM_SENS_HAS];
byte ArrayRes[NUM_SENS_HAS];
unsigned int SensIndCur = 0;
//5000
#define DELAY_REGISTER_TRIG     5000

//Pin connected to latch pin (ST_CP) of 74HC595      g
const int latchPin = 8;
//Pin connected to clock pin (SH_CP) of 74HC595      y
const int clockPin = 12;
////Pin connected to Data in (DS) of 74HC595      b
const int dataPin = 11;
//***********************************************************
//Pin connected to latch pin (ST_CP) of 74HC595      g
const int latchPinSw = 6;
//Pin connected to clock pin (SH_CP) of 74HC595      y
const int clockPinSw = 5;
////Pin connected to Data in (DS) of 74HC595      b
const int dataPinSw = 7;



int inPin = 2;// //пин для выхода echo

const int interruptPin = 2;


const int comMake_meas = 1;
const int comTestTrig_2nd = 2;
int pingPin = 4;//пин для выхода trig



const int comStMes = 1;
const int comStMesCont = 2;
const int comStMesSec = 3;
const int comStMesSecCont = 4;
const int comStMesSecOrig = 7;

volatile long wSt, wFin;//
volatile long wAxFin;//
// https://sites.google.com/site/vanyambauseslinux/arduino/ispolzovanie-preryvanij-arduino
  // Переменная счётчика (volatile означает указание компилятору не оптимизировать код её чтения,
                         // поскольку её значение изменяется внутри обработчика прерывания)
ISR(INT0_vect)
{
	if(digitalRead(interruptPin)==HIGH){
		wSt=micros();
	}
	if(digitalRead(interruptPin)==LOW){
		wFin=micros();
	}
}
// Режимы вызова прерывания INT0
//#define INT0_SENSE_LOW_LEVEL     0        // Прерывание при низком уровне на выводе
//#define INT0_SENSE_LEVEL_CHANGE  1        // Прерывание при изменении уровня
//#define INT0_SENSE_FALLING_EDGE  2        // Прерывание по фронту на спад (когда 1 переходит в 0)
//#define INT0_SENSE_RISING_EDGE   3        // Прерывание по фронту на подъём (когда 0 переходит в 1)

// Управляющая функция для прерывания INT0
//    mode    - режим вызова прерывания
//    enable  - разрешить/запретить прерывание
void int0Control (uint8_t mode, bool enable){
    EIMSK &= ~ (1 << INT0);                    // Запретить прерывание (так как следующая команда устанавливает режим INT0_SENSE_LOW_LEVEL)
    EICRA &= ~ (1 << ISC00) | (1 << ISC01);    // Обнуляем биты ISC00 и ISC01 в регистре EICRA
    EICRA |= mode;                             // Устанавливаем режим вызова прерывания INT0
    if (enable)
      EIMSK |= (1 << INT0);                    // Разрешить прерывание
}



//////////////////////////////////////////////////////////////////////////////////////
void SetArraySENS() {//d
//	ArraySENS[0] = 2;
//	ArraySENS[1] = 4;
	ArraySENS[0] =2;//10 12 18
	ArraySENS[1] = 10;
//	////ArraySENS[0] =2;//10 12 18

}
//////////////////////////////////////////////////////////////////////////////////////

void setup() {
	SetArraySENS();//d
  //set pins to output because they are addressed in the main loop

	pinMode(latchPin, OUTPUT);
	pinMode(dataPin, OUTPUT);
	pinMode(clockPin, OUTPUT);

	pinMode(latchPinSw, OUTPUT);
	pinMode(dataPinSw, OUTPUT);
	pinMode(clockPinSw, OUTPUT);

	Serial.begin(9600);

	pinMode(inPin, INPUT);
	pinMode(pingPin, OUTPUT);

	int0Control(1, true);    // Разрешить прерывание по фронту на подъём (в данном случае при нажатии на кнопку)
	//interrupts();                                 // Разрешить прерывания глобально

	digitalWrite(pingPin, LOW);
	Serial_println("setup end");
  
}
//////////////////////////////////////////////////////////////////////////////////////
void Serial_println(String s) {
	if(DEBUG_PRINT==1)Serial.println(s);
}
//////////////////////////////////////////////////////////////////////////////////////
void Serial_print(String s) {
	if(DEBUG_PRINT==1)Serial.print(s);
}
//////////////////////////////////////////////////////////////////////////////////////
void PrintResult() {
	Serial_println("PrintResult");
	String strAns="";
	for (int j = 0; j < NUM_SENS_HAS; j++) {
		strAns+=String(ArrayRes[j], DEC);
		strAns+=";";
	}
	if(NUM_SENS_HAS<=2){
		strAns+=String(1, DEC);
		strAns+=";";
	}

	//strAns+=String(5.698, 3);//q maybe new editor
	Serial.println(strAns);
}

//////////////////////////////////////////////////////////////////////////////////////
unsigned int  w8NumSenTos8Bits(int NumSen8) {
  unsigned int x = 1;
  for (unsigned int n = 0; n < NumSen8-1; n++) {
	  x = x << 1; // use operator<< for left shift
  }
  return x;
}

//////////////////////////////////////////////////////////////////////////////////////

void loop() {
  if (Serial.available() > 0) {
	   Serial_println("*************loop**********");
//		wSt=0;
//		wFin=0;
		wAxFin=0;
    // you can subtract 48 to get the actual value:0 through 9 in ASCII
    int bitToSet = Serial.read() - 48;
//    Serial_print("bitToSet=");
    //    Serial_println(bitToSet);
    switch (bitToSet) {
    	case comMake_meas:
    		SensIndCur = 0;
    	    for (unsigned int n = 1; n <= NUM_SENS; n++) {
    	    	if(hasSen(n)){
    	    		measM(n);
    	    		SensIndCur++;
    	    	}
    	    }
    	    PrintResult();
    		break;
    	case comTestTrig_2nd:
    	case 3:
    	case 4:
    	case 5:
    	case 6:
    		TestTrig_2nd(bitToSet);
    		break;

    	default:
    		break;

    }

  }
}

//////////////////////////////////////////////////////////////////////////////////////
bool hasSen(int NumSen) {
  for (int j = 0; j < NUM_SENS_HAS; j++) {
	  if(ArraySENS[j]==NumSen)return true;
  }
  return false;
}
//////////////////////////////////////////////////////////////////////////////////////
void measM(int NumSen) {
	wSt=0;
	wFin=0;
	wAxFin=0;

    int numChip=1;//d
    Serial_print("measM NumSen=");
    Serial_print(String(NumSen, DEC));
//    Serial_print("NumSenTos8Bit=");
//    Serial_println(NumSenTos8Bit);
    NumSenToNumChipAndNumForChip(NumSen,numChip);
    Serial_print(" NumSen=");
    Serial_print(String(NumSen, DEC));
     Serial_print(" numChip=");
    Serial_println(String(numChip, DEC));
    byte NumSenTos8Bit=w8NumSenTos8Bits(NumSen);
    registerWriteSwQ(numChip,NumSenTos8Bit);
    delay(10);
    //delay(3000);
    registerWriteNq(numChip,NumSenTos8Bit);
    delayMicroseconds(DELAY_REGISTER_TRIG);
    //delay(10);
    registerWriteSwQ(numChip,0);
    delay(10);
    // delay(3000);
    work_int_data_end();
}
//////////////////////////////////////////////////////////////////////////////////////
void NumSenToNumChipAndNumForChip(int &NumSen,int &numChip) {
	numChip=(int)(NumSen/8)+1;
	NumSen=NumSen%8;
}
//////////////////////////////////////////////////////////////////////////////////////

void work_int_data_end() {
	long vTune=0;//500;
    long cm = microsecondsToCentimeters((wFin-wSt-vTune));//переводим время в сантиметры
    Serial_println("**********wFin-wSt="+String((wFin-wSt), DEC)+" cm="+String(cm, DEC) );
    ArrayRes[SensIndCur]=cm;
    //Serial_println("**********wAxFin-wSt="+String((wAxFin-wSt), DEC));
}


//////////////////////////////////////////////////////////////////////////////////////

void registerWriteNq(int numChip,byte NumSenTos8Bit) {
	long vStF, vEndF, vDiff;//объявляем переменные
	digitalWrite(latchPin, LOW);
	//  // shift the bits out:
	for (int i = numChip; i >0; i--) {
		if(i==numChip)shiftOut(dataPin, clockPin, MSBFIRST, NumSenTos8Bit);
		else shiftOut(dataPin, clockPin, MSBFIRST, 0);
	}
	// turn on the output so the LEDs can light up:
	digitalWrite(latchPin, HIGH);

	digitalWrite(latchPin, LOW);
	//  // shift the bits out:
	for (int i = 1; i <= numChip; i++) {
		shiftOut(dataPin, clockPin, MSBFIRST, 0);
	}
	// turn on the output so the LEDs can light up:
	digitalWrite(latchPin, HIGH);
  }


//////////////////////////////////////////////////////////////////////////////////////

void registerWriteSwQ(int numChip,byte NumSenTos8Bit) {
	long vStF, vEndF, vDiff;//объявляем переменные
	// turn off the output so the pins don't light up
	// while you're shifting bits:
	digitalWrite(latchPinSw, LOW);
	//numChip=1;//d
	//   shift the bits out:
	for (int i = numChip; i >0; i--) {
		if(i==numChip)shiftOut(dataPinSw, clockPinSw, MSBFIRST, NumSenTos8Bit);
		else shiftOut(dataPinSw, clockPinSw, MSBFIRST, 0);
	}
//	// shift the bits out:
//	shiftOut(dataPinSw, clockPinSw, MSBFIRST, bitsToSend);

	// turn on the output so the LEDs can light up:
	digitalWrite(latchPinSw, HIGH);
}


 //////////////////////////////////////////////////////////////////////////////////////
long microsecondsToCentimeters(long microseconds)
{
  //скорость звука 340 м/с или 29,412 микросекунд/см, а поскольку звук летит до помехи и обратно, делим результат на двое
  return microseconds / 29.412 / 2;
}


//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

void registerWrite(int whichPin, int whichState) {
  long vStF, vEndF, vDiff;//объявляем переменные
//// the bits you want to send
//  byte bitsToSend = 0;
  // для хранения 16 битов используем unsigned int
  unsigned int bitsToSend = 0;  //засекаем время в микросекундах
  vStF=micros();

  // turn off the output so the pins don't light up
  // while you're shifting bits:
  digitalWrite(latchPin, LOW);

switch (whichPin) {
	case comStMes:
		bitsToSend= 6;//  0000 0110   //bitsToSend=96;//0110 0000
		break;
	case comStMesCont:
		 bitsToSend= 2;//  0000 0010
		break;
	case comStMesSec:
		bitsToSend= 24;//  0001 1000   //00011000
		break;
	case comStMesSecCont:
		bitsToSend= 8;//  0000 1000   //00001000
		break;
	case 5:
		bitsToSend= 513;// 0000 0010 0000 0001   //10 0000 0001
		break;
	case 6:
		bitsToSend= 258;// 0000 0001 0000 0010   //1 0000 0010
		break;
	default:
		break;
}
//whichPin = 0xFE;
//whichPin = 0b1010001000110011;
//bitWrite(bitsToSend, whichPin, whichState);
////byte registerOne= x & 0xff;
//byte registerTwo = (x >> 8);
// разбиваем наши 16 бит на два байта
// для записи в первый и второй регистр
//		byte registerOne = highByte(bitsToSend);
//		byte registerTwo = lowByte(bitsToSend);
//		  registerOne = 255;
//		  registerTwo = 255;

// "проталкиваем" байты в регистры
		//shiftOut(dataPin, clockPin, MSBFIRST, registerTwo);
//shiftOut(dataPin, clockPin, MSBFIRST, registerOne);
//Serial_print("registerWrite whichPin="+String(whichPin, DEC));
//Serial_print(" registerOne="+String(registerOne, DEC));
//Serial_println(" registerTwo="+String(registerTwo, DEC));
//Serial_print(" registerOne="+String(registerOne, BIN));
//Serial_println(" registerTwo="+String(registerTwo, BIN));

//  // shift the bits out:
  shiftOut(dataPin, clockPin, MSBFIRST, bitsToSend);

    // turn on the output so the LEDs can light up:
  digitalWrite(latchPin, HIGH);
  vEndF=micros();
  vDiff=vEndF-vStF;
//
  // Serial_println("registerWrite ");
  String sT=String(whichPin, DEC)+String(vStF, DEC)+String(vEndF, DEC)+String(vDiff, DEC);
  //Serial_println("registerWrite sT="+sT);
  //Serial_println("registerWrite whichPin="+String(whichPin, DEC)+"vStF="+String(vStF, DEC)+" vEndF="+String(vEndF, DEC)+" vDiff="+String(vDiff, DEC) );

  switch (whichPin) {
  	case comStMes:
 	   //Serial_println("registerWrite delaySt");
 	   //delay(100);
 	   //Serial_println("registerWrite delayEnd");
  	   //delayMicroseconds(9000);
 	   registerWrite(comStMesCont, HIGH);
  		break;
  	case comStMesCont:
 	   //workN_hc_sr();
  		break;
  	case comStMesSec:
  	   registerWrite(comStMesSecCont, HIGH);
  		break;
  	case comStMesSecCont:
  	   //workN_hc_sr();
  		break;
  	default:
  		break;
  }


 }

//////////////////////////////////////////////////////////////////////////////////////
void registerWrite16FromTwo(byte registerOne, byte registerTwo) {
   // выключаем светодиоды на время передачи битов
  digitalWrite(latchPin, LOW);

  // "проталкиваем" байты в регистры
  shiftOut(dataPin, clockPin, MSBFIRST, registerTwo);
  shiftOut(dataPin, clockPin, MSBFIRST, registerOne);

  // "защелкиваем" регистр, чтобы биты появились на выходах регистра
  digitalWrite(latchPin, HIGH);
  Serial_print("registerWrite16FromTwo registerOne="+String(registerOne, DEC));
  Serial_println(" registerTwo="+String(registerTwo, DEC));
  Serial_print(" registerOne="+String(registerOne, BIN));
  Serial_println(" registerTwo="+String(registerTwo, BIN));
}
//////////////////////////////////////////////////////////////////////////////////////
void TestTrig_2nd(int bitToSet) {
	int NumSen = bitToSet;
	byte registerOne=w8NumSenTos8Bits(NumSen);
	byte registerTwo=w8NumSenTos8Bits(NumSen);
	registerWrite16FromTwo(registerOne, registerTwo);
}

//////////////////////////////////////////////////////////////////////////////////////

void registerWriteN(int whichSens) {
	// turn off the output so the pins don't light up
	// while you're shifting bits:
	digitalWrite(latchPin, LOW);

	// разбиваем наши 16 бит на два байта
	// для записи в первый и второй регистр
	byte registerOne =w8NumSenTos8Bits(whichSens);
	registerOne =255;
	byte registerTwo = w8NumSenTos8Bits(whichSens);
	// "проталкиваем" байты в регистры
	shiftOut(dataPin, clockPin, MSBFIRST, registerTwo);
	shiftOut(dataPin, clockPin, MSBFIRST, registerOne);
	Serial_print("registerWrite registerOne="+String(registerOne, DEC));
	Serial_println(" registerTwo="+String(registerTwo, DEC));
	Serial_print(" registerOne="+String(registerOne, BIN));
	Serial_println(" registerTwo="+String(registerTwo, BIN));
	// turn on the output so the LEDs can light up:
	digitalWrite(latchPin, HIGH);
	//delay(1);
	// delay(1000);
	digitalWrite(latchPin, LOW);
	registerOne = 0;
	registerTwo = 0;
	// "проталкиваем" байты в регистры
	shiftOut(dataPin, clockPin, MSBFIRST, registerTwo);
	shiftOut(dataPin, clockPin, MSBFIRST, registerOne);
	// turn on the output so the LEDs can light up:
	digitalWrite(latchPin, HIGH);

 }
 
