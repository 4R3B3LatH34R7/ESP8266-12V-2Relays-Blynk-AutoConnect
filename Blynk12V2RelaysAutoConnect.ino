#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <AutoConnect.h>

#ifdef ESP8266
  uint32_t chipID = ESP.getChipId();
#endif
#ifdef ESP32 //may be this is going to get reversed ip address
  uint64_t macAddress = ESP.getEfuseMac();
  uint64_t macAddressTrunc = macAddress << 40;
  uint32_t chipID = macAddressTrunc >> 40;
#endif

char auth[] = "yourAuthToken"; // <-Add your own Auth Token
byte relay1ON[]  = {0xA0, 0x01, 0x01, 0xA2};//Hex command to send to serial for close relay
byte relay1OFF[] = {0xA0, 0x01, 0x00, 0xA1};//Hex command to send to serial for open relay
byte relay2ON[]  = {0xA0, 0x02, 0x01, 0xA3};//Hex command to send to serial for close relay
byte relay2OFF[] = {0xA0, 0x02, 0x00, 0xA2};//Hex command to send to serial for open relay
AutoConnect portal;
AutoConnectConfig acConfig;

void setup()
{
  Serial.begin(115200); //<-some onboard MCU serial rates may be 9600
  acConfig.apid = "ESP-" + String(chipID); //"ESP-" + String((uint32_t)(ESP.getEfuseMac() >> 32), HEX); <-wifi AP Name will be something like ESP-1234567
  acConfig.psk = "configesp"; //<-wifi AP password for ESP01 Access Point
  acConfig.apip = IPAddress(192,168,4,1); //config at http://192.168.4.1/_ac
  acConfig.hostName = acConfig.apid;
  acConfig.autoReconnect = true;
  portal.config(acConfig);
  portal.begin();
  //Blynk.begin(auth, ssid, pass);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,110), 8080);
  Blynk.config(auth, IPAddress(192,168,1,110),8080); //can also be (auth, "192,168,1,125",8080);
  Blynk.connect();
}
void loop()
{
  Blynk.run();
  portal.handleClient();
}
BLYNK_WRITE(V1){ //Button Widget is writing to pin V1
  int pinData = param.asInt(); 
  if(pinData==1){
    //digitalWrite(relay1, HIGH);
    Serial.write(relay1ON, sizeof(relay1ON)); 
  }
  else{
    //digitalWrite(relay1, LOW);
    Serial.write(relay1OFF, sizeof(relay1OFF)); 
  }
}
BLYNK_WRITE(V2){ //Button Widget is writing to pin V1
  int pinData = param.asInt(); 
  if(pinData==1){
    //digitalWrite(relay2, HIGH);
    Serial.write(relay2ON, sizeof(relay2ON));
  }
  else{
    //digitalWrite(relay2, LOW);
    Serial.write (relay2OFF, sizeof(relay2OFF));
  }
}
/*
Close 1st relay: A0 01 00 A1
Open  1st relay: A0 01 01 A2 
Close 2nd relay: A0 02 00 A2
Open  2nd relay: A0 02 01 A3
Close 3rd relay: A0 03 00 A3
Open  3rd relay: A0 03 01 A4 
Close 4th relay: A0 04 00 A4
Open  4th relay: A0 04 01 A5  
 */
