
#include <SoftwareSerial.h>
#include <Time.h>

int gLedPin = 13;
//int gRxPin = 10;
//int gTxPin = 11;
int gRxPin = 5;
int gTxPin = 4;
//#define RxD 5//!!!
//#define TxD 4//!!!
SoftwareSerial BTSerial(gRxPin, gTxPin);

void setup() {
    //# 38400 - для метода №1, 9600 - для метода №2
    BTSerial.begin(38400);
    Serial.begin(9600);
    delay(500);
}

void loop() {
   if (BTSerial.available()) {
       Serial.write(BTSerial.read());
   }
   if (Serial.available()) {
       BTSerial.write(Serial.read());
   }
}
