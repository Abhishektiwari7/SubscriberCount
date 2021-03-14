#include <HardwareSerial.h>
HardwareSerial sender( 2 );
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#define RXD2 16
#define TXD2 17
 
const char* ssid = "Tony-Stark Indeed";
const char* password =  "73884spk45";
int sub;
const char* serialdata;
const char* subCount;

void setup() {
  Serial.begin(9600);
   Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
   delay(500);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 }

void loop() {
  subscriber();
  Serial.println(sub);
  UART_esp32_to_arduino();
  
}




void subscriber()
{     if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
 
    HTTPClient http;
    http.begin("https://www.googleapis.com/youtube/v3/channels?part=statistics&id=UCcuzwvvUHneSG_AcSkFWQ9Q&key=AIzaSyC82IgHM9dMnGIPrd8IMXe74rDnuAbMpOY"); //Specify the URL
    int httpCode = http.GET();                                        //Make the request
    if (httpCode > 0) 
     { 
    String mydata = http.getString();
    StaticJsonDocument<605> doc;
    deserializeJson(doc,mydata);
    JsonObject items0 = doc["items"][0];
    JsonObject itemstat = items0["statistics"];
    subCount = itemstat["subscriberCount"];
    //Serial.println(subCount);
    sub=atoi(subCount); 
    }
 
  else {
      Serial.println("Error on HTTP request");
       }
 
    http.end(); //Free the resources
  }
  }


void UART_esp32_to_arduino()
{   serialdata = subCount;
  Serial2.write(serialdata); //Write the serial data
     delay(500);
  Serial.println("");
    }


  
