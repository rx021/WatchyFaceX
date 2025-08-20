

void WatchyFaceX::drawFaceCalendar(bool enableDarkMode) {
  uint16_t bgColor = enableDarkMode ? GxEPD_BLACK : GxEPD_WHITE; 
  uint16_t textColor = enableDarkMode ? GxEPD_WHITE : GxEPD_BLACK; 
  display.fillScreen(bgColor);

  // CALENDAR
  display.setTextColor(textColor);

  display.setFont(&DIN_1451_Engschrift_Regular64pt7b);
  String timeString = ""; // must declare first to concat numbers

  display.setCursor(hourX, hourY);
  display.print(timeString);
}
