
void WatchyFaceX::drawFaceGlobe(
  bool enableDarkMode,
  bool enableInteractive
) {
  uint16_t bgColor = enableDarkMode ? GxEPD_BLACK : GxEPD_WHITE; 
  uint16_t textColor = enableDarkMode ? GxEPD_WHITE : GxEPD_BLACK; 

  display.setFullWindow();
  display.fillScreen(bgColor);

  display.drawBitmap(
    0,
    0,
    8bg_01,
    200,
    200,
    textColor
  );
}

