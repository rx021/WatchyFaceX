#ifndef MAIN_H
#define MAIN_H

#include <Watchy.h> // include Watchy library

// font to use
#include <Fonts/FreeMonoOblique24pt7b.h>
#include "DSEG7_Classic_Bold_25.h"

RTC_DATA_ATTR bool isDarkMode = false;

class WatchyFaceX : public Watchy{
  using Watchy::Watchy;
  public: 
    void drawWatchFace();
    virtual void handleButtonPress(); // Must be virtual in Watchy.h too
};

void WatchyFaceX::handleButtonPress() {
  if (guiState == WATCHFACE_STATE) {
    uint64_t wakeupBit = esp_sleep_get_ext1_wakeup_status();

    if (wakeupBit && UP_BTN_MASK) {
      Watchy::handleButtonPress();
      return;
    }

    if (wakeupBit && DOWN_BTN_MASK) {
      Watchy::handleButtonPress();
      return;
    }

    if (wakeupBit && BACK_BTN_MASK) {
      isDarkMode = (isDarkMode ? false : true);
      RTC.read(currentTime);
      showWatchFace(true);
      return;
    }

    if (wakeupBit && MENU_BTN_MASK) {
      Watchy::handleButtonPress();
      return;
    }

  }

  Watchy::handleButtonPress();

  return;
}

void WatchyFaceX::drawWatchFace() {
  // TODO: extract this logic to separte watchface
  display.fillScreen(isDarkMode ? GxEPD_DARKGREY : GxEPD_LIGHTGREY);
  display.setTextColor(isDarkMode ? GxEPD_WHITE : GxEPD_BLACK);
  display.setFont(&DSEG7_Classic_Bold_25);
  display.setCursor(25, 110);

  String timeString = "";

  if (currentTime.Hour < 10){
    timeString += "0";
    //display.print("0");
  }
  timeString += currentTime.Hour;
  //display.print(currentTime.Hour);

  timeString += ":";
  //display.print(":");

  if (currentTime.Minute < 10){
    //display.print("0");
    timeString += "0";
  }
  timeString += currentTime.Minute;
  timeString += "_";

  display.println(timeString);
}                                         

#endif
