#include "pitches.h"
#define speakerPin 11       // Спикер, он же buzzer, он же beeper
//Выудил мелодии :grin: звуки из дубликатора домофонных ключей на Arduino
void setup()
{
// звук "Успешное включение"
    tone(speakerPin, NOTE_A7); delay(100);
    tone(speakerPin, NOTE_G7); delay(100);
    tone(speakerPin, NOTE_E7); delay(100);
    tone(speakerPin, NOTE_C7); delay(100);
    tone(speakerPin, NOTE_D7); delay(100);
    tone(speakerPin, NOTE_B7); delay(100);
    tone(speakerPin, NOTE_F7); delay(100);
    tone(speakerPin, NOTE_C7); delay(100);
    noTone(speakerPin);
    delay(2000);

// звук ОК
    for (int i=400; i<6000; i=i*1.5) { tone(speakerPin, i); delay(20); }
    noTone(speakerPin);
    delay(2000);

// звук "очередной шаг"
    for (int i=2500; i<6000; i=i*1.5) { tone(speakerPin, i); delay(10); }
    noTone(speakerPin);
    delay(2000);

// звук "ERROR"
    for (int j=0; j <3; j++){
    for (int i=1000; i<2000; i=i*1.1) { tone(speakerPin, i); delay(10); }
    delay(50);
    for (int i=1000; i>500; i=i*1.9) { tone(speakerPin, i); delay(10); }
    delay(50);
    }
    noTone(speakerPin);
  }

    void loop() {
      // ставить мелодию на повтор не будем.
}
