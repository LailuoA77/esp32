
#include "WiFi.h"
const char*ssid ="GD3CS";
const char*ssid_pass = "GD3123456";
unsigned int a;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(ssid,ssid_pass);
  while (WiFi.status()!= WL_CONNECTED) 
  {
    delay(500);
    Serial.println("Connectingto WiFi..");
  }
   Serial.println("IP address: ");
   Serial.println(WiFi.localIP());

}

void loop() {
  // put your main code here, to run repeatedly:
   Serial.printf("IP address: ");
   Serial.println(WiFi.localIP());
  Serial.printf("计数%d\n",a);
  delay(500);
  a++;

}
