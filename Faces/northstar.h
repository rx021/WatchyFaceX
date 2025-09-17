
void WatchyFaceX::drawFaceNorthStar(
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
  message = "N* goals SYSTEMS";
  display.getTextBounds(message, 0, 0, &x1, &y1, &width, &height);
  uint8_t mX = PADDING_X;
  int8_t mY = PADDING_Y + (-1 *  y1);
  // y1 is better to use instead of height here if we want the height of the font
  display.setCursor(mX, mY);
  display.println(message);

  display.setFont(&FreeSansBold9pt7b);
  display.println("dy-MDW_tests");
  display.println("dy-444_BldPrmtDlvr");
  display.println("dy-show_your_work");
  display.println("wk-write_newsletter");
  display.println("wk-meetps_hcknghts");
  display.println("qr-12+1_wk_yr_exp");
  display.println("yr-DR_checkup");

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

  String datetimeString = dateString + "-" + timeString;

  // bottomCenterText
  int centerX = DISPLAY_WIDTH / 2;
  int originY = DISPLAY_HEIGHT - PADDING_Y;

  display.getTextBounds(datetimeString, 0, originY, &x1, &y1, &width, &height);

  display.setCursor(centerX - (width/2), originY);
  display.setFont(&Seven_Segment10pt7b);
  display.setTextColor(textColor);
  display.print(datetimeString);

}
