#include <ESP8266WiFi.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//wi-fi connection required
const char *ssid = "xxxxx";   //nama wifi
const char *password = "xxxxx";   //password wifi
const char *host = "xxxxx";       //IP PC -> ipconfig

//DS18B20 pin declare
int sensorPinDS18b20 = 4; //GPO4 atau D2

float suhuC;

OneWire ourWire(sensorPinDS18b20);
DallasTemperature sensors(&ourWire);

//HC-SR04 pin declare
#define echoPin 12 //Echo Pin
#define trigPin 14 //Trigger Pin

int maximumRange = 200;   //kebutuhan akan maksimal range
int minimumRange = 00;    //kebutuhan akan minimal range
long duration, distance;  //waktu untuk kalkulasi jarak

void setup() {
  Serial.begin(115200);
  //  delay(1000);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //wi-fi identify
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

  digitalWrite(trigPin, LOW);delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  //perhitungan untuk dijadikan jarak
  distance = duration/58.2;

  Serial.print("connecting to ");
  Serial.println(host);

  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort))
  {
    Serial.println("connection failed");
    return;
  }

  // We now create a URI for the request
  String url = "/nodemcu-esp8266-with-DS18B20-Sensor-MySQL-Database/ujiCoba4-NodeMCU-DS18B20-HCSR04/add.php?";
  url += "suhu_air=";
  url += suhuC;
  if (distance >= maximumRange || distance <= minimumRange)
  {
    url += "&volume_air=";
    url += 0;
  } else {
    url += "&volume_air=";
    url += distance;
  }
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
              "Host: " + host + "\r\n" +
              "Connection: close\r\n\r\n");

  unsigned long timeout = millis();
  while (client.available() == 0)
  {
    if (millis() - timeout > 5000)
    {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  while (client.available())
  {
    String line = client.readStringUntil('\r');
    //Serial.print(line);

    if (line.indexOf("sukses gaes") != -1)
    {
      Serial.println();
      Serial.println("Yes, data masuk");
    }
    else if (line.indexOf("gagal gaes") != -1)
    {
      Serial.println();
      Serial.println("Maaf, data gagal masuk");
      //digitalWrite(alarmPin, HIGH);
    }
  }

  Serial.println();
  Serial.println("closing connection");

  //Output DS18b20
  Serial.print("DS18B20 = ");
  Serial.print(suhuC);
  Serial.print(" ");
  Serial.println("C");

  //Output HC-SR04
  if (distance >= maximumRange || distance <= minimumRange)
  {
    Serial.print("HC-SR04 = ");
    Serial.println("-1");
  }
  else {
    Serial.print("HC-SR04 = ");
    Serial.println(distance);
  }

  Serial.println("===========================");
  delay(1000);
}
