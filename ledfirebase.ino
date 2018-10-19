#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include "DHT.h"

// Set these to run example.
#define FIREBASE_HOST "example.firebaseio.com"
#define FIREBASE_AUTH "token_or_secret"
#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "PASSWORD"

DHT dht;

void setup() {
  Serial.begin(9600);
  dht.setup(D1);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {

  delay(dht.getMinimumSamplingPeriod())
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();

}
