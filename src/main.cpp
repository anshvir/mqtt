#include <Arduino.h>
#include <C:\Users\CC\.platformio\packages\framework-arduinoespressif32\libraries\WiFi\src\WiFi.h>
#include <PubSubClient.h>

const char* ssid = "WottaWorkspace";
const char* pass = "vin#223adf";
const char* brokerUser = "";
const char* brokerPass = "";
const char* broker = "broker.mqttdashboard.com";
const char* outTopic = "ansh1947";
const char* inTopic = "ansh1947IsOUT";

WiFiClient espClient;
PubSubClient client(espClient);
long currentTime, lastTime;
int count = 0;
char messages[50];

void setupWifi(){
  delay(100);
  Serial.println("\nConnecting to");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);


  while(WiFi.status() != WL_CONNECTED){
    delay(100);
    Serial.print(".......almost___Done......");
  }
  Serial.print("\nConnected to ");
  Serial.println(ssid);

}

void reconnect(){
  while(!client.connected()){
    if(client.connect("Ansh")){
      client.subscribe(inTopic);
    }
    else{
      delay(10);
    }
  }
}
char receivdPayload[10]; 
void callback(char* topic, byte* payload, unsigned int length ){
  memset(receivdPayload,0, sizeof(receivdPayload));
  //Serial.print("Recived messages; ");
  for(int i = 0; i < length; i++){
    receivdPayload[i] = payload[i];
  }
  //Serial.println(receivdPayload);
  if (strcmp(receivdPayload , "True") == 0){

    Serial.print("led on!");
    digitalWrite(26, HIGH);

  }
  else {
    Serial.print("led off ");
    digitalWrite(26, LOW);
    delay(1000);
  }
  

}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  setupWifi();

  client.setServer(broker, 1883);
  client.setCallback(callback);
}


void loop() {
  // put your main code here, to run repeatedly:

  if (!client.connected()){
    reconnect();
  }
  client.loop();

  // currentTime = millis();
  // if(currentTime - lastTime > 2000){
  //   count++;
  //   sniprintf(messages, 50,"Count: %ld", count);
  //   // Serial.print("Sending messages: ");
  //   // Serial.print(messages);
  //   client.publish(outTopic, messages);
  //   lastTime = millis();
  //   if(count > 50){
  //     count = 0;
  //   } 
  // }

 
}