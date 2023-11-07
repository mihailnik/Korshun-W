#include <Arduino.h>
// демо диспетчера задач

#include <GyverOS.h>
GyverOS<6> OS;	// указать макс. количество задач

void setup() {
//  Serial.begin(9600);
  pinMode(19, OUTPUT);
  
  // подключаем задачи (порядковый номер, имя функции, период в мс)
  OS.attach(0, f1, 400);
  OS.attach(1, f2, 1000);
  OS.attach(2, f3, 200);
  OS.attach(3, f4, 200);
  OS.attach(4, f5, 200);
  OS.attach(5, blinker, 200);
  
  //OS.detach(0);         // отключить задачу 0
  //OS.setPeriod(0, 200); // сменить период задачи 0 на 200 мс
  //OS.start(0);          // запустить задачу 0
  //OS.stop(0);           // остановить задачу 0
  //OS.exec(0);           // выполнить задачу 0 сейчас
}

void loop() {
  OS.tick();	// вызывать как можно чаще, задачи выполняются здесь
  
  // OS.getLeft() возвращает время в мс до ближайшей задачи
  // на это время можно усыпить МК, например при помощи narcoleptic или GyverPower
  // для примера просто поставим delay на это время
  delay(OS.getLeft());
}

// обработчики задач
void f1() {
  // выводит свой период в порт
  static uint32_t ms;
  
  
  ms = millis();
}

void f2() {
  static uint32_t ms;
 
 
  ms = millis();
}

void f3() {
  static uint32_t ms;


  ms = millis();
}

void f4() {
  static uint32_t ms;


  ms = millis();
}

void f5() {
  static uint32_t ms;


  ms = millis();
}

void blinker() {
  digitalWrite(19, !digitalRead(19));
  static uint32_t ms;


  ms = millis();
}