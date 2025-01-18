/*Weather monitoring system with Thingspeak.
   Created by the SriTu Hobby team.
   Home Page
*/

#include <Wire.h>
#include <ESP8266WiFi.h>
#include "DHT.h"

DHT dht(D3, DHT11);
WiFiClient client;

String apiKey = "8WNM5CNEOIJ9V70Z";
const char *ssid =  "";//wifi name
const char *pass =  "";//password
const char* server = "api.thingspeak.com";

void setup() {
  Serial.begin(115200);
  delay(10);
  dht.begin();
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}

void loop() {
  // DHT11 sensor
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Rain sensor
  int r = analogRead(A0);
  r = map(r, 0, 1024, 0, 100);

  if (client.connect(server, 80)) {
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(t);
    postStr += "&field2=";
    postStr += String(h);
    postStr += "&field3=";
    postStr += String(r);
    postStr += "\r\n\r\n\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n\n\n");
    client.print(postStr);

    Serial.print("Temperature: ");
    Serial.println(t);
    Serial.print("Humidity: ");
    Serial.println(h);
    Serial.print("Rain: ");
    Serial.println(r);
  }
  client.stop();
  delay(15000);
}
