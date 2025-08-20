
const uint8_t CELL_X_WIDTH = 26; // pixels
const uint8_t CELL_X_GAP = 3; // pixels
const uint8_t CELL_Y_HEIGHT = 18; // pixels
const uint8_t CELL_Y_GAP = 8; // pixels

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
