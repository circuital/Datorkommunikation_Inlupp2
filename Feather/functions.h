uint8_t buf[50];
uint8_t buflen = 50;
const char* topic = "iot19/temperature";
int currentMillis = 0;
int previousMillis = 0;
char tempHumCharArray[50];
String tempHumString = "";
String tempString = "";
String humString = "";

void ReconnectAndSubscribe() 
{
  while (!client.connected()) 
  {
    randomSeed(micros());
    String clientId = "ESP8266Client-"; 
    clientId += String(random(0xffff), HEX);
    Serial.println("Attempting MQTT connection...");
    if (client.connect(clientId.c_str())) 
    {
      Serial.println("Connected to MQTT Broker.");
      client.subscribe(topic);
    } 
    else 
    {
      delay(5000);
    }
  }
}

void Publish()
{
  currentMillis = millis();
  if (currentMillis - previousMillis > 2000) 
  {
    if(driver.recv(buf, &buflen))
    {
      client.publish(topic, (char*)buf);
      previousMillis = currentMillis;
    }
    delay(1000);
  }
}

void Callback(char* topic, byte* payload, unsigned int length) 
{
  for (int i = 0; i < length; i++) 
  {
    tempHumCharArray[i] = (char)payload[i];
  }
  String tempHumString = String(tempHumCharArray);
  tempString = tempHumString.substring(0, 11);
  humString = tempHumString.substring(12);
  u8g2.setFont(u8g2_font_unifont_t_chinese2);  
  u8g2.setFontDirection(0);
  u8g2.firstPage();
  do 
  {
    u8g2.setCursor(0, 15);
    u8g2.print(tempString);
    u8g2.setCursor(0, 40);
    u8g2.print(humString);    
  } 
  while ( u8g2.nextPage() );
  delay(1000);
}
