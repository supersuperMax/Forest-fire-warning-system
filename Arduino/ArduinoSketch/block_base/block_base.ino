#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

RF24 radio(9, 10);

struct Sensor {
  byte status_value;
  String lat;
  String lng;
  String label;
};

boolean flag = 0;
boolean led_flag = 0;
boolean update_value = 0;

byte button = 2;
byte led = 7;

Sensor sensor1 = {0, "59.977229", "74.900324", "1"};
Sensor sensor2 = {0, "59.963229", "74.980324", "2"};
Sensor sensor3 = {0, "59.863299", "74.500394", "3"};


byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"};
byte data [2];

void setup() {
  Serial.begin(9600);
  pinMode(button, INPUT);
  pinMode(led, OUTPUT);
  radio.begin(); //активировать модуль
  radio.setAutoAck(1);         //режим подтверждения приёма, 1 вкл 0 выкл
  radio.setRetries(0, 15);    //(время между попыткой достучаться, число попыток)
  radio.enableAckPayload();    //разрешить отсылку данных в ответ на входящий сигнал
  radio.setPayloadSize(32);     //размер пакета, в байтах

  radio.openReadingPipe(1, address[0]);     //хотим слушать трубу 0
  radio.setChannel(0x60);  //выбираем канал (в котором нет шумов!)

  radio.setPALevel (RF24_PA_MAX); //уровень мощности передатчика. На выбор RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate (RF24_1MBPS); //скорость обмена. На выбор RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
  //должна быть одинакова на приёмнике и передатчике!
  //при самой низкой скорости имеем самую высокую чувствительность и дальность!!
  // ВНИМАНИЕ!!! enableAckPayload НЕ РАБОТАЕТ НА СКОРОСТИ 250 kbps!

  radio.powerUp(); //начать работу
  radio.startListening();  //начинаем слушать эфир, мы приёмный модуль
}

void loop() {
  byte pipeNo;

  while ( radio.available(&pipeNo)) {
    radio.read( &data, sizeof(data));
  }
  delay(100);

  if (data[1] != sensor1.status_value) {
    update_value = 1;
  }
  sensor1.status_value = data[1];

  update_listner ();
  button_listner ();
}

void update_listner () {
  if (update_value) {
    messege_creator();
    update_value = 0;
  }
}

void button_listner () {
  boolean butt = digitalRead(button);

  if (butt == 1 && flag == 0) {
    flag = 1;
    led_flag = !led_flag;
    if (led_flag != sensor1.status_value) {
      update_value = 1;
      sensor1.status_value = led_flag;
    }
    digitalWrite(led, led_flag);
  }
  if (butt == 0 && flag == 1) {
    flag = 0;
  }

}

void mc (Sensor sensor) {
  Serial.print ("{\"status\":");
  Serial.print (sensor.status_value);
  Serial.print (",\"position\":{\"lat\":");
  Serial.print(sensor.lat);
  Serial.print(",\"lng\":");
  Serial.print(sensor.lng);
  Serial.print("},\"label\":\"");
  Serial.print(sensor.label);
  Serial.print("\"}");
}

void messege_creator () {
  Serial.print ("{\"sensors\":[");
  mc (sensor1); Serial.print(",");
  mc (sensor2); Serial.print(",");
  mc (sensor3);
  Serial.println("]}");
}

void rand_mes () {
  sensor1.status_value = (sensor1.status_value + 1 ) % 2;
  sensor2.status_value = (sensor2.status_value + sensor1.status_value + 1 ) % 2;
  sensor3.status_value = (sensor3.status_value + sensor1.status_value + sensor2.status_value + 1 ) % 2;
}
