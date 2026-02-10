#ifndef MAIN_H
#define MAIN_H

#include <Watchy.h> // include Watchy library

RTC_DATA_ATTR bool isDarkMode = false;
RTC_DATA_ATTR bool enableInteractive = false;

class WatchyFaceX : public Watchy{
  using Watchy::Watchy;
  public: 
    void drawWatchFace();

    // HELPERS
    void drawFaceAnalog(
      bool enableDarkMode,
      bool enableInteractive
    );
};

// needs to be included after class declared
#include "Faces/analog.h"

//-- triggered by showWatchFace() 
void WatchyFaceX::drawWatchFace() {
  WatchyFaceX::drawFaceAnalog(isDarkMode, enableInteractive);
}                                         


#endif
