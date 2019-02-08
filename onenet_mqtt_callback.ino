#include <8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
 
#define BUILTIN_LED 2
 
// Update these with values suitable for your network.
 
const char*ssid ="GD3CS";
const char*password =  "GD3123456";

const char*mqttServer = "183.230.40.39";
const char*device_id = "5301200";
const char*product_id = "84760";
const char*authinfo = "fOO6VcvyK=7IjNbEFpGVHqnxjfQ=";
 
WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
char msg_buf[200];
int value = 0;  //
char dataTemplete[]={"temperature:25.5,time:%d"};
char msgJson[75];
char debug_buf[200];
char st;
int i;
unsigned short json_len=0;
uint8_t*packet_p;
uint8_t*debug_buffer_start_index;
 
//设置wifi 
void setup_wifi() { 
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid); 
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  randomSeed(micros()); 
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

//回调函数进程
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  payload[length] = 0;
  Serial.println((char*)payload);
   
//灯光显示
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, HIGH);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, LOW);  // Turn the LED off by making the voltage HIGH
  }
}
//重新连接
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(device_id,product_id,authinfo)) { 
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(500);
    }
  }
}
//初始化
void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output, where do it esp32 get gpio2 as led
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqttServer, 6002);  //not 1883 , one net use the port of 6002 as mqtt server
  client.connect(device_id,product_id,authinfo);
  client.setCallback(callback);
  digitalWrite(BUILTIN_LED, HIGH);
}

//循环 
void loop() {
 
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
