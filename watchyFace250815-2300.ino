#include <Watchy.h> // include Watchy library

// font to use
#include <Fonts/FreeMonoOblique24pt7b.h>
                                         
#include "settings.h"

class WatchyFace2508152300 : public Watchy{
  public: 
    WatchyFace2508152300(const watchySettings& s) : Watchy(s) {}
    void drawWatchFace(){
      display.setFont(&FreeMonoOblique24pt7b);
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
};

WatchyFace2508152300 m(settings); //instantiate watch face

void setup() {
  // put your setup code here, to run once:
  m.init();
}

void loop() {
  // put your main code here, to run repeatedly:

}
