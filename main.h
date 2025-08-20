#ifndef MAIN_H
#define MAIN_H

#include <Watchy.h> // include Watchy library

// used in faces
#include <Fonts/FreeMonoOblique24pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
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

RTC_DATA_ATTR int faceIndex = 0;
RTC_DATA_ATTR int faceCount = 2;
RTC_DATA_ATTR bool isDarkMode = false;

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
    void drawHandX(
      uint8_t handRadius,
      float angle,
      uint8_t lineThickness,
      uint16_t handColor
    );
    drawFaceMessages(bool enableDarkMode);
    virtual void handleButtonPress(); // Must be virtual in Watchy.h too
};

// needs to be included after class declared
#include "Faces/customBahn.h"
#include "Faces/analog.h"

void WatchyFaceX::drawWatchFace() {
  if (faceIndex == 0) {drawFaceCustomBahn(isDarkMode);}
  if (faceIndex == 1) {drawFaceMessages(isDarkMode);}
  if (faceIndex == 2) {drawFaceCalendar(isDarkMode);}
  if (faceIndex == 3) {drawFaceAnalog(isDarkMode);}
}                                         

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
      faceIndex--;
      if (faceIndex < 0 ) {
        // go back to last if beyond list
        faceIndex = faceCount - 1;
      }
      RTC.read(currentTime);
      showWatchFace(true);
      return;
    }

    if (wakeupBit & DOWN_BTN_MASK) {
      faceIndex++;
      if (faceCount <= faceIndex) {
        // go to first if beyond list
        faceIndex = 0;
      }
      RTC.read(currentTime);
      showWatchFace(true);
      return;
    }

  } else {Watchy::handleButtonPress();}
  return;
}

#endif
