#include <PubSubClient.h>
#include <WiFi.h>

const char*ssid ="GD3CS";
const char*password =  "GD3123456";

const char*mqttServer = "183.230.40.39";
const char*device_id = "5301200";
const char*product_id = "84760";
const char*authinfo = "fOO6VcvyK=7IjNbEFpGVHqnxjfQ=";
 
WiFiClient espClient;
PubSubClient client(espClient);


void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid,password);
  while (WiFi.status()!= WL_CONNECTED) {
    delay(500);
    Serial.println("Connectingto WiFi..");
  }

  Serial.println("Connectedto the WiFi network");
  client.setServer(mqttServer,6002);
  while (!client.connected()){
    Serial.println("Connectingto MQTT...");
    if (client.connect(device_id,product_id,authinfo )) 
    {
      Serial.println("connected");
    }else {
      Serial.print("failedwith state ");
      Serial.println(client.state());
      delay(500);
    }
  }
  client.publish("esp/test","Hello from ESP32");
}
 
void loop() {
  client.loop();
}
