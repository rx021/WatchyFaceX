#ifndef MAIN_H
#define MAIN_H

#include <Watchy.h> // include Watchy library

// used in faces
#include <Fonts/FreeMonoOblique24pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSansBold9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSansBold12pt7b.h>
#include <Fonts/FreeSans18pt7b.h>
#include <Fonts/FreeSans24pt7b.h>
#include "Fonts/DSEG7_Classic_Bold_25.h"
#include "Fonts/DIN_1451_Engschrift_Regular12pt7b.h"
#include "Fonts/DIN_1451_Engschrift_Regular64pt7b.h"
#include "Fonts/Seven_Segment10pt7b.h"
#include "Fonts/Technology18pt7b.h"
#include "Icons/battery.h"
#include "Icons/charge.h"
#include "Icons/bluetooth.h"
#include "Icons/wifi.h"

RTC_DATA_ATTR bool isDarkMode = false;

// FACE TYPES: clocks, notes, datetime, toys
RTC_DATA_ATTR int faceTypeIndex = 0;
RTC_DATA_ATTR int faceTypeCount = 4;

// bahn, analog
RTC_DATA_ATTR int clockFacesIndex = 0;
RTC_DATA_ATTR int clockFacesCount = 2;
// why, northstar, messages
RTC_DATA_ATTR int noteFacesIndex = 0;
RTC_DATA_ATTR int noteFacesCount = 3;
// (WIP) calendar, event, alarms, timer, countdown
RTC_DATA_ATTR int datetimeFacesIndex = 0;
RTC_DATA_ATTR int datetimeFacesCount = 1;
// pinball
RTC_DATA_ATTR int toyFacesIndex = 0;
RTC_DATA_ATTR int toyFacesCount = 1;


class WatchyFaceX : public Watchy{
  using Watchy::Watchy;
  public: 
    void drawWatchFace();
    void drawFaceCalendar(bool enableDarkMode);
    void drawFaceCustomBahn(bool enableDarkMode);
    void drawBattery(
      bool enableDarkMode,
      uint8_t batteryXOffset,
      uint8_t batteryYOffset,
      uint8_t batteryWidth,
      uint8_t batteryHeight
    );
    void drawFaceAnalog(bool enableDarkMode);
    String getBatteryPercent();
    void drawHandX(
      uint8_t handRadius,
      float angle,
      uint8_t lineThickness,
      uint16_t handColor
    );
    void drawFaceWhy(bool enableDarkMode);
    void drawFaceNorthStar(bool enableDarkMode);
    void drawFaceMessages(bool enableDarkMode);
    void drawFacePinball(bool enableDarkMode);
    virtual void handleButtonPress(); // Must be virtual in Watchy.h too

    // ---- Added: first-boot time setup helpers ----
    /**
    void ensureCorrectTimeOnFreshBoot();
  private:
    bool firstBootSyncNTP();
    void setRTCFromBuildTime();
     */
};

// needs to be included after class declared
#include "Faces/calendar.h"
#include "Faces/customBahn.h"
#include "Faces/analog.h"
#include "Faces/why.h"
#include "Faces/northstar.h"
#include "Faces/messages.h"
#include "Faces/pinball.h"

// ---- Added includes/flag for time sync ----
/**
#include <WiFi.h>
#include <time.h>

// Persist across deep sleeps; resets when fully powered off or after full flash
RTC_DATA_ATTR bool s_firstBootNtpDone = false;

// Vancouver, with DST rules:
// "PST8PDT,M3.2.0,M11.1.0" = switch on 2nd Sunday in March and 1st Sunday in November.
static const char* TZ_VANCOUVER = "PST8PDT,M3.2.0,M11.1.0";
 */

void WatchyFaceX::drawWatchFace() {
  if (faceTypeIndex == 0) {
    if (clockFacesIndex == 0) {drawFaceCustomBahn(isDarkMode);}
    else if (clockFacesIndex == 1) {drawFaceAnalog(isDarkMode);}
  }
  else if (faceTypeIndex == 1) {
    if (noteFacesIndex == 0) {drawFaceWhy(isDarkMode);}
    else if (noteFacesIndex == 1) {drawFaceNorthStar(isDarkMode);}
    else if (noteFacesIndex == 2) {drawFaceMessages(isDarkMode);}
  }
  else if (faceTypeIndex == 2) {
    if (datetimeFacesIndex == 0) {drawFaceCalendar(isDarkMode);}
  }
  else if (faceTypeIndex == 3) {
    if (toyFacesIndex == 0) {drawFacePinball(isDarkMode);}
  }

}                                         

void WatchyFaceX::handleButtonPress() {
  if (guiState == WATCHFACE_STATE) {
    uint64_t wakeupBit = esp_sleep_get_ext1_wakeup_status();

    // NOTE:
    // careful of this condition 
    // for buttons to work
    if (wakeupBit & BACK_BTN_MASK) {
      bool isOutOfBounds = false;
      //isDarkMode = (isDarkMode ? false : true);
      if (faceTypeIndex == 0) {
        clockFacesIndex++;
        isOutOfBounds = (clockFacesCount <= clockFacesIndex);
        if (isOutOfBounds) {clockFacesIndex = 0;}
      }
      else if (faceTypeIndex == 1) {
        noteFacesIndex++;
        isOutOfBounds = (noteFacesCount <= noteFacesIndex);
        if (isOutOfBounds) {noteFacesIndex = 0;}
      }
      else if (faceTypeIndex == 2) {
        datetimeFacesIndex++;
        // go to first if beyond list
        isOutOfBounds = (datetimeFacesCount <= datetimeFacesIndex);
        if (isOutOfBounds) {datetimeFacesIndex = 0;}
      }

      RTC.read(currentTime);
      showWatchFace(true);
      return;
    }

    if (wakeupBit & MENU_BTN_MASK) {
      Watchy::handleButtonPress();
      return;
    }

    if (wakeupBit & UP_BTN_MASK) {
      faceTypeIndex--;
      if (faceTypeIndex < 0) {faceTypeIndex = faceTypeCount - 1;}
      RTC.read(currentTime);
      showWatchFace(true);
      return;
    }

    if (wakeupBit & DOWN_BTN_MASK) {
      faceTypeIndex++;
      // go to first if beyond list
      if (faceTypeCount <= faceTypeIndex) {faceTypeIndex = 0;}
      RTC.read(currentTime);
      showWatchFace(true);
      return;
    }

  } else {Watchy::handleButtonPress();}
  return;
}

/**
// --- Fallback: set RTC from firmware build time (UTC-agnostic; just "close enough") ---
void WatchyFaceX::setRTCFromBuildTime() {
  // Parse __DATE__ "Mmm dd yyyy" and __TIME__ "hh:mm:ss"
  struct tm tmBuild = {0};
  const char *monStr = __DATE__;

  // Month map
  const char* months = "JanFebMarAprMayJunJulAugSepOctNovDec";
  int mon = (strstr(months, monStr) - months) / 3; // 0-11
  int day, year, hour, min, sec;
  sscanf(__DATE__ + 4, "%d %d", &day, &year);
  sscanf(__TIME__, "%d:%d:%d", &hour, &min, &sec);

  tmBuild.tm_year = year - 1900;
  tmBuild.tm_mon  = mon;
  tmBuild.tm_mday = day;
  tmBuild.tm_hour = hour;
  tmBuild.tm_min  = min;
  tmBuild.tm_sec  = sec;

  // Write to RTC (localtime vs UTC won’t matter much for a fallback; it’ll be corrected on next Wi-Fi/NTP)
  RTC.set(tmBuild);
}

// Try to bring up Wi-Fi using whatever your project typically uses.
// If you already have a "connectWiFi()" helper from Watchy lib, call that instead.
bool WatchyFaceX::firstBootSyncNTP() {
  // 1) Turn Wi-Fi on and connect as your project normally does.
  //    If you use WiFiManager or Watchy’s built-ins, call those here.
  WiFi.mode(WIFI_STA);
  // If you rely on saved creds, you can call WiFi.begin() with no args.
  WiFi.begin();
  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < 15000UL) {
    delay(200);
  }
  if (WiFi.status() != WL_CONNECTED) {
    return false;
  }

  // 2) Configure local timezone rules + NTP
  configTzTime(TZ_VANCOUVER, NTP_SERVER);

  // 3) Wait for time
  struct tm localTime;
  if (getLocalTime(&localTime, 10000)) {   // wait up to ~10s
    // 4) Push the synced time into the RTC chip
    RTC.set(localTime);
  }

  // 5) Clean up Wi-Fi to save power
  WiFi.disconnect(true, true);
  WiFi.mode(WIFI_OFF);

  return true;
}

void WatchyFaceX::ensureCorrectTimeOnFreshBoot() {
  if (s_firstBootNtpDone) {
    return; // Already synced at least once since flashing
  }

  if (firstBootSyncNTP()) {
    s_firstBootNtpDone = true;
    return;
  }

  // If NTP failed (no Wi-Fi), seed the RTC with firmware build time as a safe fallback
  setRTCFromBuildTime();
  // We’ll mark it done, but the next time Wi-Fi is available you can re-sync explicitly if you want.
  s_firstBootNtpDone = true;
}
 */

#endif
