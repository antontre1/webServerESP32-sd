#include "ApiManager.h"
#include <ESPAsyncWebSrv.h>
#include <ArduinoJson.h>
#include <RTClib.h> // Bibliothèque pour le module RTC DS3231
#include "DatabaseManager.h"
#include "TemperatureManager.h"

AsyncWebServer server(80);
extern RTC_DS3231 rtc;

void initApiManager() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "Hello, ESP32!");
  });

  server.on("/addTemperature", HTTP_POST, [](AsyncWebServerRequest *request){
    if (request->hasParam("temperature", true)) {
      float temperature = request->getParam("temperature", true)->value().toFloat();
      DateTime now = rtc.now();
      int timestamp = now.unixtime();
      String insert_sql = String("INSERT INTO temperatures(value, timestamp) VALUES(") + temperature + ", " + timestamp + ");";
      db_exec(db, insert_sql.c_str());
      request->send(200, "text/plain", "Temperature added to database");
    } else {
      request->send(400, "text/plain", "Missing temperature parameter");
    }
  });

  server.on("/getTemperatures", HTTP_GET, [](AsyncWebServerRequest *request){
    int startTime = request->getParam("startTime")->value().toInt();
    int endTime = request->getParam("endTime")->value().toInt();
    
    String jsonString;
    db_query_temperatures(startTime, endTime, jsonString);
    request->send(200, "application/json", jsonString);
  });

  server.begin();
}
