
void WatchyFaceX::drawFaceNorthStar(bool enableDarkMode) {
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
  message = "N* goals SYSTEMS";
  display.getTextBounds(message, 0, 0, &x1, &y1, &width, &height);
  uint8_t mX = PADDING_X;
  int8_t mY = PADDING_Y + (-1 *  y1);
  // y1 is better to use instead of height here if we want the height of the font
  display.setCursor(mX, mY);
  display.println(message);
  display.println("tyi96k twi1850 tdi370");

  display.setFont(&FreeSansBold9pt7b);
  display.println("dy-MDW_tests");
  display.println("dy-444_BldPrmtDlvr");
  display.println("dy-show_your_work");
  display.println("wk-write_newsletter");
  display.println("wk-meetps_hcknghts");
  display.println("qr-12+1_wk_yr_exp");
  display.println("yr-DR_checkup");
}
