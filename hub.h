#ifndef MAIN_H
#define MAIN_H

#include <Watchy.h> // include Watchy library

RTC_DATA_ATTR bool isDarkMode = false;
RTC_DATA_ATTR bool enableInteractive = false;

class WatchyFaceX : public Watchy{
  using Watchy::Watchy;
  public: 
    // HELPERS
    void drawHandX(
      uint8_t handRadius,
      float angle,
      uint8_t lineThickness,
      uint16_t handColor
    );
    String getBatteryPercent();

    // FACES
    void drawWatchFace();

    //void drawFaceCalendar(
      //bool enableDarkMode,
      //bool enableInteractive
    //);
    void drawFaceAnalog(
      bool enableDarkMode,
      bool enableInteractive
    );

    // NOTE: Must be virtual in Watchy.h too
    virtual void handleButtonPress();
};

// needs to be included after class declared
//#include "Faces/calendar.h"
#include "Faces/analog.h"

void WatchyFaceX::handleButtonPress() {
  if (guiState == WATCHFACE_STATE) {
    uint64_t wakeupBit = esp_sleep_get_ext1_wakeup_status();

    // NOTE: beware this condition 
    // for buttons to work
    if (wakeupBit & BACK_BTN_MASK) {
      /*
      // NOTE: order should match FACE_TYPES
      if (faceTypeIndex == 0) {
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
      */

      Watchy::handleButtonPress(); //temp
      return;
    }

    if (wakeupBit & MENU_BTN_MASK) {
      /*
      if (
        faceTypeIndex == 2 // toys
      ) {
        enableInteractive = true;
        RTC.read(currentTime);
        showWatchFace(true);
        return;
      }
      */

      Watchy::handleButtonPress(); //temp
      return;
    }

    if (wakeupBit & UP_BTN_MASK) {
      /*
      faceTypeIndex = (faceTypeIndex-1 < 0)
        ? FACE_TYPE_COUNT-1
        : faceTypeIndex-1;
      // reset when changing face type
      enableInteractive = false;
      RTC.read(currentTime);
      showWatchFace(true);
      */
      Watchy::handleButtonPress(); //temp
      return;
    }

    if (wakeupBit & DOWN_BTN_MASK) {
      /*
      faceTypeIndex = (faceTypeIndex + 1) % FACE_TYPE_COUNT;
      // reset when changing face type
      enableInteractive = false;
      RTC.read(currentTime);
      showWatchFace(true);
      */
      Watchy::handleButtonPress(); //temp
      return;
    }

  } else {Watchy::handleButtonPress();}
  return;
}

//-- triggered by showWatchFace() 
void WatchyFaceX::drawWatchFace() {
  WatchyFaceX::drawFaceAnalog(isDarkMode, enableInteractive);
  //&WatchyFaceX::drawFaceCalendar,
}                                         


#endif
