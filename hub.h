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
};

// needs to be included after class declared
//#include "Faces/calendar.h"
#include "Faces/analog.h"

//-- triggered by showWatchFace() 
void WatchyFaceX::drawWatchFace() {
  WatchyFaceX::drawFaceAnalog(isDarkMode, enableInteractive);
  //&WatchyFaceX::drawFaceCalendar,
}                                         


#endif
