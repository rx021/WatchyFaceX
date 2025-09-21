
void WatchyFaceX::drawFaceCountdowwn(
  bool enableDarkMode,
  bool enableInteractive
) {
  uint16_t bgColor = enableDarkMode ? GxEPD_BLACK : GxEPD_WHITE; 
  uint16_t textColor = enableDarkMode ? GxEPD_WHITE : GxEPD_BLACK; 

  display.setFullWindow();
  display.fillScreen(bgColor);

  String message = "COUNTDOWN";

  drawFaceTitle(display, title, textColor);

  // DRAW TIMER NUMBERS
  display.setFont(&DSEG7_Classic_Bold_25);
  display.setTextColor(textColor);
  String timeString = "00:00:00";

  int16_t  x1, y1;
  uint16_t w, h;
  display.getTextBounds(timeString, 0, 0, &x1, &y1, &w, &h);

  uint8_t timeX = (DISPLAY_WIDTH / 2) - (w/2);
  uint8_t timeY = (DISPLAY_HEIGHT / 2) + (h/2);
  display.setCursor(timeX, timeY);
  display.println(timeString);
}

