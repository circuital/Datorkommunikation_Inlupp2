#include <RH_ASK.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
RH_ASK driver(2000, 5, 3, 0);
DHT dht(2, DHT11);
#include "functions.h"

void setup() 
{
  Serial.begin(115200);
  driver.init();
  dht.begin();
}

void loop() 
{
  GetTempHumFromSensor();
}
