# Wireless-Environmental-Monitoring-System

#include "thingProperties.h"
#include "DHT.h"
#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTpin 0 // D3 on the nodemcu ESP8266
#define DHTTYPE DHT11
DHT dht(DHTpin, DHTTYPE);

#define LDR_PIN 16 // D0 on the nodemcu ESP8266
#define RAIN_PIN A0 // Analog pin connected to rain sensor

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 columns and 2 rows

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  delay(1500); 

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  // Initialize LCD
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.clear();

  lcd.setCursor(3, 0);
  lcd.print("Harshini Thanish");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Weather Monitor");
  lcd.setCursor(4, 1);
  lcd.print("System");
  delay(4000);
  lcd.clear();
}

void loop() {
  ArduinoCloud.update();
  
  float h = dht.readHumidity();
  Serial.print("Humidity: ");
  Serial.println(h);
  humidity = h;

  float t = dht.readTemperature();
  Serial.print("Temperature: ");
  Serial.println(t);
  temperature = t;

  bool lightvalue = digitalRead(LDR_PIN);
  light = lightvalue;
  Serial.print("Light Value: ");
  Serial.println(lightvalue);
  if (light == 0) {
    digitalWrite(LDR_PIN, HIGH);
    Serial.print("LED ON");
  } else {
    digitalWrite(LDR_PIN, LOW);
    Serial.print("LED OFF");
  }

  int rainvalue = analogRead(RAIN_PIN);
  rain = map(rainvalue, 400, 1023, 100, 0);
  Serial.print("Rain Value: ");
  Serial.println(rain);
}

/*
  Since Temperature is READ_WRITE variable, onTemperatureChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onTemperatureChange()  {
  // Add your code here to act upon Temperature change
}

/*
  Since Humidity is READ_WRITE variable, onHumidityChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onHumidityChange()  {
  // Add your code here to act upon Humidity change
}

/*
  Since Rain is READ_WRITE variable, onRainChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onRainChange()  {
  // Add your code here to act upon Rain change
}

/*
  Since Light is READ_WRITE variable, onLightChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onLightChange()  {
  // Add your code here to act upon Light change
}

