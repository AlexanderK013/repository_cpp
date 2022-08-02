int pingPin = 4;//пин для выхода trig

int inPin = 2;//пин для выхода echo

void setup() {
  Serial.begin(9600);
  pinMode(inPin, INPUT);
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
}
 
void loop() {
  long duration, cm,tmp1;//объявляем переменные
  //посылаем датчику сигнал начала замера (высокий уровень на 10 мкс)
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  //делаем паузу чтобы датчик успел среагировать
  delayMicroseconds(500);
  //засекаем время в микросекундах
  tmp1=micros();
  //ждем пока сигнал на выходе echo не станет низкий
  while(digitalRead(inPin)==HIGH){
    //если долго нет ответа от датчика, значит препятствий в зоне видимости нет, выходим по таймауту
    if(micros()-tmp1 > 15000)
      break;
  }
  //вычисляем время "полета" ультразвукового сигнала
  duration=micros()-tmp1;
  cm = microsecondsToCentimeters(duration);//переводим время в сантиметры
  Serial.print("Distance: ");
  //если помех не обнаружено сообщаем что расстояние более 1.5 метра
  if(duration>15000)
    Serial.println(">1.5m");
  else
    Serial.println(cm);//иначе выводим расстояние до помехи в сантиметрах
  delay(1000);
}
long microsecondsToCentimeters(long microseconds)
{
  //скорость звука 340 м/с или 29,412 микросекунд/см, а поскольку звук летит до помехи и обратно, делим результат на двое
  return microseconds / 29.412 / 2;
}




///Источник http://arduino-ua.com/art5-Podkluchenie_yltrazvykovogo_datchika_rasstoyanii_k_Arduino




