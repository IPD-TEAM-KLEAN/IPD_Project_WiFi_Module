#include <WEMOS_SHT3X.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <VL53L1X.h>
#include <math.h>

#include "IPD_DEF.h"

VL53L1X sensor;
SHT3X sht30(0x45);

// const char* ssid = "Galaxy Fold 5G0006";
// const char* password = "q01pq01p";
const char* ssid = "Minwoo";
const char* password = "q01pq01p";


//Your Domain name with URL path or IP address with path
String serverName = "http://211.57.119.81:8080";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
unsigned long timerDelay = 2000;
// ------------------------------

float battery = 0.0;
float temp, humi, distance, raw;
String state;

String latitude  = "36.353421301096766";
String longitude = "127.42512015876481";


void setup() {
  Serial.begin (115200);
  Serial.println("Connecting");
  WiFi.begin(ssid, password);
  Wire.begin();
  Wire.setClock(400000);
  
  sensor.setTimeout(500);
  pinMode(A0,INPUT);

  if(!sensor.init()){
    Serial.println("Failed to detect and initialize sensor!");
    while(1);
  }
  sensor.setDistanceMode(VL53L1X::Long);
  sensor.setMeasurementTimingBudget(50000);
  sensor.startContinuous(50);  


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
  raw = analogRead(A0);
  battery=raw/1023.0;
  battery = battery*4.2;
  battery = (3.6-battery)/3.6*100;
  battery = round(battery);
  distance = sensor.read();
  if (distance < 500){
    state = "Active";
  }
  else { 
    state = "Disable";
  }
  
  if ((millis() - lastTime) > timerDelay) {
    if(WiFi.status()== WL_CONNECTED){

      if(sht30.get()==0){
        temp = sht30.cTemp;
        humi = sht30.humidity;

        Battery(latitude, longitude, battery);
        Temperature(latitude,longitude,temp);
        Humidity(latitude,longitude,humi);
        Distance(latitude,longitude,distance,state);
      }
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}

double
round(double x)
{
        double t;

        if (!isfinite(x))
                return (x);

        if (x >= 0.0) {
                t = floor(x);
                if (t - x <= -0.5)
                        t += 1.0;
                return (t);
        } else {
                t = floor(-x);
                if (t + x <= -0.5)
                        t += 1.0;
                return (-t);
        }
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
  Serial.print("Sewer : ");
  Serial.println(json);
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
  Serial.print("Temp : ");
  Serial.println(json);
  http.end();
}

void Humidity(String latitude,String longitude,float humi){
  DynamicJsonDocument doc(40960);
  WiFiClient client;
  HTTPClient http;
  doc["latitude"] = latitude;
  doc["longitude"] = longitude;
  doc["value"] = humi;
  String json;
  serializeJson(doc, json);
  String serverPath = serverName + "/change/humidity";
  http.begin(client, serverPath.c_str()); // 서버와 연결
  http.addHeader("Content-Type","application/json");
  int httpResponseCode = http.POST(json);
  // Response_check(httpResponseCode);
  Serial.print("Humi : ");
  Serial.println(json);
  http.end();
}

void Distance(String latitude,String longitude,float distance, String state){
  DynamicJsonDocument doc(40960);
  WiFiClient client;
  HTTPClient http;
  doc["latitude"] = latitude;
  doc["longitude"] = longitude;
  doc["value"] = distance;
  doc["state"] = state;
  String json;
  serializeJson(doc, json);
  String serverPath = serverName + "/change/distance";
  http.begin(client, serverPath.c_str()); // 서버와 연결
  http.addHeader("Content-Type","application/json");
  int httpResponseCode = http.POST(json);
  // Response_check(httpResponseCode);
  Serial.print("Distance : ");
  Serial.println(json);
  http.end();
}

void Battery(String latitude, String longitude, float battery){
  DynamicJsonDocument doc(40960);
  WiFiClient client;
  HTTPClient http;
  doc["latitude"] = latitude;
  doc["longitude"] = longitude;
  doc["value"] = 96;
  String json;
  serializeJson(doc, json);
  String serverPath = serverName + "/change/battery";
  http.begin(client, serverPath.c_str()); // 서버와 연결
  http.addHeader("Content-Type","application/json");
  int httpResponseCode = http.POST(json);
  // Response_check(httpResponseCode);
  Serial.print("Battery : ");
  Serial.println(json);
  http.end();  
}