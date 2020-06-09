

/* --- www.nyebarilmu.com --- */

/*
Sensor jarak HC-SR04
pin yang perlu dihubungkan
VCC to arduino 5v
GND to arduino GND
Echo to Arduino pin 7
Trig to Arduino pin 8
*/

#include <Wire.h>
#include <OneWire.h>

#define echoPin 12 //Echo Pin
#define trigPin 14 //Trigger Pin

int maximumRange = 200; //kebutuhan akan maksimal range
int minimumRange = 00; //kebutuhan akan minimal range
long duration, distance; //waktu untuk kalkulasi jarak

void setup() {
Serial.begin (115200); //inisialiasasi komunikasi serial
//deklarasi pin
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
}

void loop() {
/* Berikut siklus trigPin atau echo pin yang digunakan
untuk menentukan jarak objek terdekat dengan memantulkan
gelombang suara dari itu. */
digitalWrite(trigPin, LOW);delayMicroseconds(2);
digitalWrite(trigPin, HIGH);delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);

//perhitungan untuk dijadikan jarak
distance = duration/58.2;

/* Kirim angka negatif ke komputer dan Turn LED ON 
untuk menunjukkan "di luar jangkauan" */

if (distance >= maximumRange || distance <= minimumRange)
{
Serial.println("-1");
}
else {


/*
 * dik: p(kolam)=; l(kolam)=; t(kolam)=;
 * 
 * Rumus 
 * t(air) = t(kolam) - distance
 * volume(air) = p(kolam) * l(kolam) * t(air) 
 */
int pKolam = 15;
int lKolam = 14;
int tKolam = 11;
int tAir;
int volumeAir;

tAir = tKolam - distance;
volumeAir = pKolam * lKolam * tAir;
Serial.println(volumeAir); //p kolam dikurangi

//waktu tunda 50mS
delay(1000);
}}
