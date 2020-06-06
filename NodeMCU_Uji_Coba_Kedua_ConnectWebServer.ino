#include <ESP8266WiFi.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>

const char *ssid = "xxxxx"; //nama wifi
const char *password = "xxxxx";      //password wifi
const char *host = "xxxxx";         //IP PC -> ipconfig

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
  String url = "/nodemcu-esp8266-with-DS18B20-Sensor-MySQL-Database/add.php?";
  url += "suhu_air=";
  url += suhuC;

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

  //menampilkan hasil pembacaan sensor Suhu DS18b20
  Serial.print("Suhu = ");
  Serial.print(suhuC);
  Serial.print(" ");
  Serial.println("C");
  delay(1000);
}
