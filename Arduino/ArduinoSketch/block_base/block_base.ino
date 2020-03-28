struct Sensor {
  byte status_value;
  String lat;
  String lng;
  String label;
};

boolean flag = 0;
boolean led_flag = 0;
boolean update_value = 0;

Sensor sensor1 = {0, "59.977229", "74.900324", "1"};
Sensor sensor2 = {0, "59.963229", "74.980324", "2"};
Sensor sensor3 = {0, "59.863299", "74.500394", "3"};

void setup() {
  Serial.begin(9600);
  pinMode(13, INPUT);
  pinMode(12, OUTPUT);
}

void loop() {
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
  boolean butt = digitalRead(13);

  if (butt == 1 && flag == 0) {
    flag = 1;
    led_flag = !led_flag;
    if (led_flag != sensor1.status_value) {
      update_value = 1;
      sensor1.status_value = led_flag;
    }
    digitalWrite(12, led_flag);
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
