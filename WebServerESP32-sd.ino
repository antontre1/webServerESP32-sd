#include <SD.h>
#include <SPI.h>
#include <WiFi.h>
#include <ESPAsyncWebSrv.h>
#include "WifiManager.h"
#include "TemperatureManager.h"
#include "DatabaseManager.h"
#include "ApiManager.h"

void setup() {
  if (!SD.begin()) {
    Serial.println("Card failed, or not present");
    while (1);
  }
  Serial.println("Card initialized.");

  Serial.begin(115200);
  initWiFi();
  initTemperatureManager();
  initDatabaseManager();
  initApiManager();
}

void loop() {
  // Nothing to loop here
}
