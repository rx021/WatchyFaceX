

void WatchyFaceX::drawFaceMessages(bool enableDarkMode) {
  uint16_t bgColor = enableDarkMode ? GxEPD_BLACK : GxEPD_WHITE; 
  uint16_t textColor = enableDarkMode ? GxEPD_WHITE : GxEPD_BLACK; 
  display.fillScreen(bgColor);

  // MESSAGES
  display.setTextColor(textColor);

  int16_t  x1, y1;
  uint16_t width, height;
  String timeString = "FreeSans9pt7b";
  
  // TEST 01
  display.setFont(&FreeSans9pt7b);
  timeString = "FreeSans9pt7b";
  display.getTextBounds(timeString, 0, 0, &x1, &y1, &width, &height);
  display.setCursor(hourX, hourY);
  display.print(timeString);
                          
  // TEST 02
  display.setFont(&FreeSans12pt7b);
  timeString = "FreeSans12pt7b";
  display.getTextBounds(timeString, 0, 0, &x1, &y1, &width, &height);
  display.setCursor(hourX, hourY);
  display.print(timeString);


  // TEST 03
  display.setFont(&FreeSans18pt7b);
  timeString = "FreeSans18pt7b";
  display.getTextBounds(timeString, 0, 0, &x1, &y1, &width, &height);
  display.setCursor(hourX, hourY);
  display.print(timeString);

  // TEST 04
  display.setFont(&FreeSans24pt7b);
  timeString = "FreeSans24pt7b";
  display.getTextBounds(timeString, 0, 0, &x1, &y1, &width, &height);
  display.setCursor(hourX, hourY);
  display.print(timeString);
}

