#include <MQ135.h>

#include <ESP8266WiFi.h>
#include <Wire.h>
#include <OneWire.h>

const int gasSensor =0;
void setup(){
  Serial.begin(9600);      // sets the serial port to 9600
}
void loop(){
  float voltage;
  voltage = getVoltage(gasSensor);
  
  Serial.print(voltage);
  Serial.println(" PPM");
  delay(1000);
}

float getVoltage(int pin){
  return (analogRead(pin) * 0.004882814);
  // This equation converts the 0 to 1023 value that analogRead()
  // returns, into a 0.0 to 5.0 value that is the true voltage
  // being read at that pin.
}
