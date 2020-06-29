/* www.nyebarilmu.com
 *  2019
 *  Program pembacaan pH meter dan ds18b20 via serial monitor
*/
 
#include "DFRobot_PH.h" //library yang diinstal seperti instruksi diatas
//#include <OneWire.h>  //library untuk pembacaan sensor ds18b20
//#include <DallasTemperature.h> 
// 
//#define sensor_ds18b20 2 //pada pin 2 untuk sensor ds18b20
// 
//OneWire oneWire(sensor_ds18b20);
 
//DallasTemperature sensors(&oneWire); //penggunaan interface 1 wire untuk pengaksesan
 
#define sensor_ph A1 //pembacaan sensor ph menggunakan ADC
 
float tegangan,nilaiph;
DFRobot_PH ph;
 
void setup()
{
   Serial.begin(9600);  //serial monitor
    ph.begin(); //mulai untuk pembacaan sensor ph meter
//    sensors.begin(); //mulai untuk pembacaan sensor ds18b20
}
 
void loop()
{
  sensors.requestTemperatures(); 
  static unsigned long timepoint = millis();
    if(millis()-timepoint>1000U){                  //time interval: 1s
        timepoint = millis();
        tegangan = analogRead(sensor_ph)/1024.0*5000; //mengubah tegangan analog menjadi digital dan menjadi tegangan
//        suhu = sensors.getTempCByIndex(00);
        nilaiph = ph.readPH(tegangan,suhu);  //konversi tegangan menjadi ph meter dengan kompensasi suhu
        Serial.print("Celsius temperature: ");
//        Serial.print(suhu,1); //nilai pembacaan suhu
        Serial.print("^C  pH:");
        Serial.println(nilaiph,2); //nilai pembacaan ph meter
    }
    ph.calibration(tegangan,suhu); 
}
