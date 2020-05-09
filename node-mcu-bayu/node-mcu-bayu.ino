#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//memasukkan pin
int sensorPinDS18b20 = 2;

//membuat variabel kosong
float suhuC;

OneWire ourWire(sensorPinDS18b20);
DallasTemperature sensors(&ourWire);

void setup() {
   Serial.begin(115200);
   delay(1000);
}

void loop() {
  sensors.requestTemperatures();
  suhuC = sensors.getTempCByIndex(0);

  //menampilkan hasil pembacaan sensor Suhu DS18b20
  Serial.print("Suhu = ");
  Serial.print(suhuC);
  Serial.print(" ");
  Serial.println("C");
}
