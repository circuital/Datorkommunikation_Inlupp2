#include <RH_ASK.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <U8g2lib.h>

RH_ASK driver(2000, 2, 5, 0); 
WiFiClient espClient;
PubSubClient client(espClient);
U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

const char* mqtt_server = "172.20.216.21";
#include "functions.h"

void setup() 
{
  Serial.begin(115200);
  WiFi.begin("Nackademin-IOT", "Nack@!pr");
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("Device with IP Address: " + WiFi.localIP().toString() + " connected to WiFi.");
  driver.init();
  client.setServer(mqtt_server, 1883);
  client.setCallback(Callback);
  u8g2.begin();
  u8g2.enableUTF8Print();    
}

void loop() 
{
  if (!client.connected()) 
  {
    ReconnectAndSubscribe();
  }
  client.loop();

  Publish();
}
