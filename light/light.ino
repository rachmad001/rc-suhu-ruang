// this example is public domain. enjoy!
// https://learn.adafruit.com/thermocouple/

#include <max6675.h>
#include <DHT.h>
#include <ArduinoJson.h>

DHT dht(2, DHT11);

int thermoDO = 4;
int thermoCS = 5;
int thermoCLK = 6;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

void setup() {
  Serial.begin(9600);

  Serial.println("MAX6675 test");
  dht.begin();
  delay(500);
}

void loop() {
  StaticJsonDocument<200> doc;
  float celcius = thermocouple.readCelsius();
  float fahr = thermocouple.readFahrenheit();
  float kelembaban = dht.readHumidity();
  float suhu = dht.readTemperature();
  doc["celcius"] = celcius;
  doc["fahrenheit"] = fahr;
  doc["kelembaban"] = kelembaban;
  doc["suhu"] = suhu;
  String data = "";
  serializeJson(doc, data);
  Serial.println(data);
  delay(1000);
}
