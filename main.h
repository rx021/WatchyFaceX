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
    void drawBattery(bool enableDarkMode);
    virtual void handleButtonPress(); // Must be virtual in Watchy.h too
};

#include "icons.h"
#include "face0.h"

void WatchyFaceX::handleButtonPress() {
  if (guiState == WATCHFACE_STATE) {
    // TODO: try different faces for up and down
    // - hypothesis: buttons not working
    uint64_t wakeupBit = esp_sleep_get_ext1_wakeup_status();

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

    if (wakeupBit && UP_BTN_MASK) {
      Watchy::handleButtonPress();
      return;
    }

    if (wakeupBit && DOWN_BTN_MASK) {
      Watchy::handleButtonPress();
      return;
    }

  }

  Watchy::handleButtonPress();

  return;
}

void WatchyFaceX::drawWatchFace() {
  // boolean doesn't work? might be buttons don't work
  // TODO: try int toggle rather than boolean
  if (isDarkMode) {
    drawFace0(true);
  } else {
    drawFace0(false);
  }
}                                         

#endif
