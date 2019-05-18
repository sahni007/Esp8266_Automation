/*
This is test code for automation using esp8266 only for 4 switches
For test i am using CloudMWtt broker: https://www.cloudmqtt.com/
and for server i am using MQTTLens
this code is working for 4 switches with MQTT lens and cloudmqtt 

*/


#include <ESP8266WiFi.h>
#include <PubSubClient.h>
//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
#include <EEPROM.h>
#define XBEE_DATA_LENGTH 8*2
#define FALSE 0
#define TRUE 1
const char* ssid = "Xiaomi";
const char* password =  "appansch";
const char* mqttServer = "postman.cloudmqtt.com";
const int mqttPort =  18086;
const char* mqttUser = "ndlpnzdg";
const char* mqttPassword = "gToNyPhITSLf";



#define OUTPUT_RELAY1 D0
#define OUTPUT_RELAY2 D1
#define OUTPUT_RELAY3 D2
#define OUTPUT_RELAY4 D3 


//data related to external interrupt
const int interruptPin = 0; //GPIO 0 (Flash Button) 
volatile byte interruptCounter = 0;
int numberOfInterrupts = 0;
int HotSpotStartFlag = FALSE;



      unsigned char ServerDataReceivedBuffer[XBEE_DATA_LENGTH]="0";
      unsigned char tempServerDataReceivedBuffer[XBEE_DATA_LENGTH]="0";
      unsigned int ServerDataPosition=0;
      unsigned int ServerDataReceivedFlag = FALSE;

unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 5000;           // interval at which to blink (milliseconds)

void copyServerDataReceiver();
void applicationControl(char SwitchNumber, char switchState);
WiFiClient espClient;
PubSubClient client(espClient);
void setup() {
 
  Serial.begin(9600);
   
   pinMode(OUTPUT_RELAY1,OUTPUT);
    pinMode(OUTPUT_RELAY2,OUTPUT);
      pinMode(OUTPUT_RELAY3,OUTPUT);
        pinMode(OUTPUT_RELAY4,OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP); 
  attachInterrupt(digitalPinToInterrupt(interruptPin), handleInterrupt, CHANGE); 

  //wifi related data

  /* Set ESP32 to WiFi Station mode */
          WiFiManager wifiManager;
         wifiManager.autoConnect("skybot");
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.print(".");
//  }
//  Serial.println("WiFi Connected.");
//  Serial.print("IP Address: ");
//  Serial.println(WiFi.localIP());
//   WiFi.begin(ssid, password);
// 
//   while (WiFi.status() != WL_CONNECTED) {
//                      delay(500);
//                      Serial.print(".");
//                    }
//                    Serial.println();
//                  
//                    Serial.println("WiFi connected");
//                    Serial.println("IP address: "); 
//                    Serial.println(WiFi.localIP());
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }

}
 
  client.publish("esp/auto", "Hello from ESP8266");
  client.subscribe("esp/auto");
 
}
 void handleInterrupt() {
  Serial.println("Interrupt_Detected");
  interruptCounter++;
}
void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  for (int i = 0; i <= 15; i++) {
   // Serial.print((char)payload[i]);
   if(payload[0] == '%'){
    ServerDataReceivedBuffer[ServerDataPosition]=(char)payload[i];
     ServerDataPosition++;
   // Serial.write(ServerDataReceivedBuffer[ServerDataPosition]);//ok
    if(ServerDataPosition > 15)
    {
      ServerDataReceivedFlag = TRUE;
      ServerDataPosition = 0;
   //   copyServerDataReceiver();
       // Serial.write(tempServerDataReceivedBuffer[1]);Serial.write(tempServerDataReceivedBuffer[2]);
   //   applicationControl(tempServerDataReceivedBuffer[1],tempServerDataReceivedBuffer[2]); ///pass switch_lsb and switch_state
     
    //  Serial.println("DataReceived");
    }
   }
  }
 
  Serial.println();
  Serial.println("-----------------------");

}
 
void loop() {

    client.loop();
     if(ServerDataReceivedFlag == TRUE){
     ServerDataReceivedFlag = FALSE;
     if(ServerDataReceivedBuffer[0] == '%' && ServerDataReceivedBuffer[1] == '%' && ServerDataReceivedBuffer[14]== '@'){
     //Serial.println("OK");
      copyServerDataReceiver();
    // Serial.write(tempServerDataReceivedBuffer[1]);Serial.write(tempServerDataReceivedBuffer[2]);
      applicationControl(tempServerDataReceivedBuffer[1],tempServerDataReceivedBuffer[2]);
     }
  }

}

void applicationControl(char SwitchNumber, char switchState){
  int sw_state = switchState - '0';
  switch(SwitchNumber)
  {
    case '1':{
      digitalWrite(OUTPUT_RELAY1,sw_state);
      Serial.println("LOAD1");
    }
      break;
    case '2':{
      digitalWrite(OUTPUT_RELAY2,sw_state);
      Serial.println("LOAD2");
    }
      break;
    case '3':{
      digitalWrite(OUTPUT_RELAY3,sw_state);
      Serial.println("LOAD3");
    }
      break;
    case '4':{
      digitalWrite(OUTPUT_RELAY4,sw_state);
      Serial.println("LOAD4");
    }
      break;
      default:
      break;
  }
  
  
  
  }
void copyServerDataReceiver(){
 // Serial.println("enter in copy");
      int dataBufferCounter = 2;
    for(dataBufferCounter = 2;dataBufferCounter < 9 ;dataBufferCounter++){
        tempServerDataReceivedBuffer[dataBufferCounter-2] = ServerDataReceivedBuffer[dataBufferCounter]; // copy data buffer from server
     //   Serial.write(tempServerDataReceivedBuffer[dataBufferCounter-2]);
        ServerDataReceivedBuffer[dataBufferCounter]='#';  // clean data buffer
    }
}
