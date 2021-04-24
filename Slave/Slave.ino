#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Wire.h>
int data[14];

#define FIREBASE_HOST "nmcu-ecb40.firebaseio.com"
#define FIREBASE_AUTH "0ym5quflPnIYH9Ufmr5uRkrOLDKRAP3p7FSZ3Dcx"
#define WIFI_SSID "Kost Ceria"
#define WIFI_PASSWORD "bayarosek!"

void setup(){
  Wire.begin(D1, D2);        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop(){
  Wire.requestFrom(2, 4);    // request 3 bytes from slave device #2
    for(int i=0; i<14; i++){ 
      int c = Wire.read(); // receive a byte as character
      Serial.print(c); 
      data[i]=c;
      Serial.print('\t');    
  }
    Firebase.setInt("Pot A S1", data[0]);
    Firebase.setInt("Pot A S2", data[1]);
    Firebase.setInt("Pot B S1", data[2]);
    Firebase.setInt("Pot B S2", data[3]);
    Firebase.setInt("Pot C S1", data[4]);
    Firebase.setInt("Pot C S2", data[5]);
    Firebase.setInt("Pot D S1", data[6]);
    Firebase.setInt("Pot D S2", data[7]);
    Firebase.setInt("Pot E S1", data[8]);
    Firebase.setInt("Pot E S2", data[9]);
    Firebase.setInt("Pot F S1", data[10]);
    Firebase.setInt("Pot F S2", data[11]);
    Firebase.setInt("Suhu", data[12]);
    Firebase.setInt("Status Penyinaran", data[13]);
  delay(500);
}
