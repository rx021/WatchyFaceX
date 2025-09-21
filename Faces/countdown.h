
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

  String timeString = "00:00:00";

  drawCenterTime(display, timeString, textColor);
}

