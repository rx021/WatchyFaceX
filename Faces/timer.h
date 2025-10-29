
void WatchyFaceX::drawFaceTimer(
  bool enableDarkMode,
  bool enableInteractive
) {
  uint16_t bgColor = enableDarkMode ? GxEPD_BLACK : GxEPD_WHITE; 
  uint16_t textColor = enableDarkMode ? GxEPD_WHITE : GxEPD_BLACK; 

  display.setFullWindow();
  display.fillScreen(bgColor);
  display.setFont(&FreeSansBold12pt7b);
  display.setTextColor(textColor);

  int16_t  x1, y1;
  uint16_t w, h;

  String message = "TIMER";
  display.getTextBounds(message, 0, 0, &x1, &y1, &w, &h);
  uint8_t mX = 1; // PADDING_X;
  int8_t mY = 1 + (-1 *  y1); // PADDING_Y + (-1 *  y1);
  // y1 is better to use instead of height here if we want the height of the font

  display.setCursor(mX, mY);
  display.println(message);
}
