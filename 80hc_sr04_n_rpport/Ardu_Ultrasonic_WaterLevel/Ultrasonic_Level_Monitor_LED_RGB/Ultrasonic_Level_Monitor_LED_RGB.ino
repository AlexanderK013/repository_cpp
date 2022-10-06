//www.diyusthad.com
//www.youtube.com/c/diyusthad

//#define red 9
//#define green 10
//#define blue 11
#define red 9
#define green 11
#define blue 10
int t = 500;
int brightness;
int fadeAmount = 5;
const unsigned int DIM1 = 7;
const unsigned int DIM2 = 3;

int ary[DIM1][DIM2] = { { 255, 0, 0 }, //	 	red
		{ 255, 165, 0 }, //	 	orange
		{ 255, 255, 0 }, //	 	yellow
		{ 0, 128, 0 }, //	 	green
		{ 0, 0, 255 }, //	 	blue
		{ 75, 0, 130 }, //	 	indigo
		{ 238, 130, 238 }, //	 	violet

		};
//Пин, к которому подключен пьезодинамик.
int piezoPin = 11;//3;
#include "pitches.h"
int division_factor =1;//25;//
// notes in the melody:
int melody[] = {

NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4 };

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {

4, 8, 8, 4, 4, 4, 4, 4 };


int melody2[] = {
 NOTE_A4, NOTE_E3, NOTE_A4, 0,
 NOTE_A4, NOTE_E3, NOTE_A4, 0,
 NOTE_E4, NOTE_D4, NOTE_C4, NOTE_B4, NOTE_A4, NOTE_B4, NOTE_C4, NOTE_D4,
 NOTE_E4, NOTE_E3, NOTE_A4, 0
};

int noteDurations2[] = {

 250, 250, 250, 250,
 250, 250, 250, 250,
 125, 125, 125, 125, 125, 125, 125, 125,
 250, 250, 250, 250
};int melody0[] = {
		  392, 392, 392, 311, 466, 392, 311, 466, 392,
		  587, 587, 587, 622, 466, 369, 311, 466, 392,
		  784, 392, 392, 784, 739, 698, 659, 622, 659,
		  415, 554, 523, 493, 466, 440, 466,
		  311, 369, 311, 466, 392
		};
		int noteDurations0[] = {
		  350, 350, 350, 250, 100, 350, 250, 100, 700,
		  350, 350, 350, 250, 100, 350, 250, 100, 700,
		  350, 250, 100, 350, 250, 100, 100, 100, 450,
		  150, 350, 250, 100, 100, 100, 450,
		  150, 350, 250, 100, 750
		};
void setup() {
	loop_melody();
} //3
void loop3() {
//
	// //analogWrite(red, brightness); //writing brightness value to red
	analogWrite(green, brightness); //writing brightness value to green
	analogWrite(blue, brightness); //writing brightness value to green

	brightness += fadeAmount; //increasing brightness value by 5 in each loop

	if (brightness < 0 || brightness > 125) {
		fadeAmount = -fadeAmount; //reversing the direction of fading when brightness reachs 0 or 255
	}
	delay(30); //delaying the speed of fading
}
//
void loop2() {
	//  analogWrite(red, 255);
	// //////  delay(t);green
	analogWrite(green, 255);
	delay(t);
	analogWrite(green, 0);
	delay(t);
	// analogWrite(blue, 255);
	//delay(t);
//  analogWrite(red, 0);
//  delay(t);
//  analogWrite(green, 0);
//  delay(t);
}
//
void loop0() {
	analogWrite(red, ary[0][0]);
	delay(t);
	analogWrite(red, 0);
	delay(t);
//  analogWrite(blue, ary[0][0]);
//  delay(t);
//  analogWrite(blue, 0);
//  delay(t);
//  analogWrite(green, ary[0][0]);
//  delay(t);
//  analogWrite(green, 0);
//  delay(t);
}
void loop_piezo() {

	/*Функция принимает три аргумента
	 1) Номер пина
	 2) Частоту в герцах, определяющую высоту звука
	 3) Длительность в миллисекундах.
	 */
	tone(piezoPin, 1000, 500); // Звук прекратится через 500 мс, о программа останавливаться не будет!
	/* Вариант без установленной длительности   */
	tone(piezoPin, 2000); // Запустили звучание
	delay(500);
	noTone(piezoPin); // Остановили звучание
}
void loop_melody() {

    int arrSizelength = sizeof(melody)/sizeof(melody[0]);
	// iterate over the notes of the melody:

	for (int thisNote = 0; thisNote < arrSizelength; thisNote++) {

		// to calculate the note duration, take one second divided by the note type.

		//e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.

		int noteDuration = 1000 / noteDurations[thisNote];
		noteDuration = noteDuration*division_factor;

		tone(piezoPin, melody[thisNote], noteDuration);

		// to distinguish the notes, set a minimum time between them.

		// the note's duration + 30% seems to work well:

		int pauseBetweenNotes = noteDuration * 1.30;

		delay(pauseBetweenNotes);

		// stop the tone playing:

		noTone(piezoPin);

	}
}
//0
void loop00() {
	for (int i = 0; i < DIM1; i++) {
		analogWrite(red, ary[i][0]);
		analogWrite(green, ary[i][1]);
		analogWrite(blue, ary[i][2]);
		delay(t);
		analogWrite(red, 0);
		analogWrite(green, 0);
		analogWrite(blue, 0);
		delay(t);
	}

}
void loop() {
	//	loop_piezo() ;
	//loop_melody();
	;
}
