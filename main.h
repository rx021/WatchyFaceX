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

RTC_DATA_ATTR int faceTypeIndex = 0;
RTC_DATA_ATTR int clockFacesIndex = 0;
RTC_DATA_ATTR int noteFacesIndex = 0;
RTC_DATA_ATTR int plannerFacesIndex = 0;
RTC_DATA_ATTR int toyFacesIndex = 0;

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

// Type alias for a WatchyFaceX member function: void f(bool)
using FaceFn = void (WatchyFaceX::*)(bool);

static constexpr FaceFn CLOCK_FACES[] = {
  &WatchyFaceX::drawFaceCustomBahn,
  &WatchyFaceX::drawFaceAnalog,
};
static constexpr size_t CLOCK_COUNT = sizeof(CLOCK_FACES) / sizeof(CLOCK_FACES[0]);

static constexpr FaceFn NOTE_FACES[] = {
  &WatchyFaceX::drawFaceWhy,
  &WatchyFaceX::drawFaceNorthStar,
  &WatchyFaceX::drawFaceMessages,
};
static constexpr size_t NOTE_COUNT = sizeof(NOTE_FACES) / sizeof(NOTE_FACES[0]);

static constexpr FaceFn PLANNER_FACES[] = {
  &WatchyFaceX::drawFaceCalendar,
  // calendar (WIP), event, alarms, timer, countdown
};
static constexpr size_t PLANNER_COUNT = sizeof(PLANNER_FACES) / sizeof(PLANNER_FACES[0]);

static constexpr FaceFn TOY_FACES[] = {
  &WatchyFaceX::drawFacePinball,
};
static constexpr size_t TOY_COUNT = sizeof(TOY_FACES) / sizeof(TOY_FACES[0]);

struct FaceType {
  const FaceFn* list;
};

static FaceType FACE_TYPES[] = {
  {CLOCK_FACES},
  {NOTE_FACES},
  {TOY_FACES},
  {PLANNER_FACES},
};
static constexpr size_t FACE_TYPE_COUNT = sizeof(FACE_TYPES) / sizeof(FACE_TYPES[0]);

void WatchyFaceX::drawWatchFace() {
  FaceFn currFace;

  if (faceTypeIndex == 0) {
    currFace = CLOCK_FACES[clockFacesIndex];
    (this->*currFace)(isDarkMode);
  }
  else if (faceTypeIndex == 1) {
    currFace = NOTE_FACES[noteFacesIndex];
    (this->*currFace)(isDarkMode);
  }
  else if (faceTypeIndex == 2) {
    currFace = PLANNER_FACES[plannerFacesIndex];
    (this->*currFace)(isDarkMode);
  }
  else if (faceTypeIndex == 3) {
    currFace = TOY_FACES[toyFacesIndex];
    (this->*currFace)(isDarkMode);
  }
}                                         

void WatchyFaceX::handleButtonPress() {
  if (guiState == WATCHFACE_STATE) {
    uint64_t wakeupBit = esp_sleep_get_ext1_wakeup_status();

    // NOTE:
    // careful of this condition 
    // for buttons to work
    if (wakeupBit & BACK_BTN_MASK) {
      //isDarkMode = (isDarkMode ? false : true);
      if (faceTypeIndex == 0) {
        clockFacesIndex = (clockFacesIndex + 1) % CLOCK_COUNT;
      }
      else if (faceTypeIndex == 1) {
        noteFacesIndex = (noteFacesIndex + 1) % NOTE_COUNT;
      }
      else if (faceTypeIndex == 2) {
        plannerFacesIndex = (plannerFacesIndex + 1) % PLANNER_COUNT;
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
      if (faceTypeIndex < 0) {faceTypeIndex = FACE_TYPE_COUNT - 1;}
      RTC.read(currentTime);
      showWatchFace(true);
      return;
    }

    if (wakeupBit & DOWN_BTN_MASK) {
      faceTypeIndex = (faceTypeIndex + 1) % FACE_TYPE_COUNT;
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
