
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>

const char *ssid = "SWIFT-3-OBOHIB0 8693"; //nama wifi
const char *password = "rawamas4498";      //password
const char *host = "10.10.12.152";         //IP PC

//memasukkan pin
int sensorPinDS18b20 = 4;

//membuat variabel kosong
float suhuC;

OneWire ourWire(sensorPinDS18b20);
DallasTemperature sensors(&ourWire);

void setup() {
   Serial.begin(115200);
   delay(1000);

   Serial.println();
   Serial.println();
   Serial.print("Connecting to ");
   Serial.println(ssid);

   WiFi.begin(ssid, password);

   while (WiFi.status() != WL_CONNECTED)
   {
     delay(500);
     Serial.print(".");
   }

   Serial.println("");
   Serial.println("WiFi connected");
   Serial.println("IP address: ");
   Serial.println(WiFi.localIP());
}

void loop() {
  sensors.requestTemperatures();
  suhuC = sensors.getTempCByIndex(0);

  //menampilkan hasil pembacaan sensor Suhu DS18b20
  Serial.print("Suhu = ");
  Serial.print(suhuC);
  Serial.print(" ");
  Serial.println("C");
  delay(1000);
}
