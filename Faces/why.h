
void WatchyFaceX::drawFaceWhy(bool enableDarkMode) {
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

  // WHY?:
  display.setFont(&FreeSans9pt7b);
  message = "Start w WHY? vision?";
  display.getTextBounds(message, 0, 0, &x1, &y1, &width, &height);
  uint8_t mX = PADDING_X;
  int8_t mY = PADDING_Y + (-1 *  y1);
  // y1 is better to use instead of height here if we want the height of the font
  display.setCursor(mX, mY);
  display.println(message);
  display.println("why go on?");

  display.setFont(&FreeSansBold9pt7b);
  display.println("to Explr Love Give");
  display.println("moralDuty OPTIMISM");
  display.println("ROIspeed Fdbk Sync");
  display.println("WuWei ESC 80/20");
  display.println("lack clarity");
  display.println("antifrgl essntl gratefl");
}

