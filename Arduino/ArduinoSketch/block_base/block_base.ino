struct Sensor {
  byte status_value;
  String lat;
  String lng;
  String label; 
};

Sensor sensor1 = {0, "59.977229", "74.900324", "1"};
Sensor sensor2 = {0, "59.963229", "74.980324", "2"};
Sensor sensor3 = {0, "59.863299", "74.500394", "3"};

void setup() {
  Serial.begin(9600);
}
 
void loop() {
    messege_creator();
    sensor1.status_value = (sensor1.status_value + 1 )%2;
    sensor2.status_value = (sensor2.status_value + sensor1.status_value + 1 )%2;
    sensor3.status_value = (sensor3.status_value + sensor1.status_value + sensor2.status_value + 1 )%2;
    delay(5000);
    
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
