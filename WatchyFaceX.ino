
#include <WiFi.h>
#include <time.h>

#include "main.h"
#include "settings.h"
//#include "secrets.h"

// Persist across deep sleeps; resets when fully powered off or after full flash
RTC_DATA_ATTR bool s_firstBootNtpDone = false;

// Vancouver, with DST rules:
// "PST8PDT,M3.2.0,M11.1.0" = switch on 2nd Sunday in March and 1st Sunday in November.
static const char* TZ_VANCOUVER = "PST8PDT,M3.2.0,M11.1.0";

// --- Fallback: set RTC from firmware build time (UTC-agnostic; just "close enough") ---
void setRTCFromBuildTime() {
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
bool firstBootSyncNTP(const char* ntpServer) {
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
  configTzTime(TZ_VANCOUVER, ntpServer);

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

void ensureCorrectTimeOnFreshBoot(const char* ntpServer) {
  if (s_firstBootNtpDone) {
    return; // Already synced at least once since flashing
  }

  if (firstBootSyncNTP(ntpServer)) {
    s_firstBootNtpDone = true;
    return;
  }

  // If NTP failed (no Wi-Fi), seed the RTC with firmware build time as a safe fallback
  setRTCFromBuildTime();
  // We’ll mark it done, but the next time Wi-Fi is available you can re-sync explicitly if you want.
  s_firstBootNtpDone = true;
}

WatchyFaceX watchy(settings); //instantiate watch face

void setup() {
  const char* timezone = "PST8PDT,M3.2.0,M11.1.0"; // America/Vancouver
  // https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv

  setenv("TZ", timezone, 1);

  watchy.init();

  ensureCorrectTimeOnFreshBoot(settings.ntpServer);
}

void loop() {
  // put your main code here, to run repeatedly:
}


