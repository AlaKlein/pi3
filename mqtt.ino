#include "WiFi.h"
#include "EspMQTTClient.h"

EspMQTTClient client(
  "AlaKlein",
  "yrl4771*",
  "192.168.2.156",
  "esp32",
  1883
);

//conf wifi
const char* ssid       = "AlaKlein";
const char* password   = "yrl4771*";


void setup() {
  Serial.begin(115200);

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" CONNECTED");
  Serial.println(WiFi.localIP());

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void onConnectionEstablished()
{

  // Subscribe to "mytopic/wildcardtest/#" and display received message to Serial
  client.subscribe("mytopic/ESP32", [](const String & topic, const String & payload) {
    Serial.println("(From wildcard) topic: " + topic + ", payload: " + payload);
  });
}

void loop() {
  client.loop();

}
