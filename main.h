#ifndef MAIN_H
#define MAIN_H

#include <Watchy.h> // include Watchy library

// used in faces
//#include <Fonts/FreeMonoOblique24pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSansBold9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSansBold12pt7b.h>
//#include <Fonts/FreeSans18pt7b.h>
//#include <Fonts/FreeSans24pt7b.h>
#include "Fonts/DSEG7_Classic_Bold_25.h"
#include "Fonts/DIN_1451_Engschrift_Regular12pt7b.h"
#include "Fonts/DIN_1451_Engschrift_Regular64pt7b.h"
#include "Fonts/Seven_Segment10pt7b.h"
#include "Fonts/Technology18pt7b.h"
#include "Icons/battery.h"
#include "Icons/charge.h"
#include "Icons/bluetooth.h"
#include "Icons/wifi.h"
#include "Images/globe.h"
#include "Images/media.h"

RTC_DATA_ATTR bool isDarkMode = false;
RTC_DATA_ATTR bool enableInteractive = false;

RTC_DATA_ATTR int faceTypeIndex = 0;

RTC_DATA_ATTR int plannerFacesIndex = 0;
RTC_DATA_ATTR int noteFacesIndex = 0;
RTC_DATA_ATTR int toyFacesIndex = 0;

class WatchyFaceX : public Watchy{
  using Watchy::Watchy;
  public: 
    // HELPERS
    void drawBattery(
      bool enableDarkMode,
      uint8_t batteryXOffset,
      uint8_t batteryYOffset,
      uint8_t batteryWidth,
      uint8_t batteryHeight
    );
    String getBatteryPercent();
    void drawHandX(
      uint8_t handRadius,
      float angle,
      uint8_t lineThickness,
      uint16_t handColor
    );
    // FACES
    void drawWatchFace();
    void drawFaceGlobe(
      bool enableDarkMode,
      bool enableInteractive
    );
    void drawFaceMedia(
      bool enableDarkMode,
      bool enableInteractive
    );
    void drawFaceCalendar(
      bool enableDarkMode,
      bool enableInteractive
    );
    void drawFaceAlarms(
      bool enableDarkMode,
      bool enableInteractive
    );
    void drawFaceTimer(
      bool enableDarkMode,
      bool enableInteractive
    );
    void drawFaceCountdowwn(
      bool enableDarkMode,
      bool enableInteractive
    );
    void drawFaceCustomBahn(
      bool enableDarkMode,
      bool enableInteractive
    );
    void drawFaceAnalog(
      bool enableDarkMode,
      bool enableInteractive
    );
    void drawFaceWhy(
      bool enableDarkMode,
      bool enableInteractive
    );
    void drawFaceNorthStar(
      bool enableDarkMode,
      bool enableInteractive
    );
    void drawFaceMessages(
      bool enableDarkMode,
      bool enableInteractive
    );
    void drawFacePinball(
      bool enableDarkMode,
      bool enableInteractive
    );
    void drawFacePinballX(
      bool enableDarkMode,
      bool enableInteractive
    );
    // NOTE: Must be virtual in Watchy.h too
    virtual void handleButtonPress();
};

// needs to be included after class declared
#include "Faces/globe.h"
#include "Faces/media.h"
#include "Faces/calendar.h"
#include "Faces/alarms.h"
#include "Faces/timer.h"
#include "Faces/countdown.h"
#include "Faces/customBahn.h"
#include "Faces/analog.h"
#include "Faces/why.h"
#include "Faces/northstar.h"
#include "Faces/messages.h"
#include "Faces/pinball.h"
#include "Faces/pinballX.h"

// Type alias for a WatchyFaceX member function: void f(bool)
using FaceFn = void (WatchyFaceX::*)(bool, bool);

static constexpr FaceFn PLANNER_FACES[] = {
  &WatchyFaceX::drawFaceCalendar,
  &WatchyFaceX::drawFaceCustomBahn,
  &WatchyFaceX::drawFaceAnalog,
  //&WatchyFaceX::drawFaceAlarms,
  &WatchyFaceX::drawFaceTimer,
  &WatchyFaceX::drawFaceCountdowwn,
};
static constexpr size_t PLANNER_COUNT = sizeof(PLANNER_FACES) / sizeof(PLANNER_FACES[0]);

static constexpr FaceFn NOTE_FACES[] = {
  &WatchyFaceX::drawFaceWhy,
  &WatchyFaceX::drawFaceNorthStar,
  &WatchyFaceX::drawFaceMessages,
};
static constexpr size_t NOTE_COUNT = sizeof(NOTE_FACES) / sizeof(NOTE_FACES[0]);

static constexpr FaceFn TOY_FACES[] = {
  &WatchyFaceX::drawFaceGlobe,
  &WatchyFaceX::drawFaceMedia,
  &WatchyFaceX::drawFacePinballX,
  //&WatchyFaceX::drawFacePinball,
};
static constexpr size_t TOY_COUNT = sizeof(TOY_FACES) / sizeof(TOY_FACES[0]);

struct FaceType {
  const FaceFn* list;
};
static FaceType FACE_TYPES[] = {
  {PLANNER_FACES},
  {NOTE_FACES},
  {TOY_FACES},
};
static constexpr size_t FACE_TYPE_COUNT = sizeof(FACE_TYPES) / sizeof(FACE_TYPES[0]);

void WatchyFaceX::handleButtonPress() {
  if (guiState == WATCHFACE_STATE) {
    uint64_t wakeupBit = esp_sleep_get_ext1_wakeup_status();

    // NOTE: beware this condition 
    // for buttons to work
    if (wakeupBit & BACK_BTN_MASK) {
      // NOTE: order should match FACE_TYPES
      if (faceTypeIndex == 0) {
        // reset when changing face
        enableInteractive = false;
        plannerFacesIndex = (plannerFacesIndex + 1) % PLANNER_COUNT;
      }
      else if (faceTypeIndex == 1) {
        noteFacesIndex = (noteFacesIndex + 1) % NOTE_COUNT;
      }
      else if (faceTypeIndex == 2) {
        // reset when changing face
        enableInteractive = false;
        toyFacesIndex = (toyFacesIndex + 1) % TOY_COUNT;
      }

      RTC.read(currentTime);
      showWatchFace(true);
      return;
    }

    if (wakeupBit & MENU_BTN_MASK) {
      if (
        faceTypeIndex == 0 // planner
        faceTypeIndex == 2 // toys
      ) {
        enableInteractive = true;
        RTC.read(currentTime);
        showWatchFace(true);
        return;
      }

      Watchy::handleButtonPress();
      return;
    }

    if (wakeupBit & UP_BTN_MASK) {
      faceTypeIndex = (faceTypeIndex-1 < 0)
        ? FACE_TYPE_COUNT-1
        : faceTypeIndex-1;
      // reset when changing face type
      enableInteractive = false;
      RTC.read(currentTime);
      showWatchFace(true);
      return;
    }

    if (wakeupBit & DOWN_BTN_MASK) {
      faceTypeIndex = (faceTypeIndex + 1) % FACE_TYPE_COUNT;
      // reset when changing face type
      enableInteractive = false;
      RTC.read(currentTime);
      showWatchFace(true);
      return;
    }

  } else {Watchy::handleButtonPress();}
  return;
}

//-- triggered by showWatchFace() 
void WatchyFaceX::drawWatchFace() {
  FaceFn currFace;

  if (faceTypeIndex == 0) {
    currFace = PLANNER_FACES[plannerFacesIndex];
    (this->*currFace)(isDarkMode, enableInteractive);
  }
  else if (faceTypeIndex == 1) {
    currFace = NOTE_FACES[noteFacesIndex];
    (this->*currFace)(isDarkMode, enableInteractive);
  }
  else if (faceTypeIndex == 2) {
    currFace = TOY_FACES[toyFacesIndex];
    (this->*currFace)(isDarkMode, enableInteractive);
  }
}                                         

#endif
