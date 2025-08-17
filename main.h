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
    void drawFace0(bool enableDarkMode);
    void drawBattery(
      bool enableDarkMode,
      uint8_t batteryXOffset,
      uint8_t batteryYOffset,
      uint8_t batteryWidth
    );
    virtual void handleButtonPress(); // Must be virtual in Watchy.h too
};

#include "icons.h"
#include "fonts.h"
#include "face0.h"

void WatchyFaceX::handleButtonPress() {
  if (guiState == WATCHFACE_STATE) {
    uint64_t wakeupBit = esp_sleep_get_ext1_wakeup_status();

    // NOTE:
    // careful of this condition 
    // for buttons to work
    if (wakeupBit & BACK_BTN_MASK) {
      isDarkMode = (isDarkMode ? false : true);
      RTC.read(currentTime);
      showWatchFace(true);
      return;
    }

    if (wakeupBit & MENU_BTN_MASK) {
      Watchy::handleButtonPress();
      return;
    }

    if (wakeupBit & UP_BTN_MASK) {
      Watchy::handleButtonPress();
      return;
    }

    if (wakeupBit & DOWN_BTN_MASK) {
      Watchy::handleButtonPress();
      return;
    }

  } else {Watchy::handleButtonPress();}
  return;
}

void WatchyFaceX::drawWatchFace() {
  drawFace0(isDarkMode);
}                                         

#endif
