#include <ArduinoJson.h>
#include "AntaresESP8266HTTP.h"

#define ACCESSKEY "b228a36e03408e66:7ff275b11927ee13"
#define WIFISSID "OPPO A12"
#define PASSWORD "1234duakali"

#define projectName "suhu-"
#define deviceName "ruang"

AntaresESP8266HTTP antares(ACCESSKEY);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  antares.setDebug(true);
  antares.wifiConnectionNonSecure(WIFISSID,PASSWORD);
}

void loop() {
  // put your main code here, to run repeatedly:
  StaticJsonBuffer<200> doc;
  if(Serial.available()) {
    String data = Serial.readStringUntil('\n');
    JsonObject& root = doc.parseObject(data);
    if(!root.success()) {
      return;
    }
    float celc = root["celcius"];
    float fahr = root["fahrenheit"];
    float lemb = root["kelembaban"];
    float suhu = root["suhu"];
//    float celc = 1.0;
//    float fahr = 1.0;
//    float lemb = 1.0;
//    float suhu = 1.0;
    antares.add("max6675k", "celcius", celc);
    antares.add("max6675k", "fahrenheit", fahr);
    antares.add("dht11", "kelembaban", lemb);
    antares.add("dht11", "suhu", suhu);
    antares.sendNonSecure(projectName, deviceName); 
  }
}
