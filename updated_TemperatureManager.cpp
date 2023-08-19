#include "TemperatureManager.h"
#include <RTClib.h> // Bibliothèque pour le module RTC DS3231
#include "DatabaseManager.h"

RTC_DS3231 rtc;

void initTemperatureManager() {
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
}
