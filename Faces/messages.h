
template<typename GFX>
inline void bottomCenterText(
    GFX &display,
    const String &s,
    int centerX,
    int originY,
    int textColor
){
  int16_t x1,y1; uint16_t w,h;
  display.getTextBounds(s, 0, originY, &x1, &y1, &w, &h);

  display.setCursor(centerX - w, originY);
  display.setFont(&Seven_Segment10pt7b);
  display.setTextColor(textColor);
  display.print(s);
}

void WatchyFaceX::drawFaceMessages(
  bool enableDarkMode,
  bool enableInteractive
) {
  uint8_t PADDING_X = 1; // pixels
  uint8_t PADDING_Y = 1; // pixels
  uint16_t bgColor = enableDarkMode ? GxEPD_BLACK : GxEPD_WHITE; 
  uint16_t textColor = enableDarkMode ? GxEPD_WHITE : GxEPD_BLACK; 
  display.fillScreen(bgColor);

  // MESSAGES
  display.setTextColor(textColor);

  int16_t  x1, y1;
  uint16_t width, height;
  String message = "";

  // QUESTIONS:
  display.setFont(&FreeSans9pt7b);
  message = "plyr? Movr Explr Creatr";
  display.getTextBounds(message, 0, 0, &x1, &y1, &width, &height);
  uint8_t mX = PADDING_X;
  int8_t mY = PADDING_Y + (-1 *  y1);
  // y1 is better to use instead of height here if we want the height of the font
  display.setCursor(mX, mY);
  display.println(message);
  display.println("prsna? retrvr bldr sprtn");
  display.println("mntra? I'm/I've enough?");

  display.setFont(&FreeSansBold9pt7b);
  display.println("my blockers? how to PLAY?");

  display.setFont(&FreeSans9pt7b);
  display.println("-friction +focus");
  display.println("+locality -distraction");

  // DRAW DATE from bottom-up: 

  String dateString = "";
  dateString += currentTime.Year + 1970; 
  dateString += monthShortStr(currentTime.Month);
  dateString += "-";

  uint8_t currDay = currentTime.Day;
  if (currDay < 10) { dateString += "0"; }
  dateString += currDay;
  dateString += dayShortStr(currentTime.Wday);

  String timeString = ""; // must declare first to concat numbers
  if (currentTime.Hour < 10) {timeString += "0";}
  timeString += currentTime.Hour; // can add number to string
  timeString += ":";
  if (currentTime.Minute < 10) {timeString += "0";}
  timeString += currentTime.Minute;

  String datetimeString = dateString + timeString;
  bottomLeftText(
      display, 
      datetimeString, 
      DISPLAY_WIDTH / 2, 
      DISPLAY_HEIGHT - PADDING_Y, 
      textColor
  );
}

