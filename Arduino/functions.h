char tempMsg[50];
char humMsg[50];
char tempHumMsg[50];

void SendTempHumToFeather(char* tempHumValue)
{
  driver.send((uint8_t *)tempHumValue, strlen(tempHumValue));
  driver.waitPacketSent();
}

void GetTempHumFromSensor()
{  
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  dtostrf(temp, 4, 2, tempMsg);
  dtostrf(hum, 2, 0, humMsg);
  strcpy(tempHumMsg, "Temp: ");
  strcat(tempHumMsg, tempMsg);
  strcat(tempHumMsg, " Hum: ");
  strcat(tempHumMsg, humMsg);
  SendTempHumToFeather(tempHumMsg);
}
