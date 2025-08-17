#include <Watchy.h> // include Watchy library

// font to use
#include <Fonts/FreeMonoOblique24pt7b.h>
#include "DSEG7_Classic_Bold_25.h"
                                         
#include "settings.h"

#define DARKMODE false

RTC_DATA_ATTR int darkmode = 0;

class WatchyFace2508152300 : public Watchy{
  using Watchy::Watchy;
  public: 
    WatchyFace2508152300(const watchySettings& s) : Watchy(s) {}
    void drawWatchFace();
    virtual void handleButtonPress(); // Must be virtual in Watchy.h too
};

void WatchyFace2508152300::handleButtonPress() {
  if (guiState == WATCHFACE_STATE) {
    uint64_t wakeupBit = esp_sleep_get_ext1_wakeup_status();

    if (wakeupBit && UP_BTN_MASK) {
      display.print("_UP");
      Watchy::handleButtonPress();
      return;
    }

    if (wakeupBit && DOWN_BTN_MASK) {
      display.print("_DWN");
      Watchy::handleButtonPress();
      return;
    }

    if (wakeupBit && BACK_BTN_MASK) {
      display.print("_BK");
      bool isDarkmode = (darkmode == 0);
      darkmode = (isDarkmode ? 0 : 1);
      RTC.read(currentTime);
      showWatchFace(true);
      return;
    }

    if (wakeupBit && MENU_BTN_MASK) {
      display.print("_MN");
      Watchy::handleButtonPress();
      return;
    }

  }

  Watchy::handleButtonPress();

  return;
}

void WatchyFace2508152300::drawWatchFace() {
  bool isDarkmode = (darkmode == 1);
  display.fillScreen(isDarkmode ? GxEPD_DARKGREY : GxEPD_LIGHTGREY);
  display.setTextColor(isDarkmode ? GxEPD_WHITE : GxEPD_BLACK);
  display.setFont(&DSEG7_Classic_Bold_25);
  display.setCursor(25, 110);
  if (currentTime.Hour < 10){
    display.print("0");
  }
  display.print(currentTime.Hour);
  display.print(":");
  if (currentTime.Minute < 10){
    display.print("0");
  }
  display.print(currentTime.Minute);
}

WatchyFace2508152300 m(settings); //instantiate watch face

void setup() {
  // put your setup code here, to run once:
  m.init();
}

void loop() {
  // put your main code here, to run repeatedly:

}
