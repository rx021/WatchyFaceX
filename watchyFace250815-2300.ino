#include <Watchy.h> // include Watchy library

// font to use
#include <Fonts/FreeMonoOblique24pt7b.h>
#include "DSEG7_Classic_Bold_25.h"
                                         
#include "settings.h"

#define DARKMODE false

RTC_DATA_ATTR int darkmode = 0

class WatchyFace2508152300 : public Watchy{
  public: 
    WatchyFace2508152300(const watchySettings& s) : Watchy(s) {}
    void drawWatchFace(){
      display.fillScreen(darkmode == 1 ? GxEPD_DARKGREY : GxEPD_LIGHTGREY);
      display.setTextColor(darkmode == 1 ? GxEPD_WHITE : GxEPD_BLACK);
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
    virtual void handleButtonPress(); // Must be virtual in Watchy.h too
};

void WatchyFace2508152300::handleButtonPress() {
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
      darkmode = (darkmode == 0) ? 1 : 0;
      RTC.read(currentTime)
      showWatchFace(true);
      return;
    }

    if (wakeupBit && MENU_BTN_MASK) {
      Watchy::handleButtonPress();
      return;
    }

  } else {Watchy::handleButtonPress();}

  return;
}

WatchyFace2508152300 m(settings); //instantiate watch face

void setup() {
  // put your setup code here, to run once:
  m.init();
}

void loop() {
  // put your main code here, to run repeatedly:

}
