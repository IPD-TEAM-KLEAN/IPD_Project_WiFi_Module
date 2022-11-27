#include <WEMOS_SHT3X.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

#define echoPin D7 // Echo Pin
#define trigPin D6 // Trigger Pin
#define tempPin A0 // DHT pin

// const char* ssid = "Galaxy Fold 5G0006";
// const char* password = "q01pq01p";
const char* ssid = "lim";
const char* password = "abc1234@";


//Your Domain name with URL path or IP address with path
String serverName = "http://211.57.119.81:8080";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;
// ------------------------------

long duration, distance; // Duration used to calculate distance
String latitude  = "36.353421301096766";
String longitude = "127.42512015876481";

bool state;

void setup() {
  Serial.begin (115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(tempPin, INPUT);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  delay(500);
  Sewer(latitude,longitude);
}

void loop() {
  // Send an HTTP POST request depending on timerDelay

  // Temperature Measurement
  int reading = analogRead(tempPin);
  reading = map(reading,0,1023,0,3300);
  float temp = (reading - 550) * 0.1;  

  // Distance Measurement
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  //Calculate the distance (in cm) based on the speed of sound.
  distance = duration/58.2;        

  if(distance < 20){
    state = false;
  }
  else{
    state = true;
  }

  if ((millis() - lastTime) > timerDelay) {
    if(WiFi.status()== WL_CONNECTED){

      Temperature(latitude,longitude,temp);
      Ultrasonic(latitude,longitude,distance,state);
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
  Serial.print(" END ");
  Serial.println(state);
}

void Sewer(String latitude,String longitude){
  DynamicJsonDocument doc(40960);
  WiFiClient client;
  HTTPClient http;
  doc["latitude"] = latitude;
  doc["longitude"] = longitude;
  String json;
  serializeJson(doc, json);
  String serverPath = serverName + "/create/sewer";
  http.begin(client, serverPath.c_str()); // 서버와 연결
  http.addHeader("Content-Type","application/json");
  int httpResponseCode = http.POST(json);
  // Response_check(httpResponseCode);
  http.end();
}

void Temperature(String latitude,String longitude,float temp){
  DynamicJsonDocument doc(40960);
  WiFiClient client;
  HTTPClient http;
  doc["latitude"] = latitude;
  doc["longitude"] = longitude;
  doc["value"] = temp;
  String json;
  serializeJson(doc, json);
  String serverPath = serverName + "/change/temperature";
  http.begin(client, serverPath.c_str()); // 서버와 연결
  http.addHeader("Content-Type","application/json");
  int httpResponseCode = http.POST(json);
  // Response_check(httpResponseCode);
  http.end();
}

void Ultrasonic(String latitude,String longitude,float distance,bool state){
  DynamicJsonDocument doc(40960);
  WiFiClient client;
  HTTPClient http;  
  doc["latitude"] = latitude;
  doc["longitude"] = longitude;
  if(state==true){
    doc["state"] = "Active";
  }
  else {
    doc["state"] = "Disable";
  }
  doc["value"] = distance;
  String json;
  serializeJson(doc, json);
  String serverPath = serverName + "/change/block";
  http.begin(client, serverPath.c_str()); // 서버와 연결
  http.addHeader("Content-Type","application/json");
  int httpResponseCode = http.POST(json);
  // Response_check(httpResponseCode);
  http.end();
  Serial.print(" Void : ");
  Serial.println(state);
}

// void Response_check(int httpResponseCode){
//   HTTPClient http;  
//   if (httpResponseCode>0) {
//     Serial.print("HTTP Response code: ");
//     Serial.println(httpResponseCode);
//     String payload = http.getString();
//     Serial.println(payload);
//   }
//   else {
//     Serial.print("Error code: ");
//     Serial.println(httpResponseCode);
//   }
// }