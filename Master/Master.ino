//D1 >> SDA
//D2 >> SCL
#include <OneWire.h> 
#include <DallasTemperature.h>
#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;
int data[14];
int pompa = 7;
int lampu = 6;
int motor = 5;
int ONE_WIRE_BUS = 2;
int Sensor1 = A0;
int Sensor2 = A1;
int Sensor3 = A2;
int Sensor4 = A3;
int Sensor5 = A4;
int Sensor6 = A5;
int Sensor7 = A6;
int Sensor8 = A7;
int Sensor9 = A8;
int Sensor10 = A9;
int Sensor11 = A10;
int Sensor12 = A11;

OneWire oneWire(ONE_WIRE_BUS);  
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  Wire.begin(2);                // join i2c bus with address #2
  Wire.onRequest(requestEvent);
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

pinMode(A0, INPUT);
pinMode(A1, INPUT);
pinMode(A2, INPUT);
pinMode(A3, INPUT);
pinMode(A4, INPUT);
pinMode(A5, INPUT);
pinMode(A6, INPUT);
pinMode(A7, INPUT);
pinMode(A8, INPUT);
pinMode(A9, INPUT);
pinMode(A10, INPUT);
pinMode(A11, INPUT);
pinMode(7, OUTPUT); //Relay WaterPump
pinMode(6, OUTPUT); //Relay Lampu
pinMode(5,OUTPUT); //Relay Motor
Serial.begin(9600); 
}

int temperatur(){
  sensors.requestTemperatures();
  double suhu = sensors.getTempCByIndex(0);
  if ( suhu < 29 ){
    digitalWrite (lampu, HIGH);
  }else {
    digitalWrite(lampu, LOW);
   }
   return suhu;
   delay(1000);
}
       
int penyinaran(){
DateTime now = rtc.now();
if ((now.hour() == 14 && now.minute() > 6) && (now.hour() == 14 && now.minute()< 8)) {
      digitalWrite(6, LOW);
      return 1;
     }
     else {
      digitalWrite(6, HIGH);
      return 0;
     }
}

void loop() {
  data[0] = map(analogRead(Sensor1), 0, 1023, 0, 100);
  data[1] = map(analogRead(Sensor2), 0, 1023, 0, 100);
  data[2] = map(analogRead(Sensor3), 0, 1023, 0, 100);
  data[3] = map(analogRead(Sensor4), 0, 1023, 0, 100);
  data[4] = map(analogRead(Sensor5), 0, 1023, 0, 100);
  data[5] = map(analogRead(Sensor6), 0, 1023, 0, 100);
  data[6] = map(analogRead(Sensor7), 0, 1023, 0, 100);
  data[7] = map(analogRead(Sensor8), 0, 1023, 0, 100);
  data[8] = map(analogRead(Sensor9), 0, 1023, 0, 100);
  data[9] = map(analogRead(Sensor10), 0, 1023, 0, 100);
  data[10] = map(analogRead(Sensor11), 0, 1023, 0, 100);
  data[11] = map(analogRead(Sensor12), 0, 1023, 0, 100);
  data[12] = temperatur();
  data[13] = penyinaran();
}

void requestEvent(){
  uint8_t Send[14];

  for (int i = 0; i<12; i++){
    Send[i]=data[i];
  }
  Send[12] = data[12];
  Send[13] = data[13];  
  Wire.write(Send, 14); 
  
}
