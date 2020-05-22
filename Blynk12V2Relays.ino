#include <Blynk.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "yourAuthToken";
char ssid[] = "yourAP-SSID";
char pass[] = "yourAP-Password";
byte relay1ON[]  = {0xA0, 0x01, 0x01, 0xA2};//Hex command to send to serial for close relay
byte relay1OFF[] = {0xA0, 0x01, 0x00, 0xA1};//Hex command to send to serial for open relay
byte relay2ON[]  = {0xA0, 0x02, 0x01, 0xA3};//Hex command to send to serial for close relay
byte relay2OFF[] = {0xA0, 0x02, 0x00, 0xA2};//Hex command to send to serial for open relay

void setup(){
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass, IPAddress(192,168,10,10), 8080);//Change to your IP address
}
void loop(){
  Blynk.run();
}
//Relay board must be in Mode1 to get this working. To get into Mode1, press S1 Button and boot.
BLYNK_WRITE(V1){
  int pinData = param.asInt();
  if(pinData==1){
    Serial.write(relay1ON, sizeof(relay1ON));
  }
  else{
    Serial.write(relay1OFF, sizeof(relay1OFF));
  }
}
BLYNK_WRITE(V2){
  int pinData = param.asInt();
  if(pinData==1){
    Serial.write(relay2ON, sizeof(relay2ON));
  }
  else{
    Serial.write(relay2OFF, sizeof(relay2OFF));
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
