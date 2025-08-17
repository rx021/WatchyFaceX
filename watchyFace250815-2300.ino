
#include "main.h"
#include "settings.h"
#include "secrets.h"

//#include <WiFi.h>
//#include <RTClib.h>
//#include <TimeLib.h>
//#include <time.h>

WatchyFaceX watchy(settings); //instantiate watch face

void setup() {
  const char* timezone = "PST8PDT,M3.2.0,M11.1.0"; // America/Vancouver

  setenv("TZ", timezone, 1);

  //struct tm timeinfo;
  //String datetime;
  const char* ntp_server = "pool.ntp.org";
  // find yours:
  // https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv

  // trying to connect to WiFi and obtain current date and time from ntp time server
  //WiFi.begin(ssid, password);
  //delay(3000);
  //if (WiFi.status() == WL_CONNECTED) {
    //char timeStringBuff[50];
    //configTime(0, 0, ntp_server);
    //configTime()
    //getLocalTime(&timeinfo);
    //WiFi.disconnect(true);
    //WiFi.mode(WIFI_OFF);
    //strftime(
      //timeStringBuff,
      //sizeof(timeStringBuff),
      //"%Y:%m:%d:%H:%M:%S",
      //&timeinfo
    //);
    //datetime = timeStringBuff;

  // otherwise take compile date and time
  //} else {
    //char timeStringBuff[] = "YYYY:MM:DD:hh:mm:ss";
    //DateTime compileTime = DateTime(F(__DATE__), F(__TIME__));  
    //datetime = compileTime.toString(timeStringBuff);
  //}

  // initialising watchy with date and time as "Year:Month:Day:Hour:Minute:Second" on reset
  //watchy.init(datetime);
  watchy.init();
}

void loop() {
  // put your main code here, to run repeatedly:
}
