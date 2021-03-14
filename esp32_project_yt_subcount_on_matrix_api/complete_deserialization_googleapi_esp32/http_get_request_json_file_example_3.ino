#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
 
const char* ssid = "Tony-Stark Indeed";
const char* password =  "73884spk45";
//const char* name="UCcuzwvvUHneSG_AcSkFWQ9Q";
//const char* key="AIzaSyC82IgHM9dMnGIPrd8IMXe74rDnuAbMpOY"; 
 
void setup() {
 
  Serial.begin(115200);
  delay(4000);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
 
}
 
void loop() {
 
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
 
    HTTPClient http;
 
    http.begin("https://www.googleapis.com/youtube/v3/channels?part=statistics&id=UCcuzwvvUHneSG_AcSkFWQ9Q&key=AIzaSyC82IgHM9dMnGIPrd8IMXe74rDnuAbMpOY"); //Specify the URL
    int httpCode = http.GET();                                        //Make the request
 
    if (httpCode > 0) { //Check for the returning code
 
        String payload = http.getString();
        //Serial.println(payload);
          StaticJsonDocument<605> doc;
         deserializeJson(doc,payload);
        //https://arduinojson.org/v6/assistant/
const char* kind = doc["kind"]; // "youtube#channelListResponse"
Serial.println(kind);
const char* etag = doc["etag"]; // "\"xwzn9fn_LczrfK9QS3iZcGzqRGs/4p--d3SDhjj8zQ7_ptLO9cENl0s\""
Serial.println(etag);
int pageInfo_totalResults = doc["pageInfo"]["totalResults"]; // 1
Serial.println(pageInfo_totalResults);
int pageInfo_resultsPerPage = doc["pageInfo"]["resultsPerPage"]; // 1
Serial.println(pageInfo_resultsPerPage);
JsonObject items_0 = doc["items"][0];
const char* items_0_kind = items_0["kind"]; // "youtube#channel"
Serial.println(items_0_kind);
const char* items_0_etag = items_0["etag"]; // "\"xwzn9fn_LczrfK9QS3iZcGzqRGs/r9miCr0YFooyNNpiHF0gsOfa7Ho\""
Serial.println(items_0_etag);
const char* items_0_id = items_0["id"]; // "UCcuzwvvUHneSG_AcSkFWQ9Q"
Serial.println(items_0_id);

JsonObject items_0_statistics = items_0["statistics"];
const char* items_0_statistics_viewCount = items_0_statistics["viewCount"]; // "31439"
Serial.println(items_0_statistics_viewCount);
const char* items_0_statistics_commentCount = items_0_statistics["commentCount"]; // "0"
Serial.println(items_0_statistics_commentCount);
const char* items_0_statistics_subscriberCount = items_0_statistics["subscriberCount"]; // "300"
Serial.println(items_0_statistics_subscriberCount);
bool items_0_statistics_hiddenSubscriberCount = items_0_statistics["hiddenSubscriberCount"]; // false
Serial.println(items_0_statistics_hiddenSubscriberCount);
const char* items_0_statistics_videoCount = items_0_statistics["videoCount"]; // "38"
Serial.println(items_0_statistics_videoCount);
}
 
    else {
      Serial.println("Error on HTTP request");
    }
 
    http.end(); //Free the resources
  }
 
  delay(10000);
 
}
