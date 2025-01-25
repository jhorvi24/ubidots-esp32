#include <Ubidots.h>
#include "credentials.h"
#include <DHT.h>
#include <DHT_U.h>


const char* UBIDOTS_TOKEN = "BBUS-PNX5TvbDPSUeiUyPiDacEcDfjtPIKO";  // Put here your Ubidots TOKEN
#define dhtpin 14
#define DHTTYPE DHT11
#define led 2

float h;
float t;

DHT dht(dhtpin, DHTTYPE);

Ubidots* ubidots{nullptr};

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  Ubidots::wifiConnect(ssid, password);
  ubidots = new Ubidots(UBIDOTS_TOKEN, UBI_HTTP);
  ubidots->setDebug(true); // Uncomment this line for printing debug messages
  dht.begin();
  pinMode(led, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  h = dht.readHumidity();
  t = dht.readTemperature();

  

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.println("%");
  Serial.print(F("Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));

  ubidots->add("temperature", t);  // Change for your variable name
  ubidots->add("humidity", h);

  bool bufferSent = false;
  bufferSent = ubidots->send();  // Will send data to a device label that matches the device Id

  if (bufferSent) {
    // Do something if values were sent properly
    Serial.println("Values sent by the device");
  }

  delay(5000);

}
