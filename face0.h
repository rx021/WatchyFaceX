
// NOTE: top left is X=0, Y=0
// NOTE: bottom right is X=200, Y=200

const uint8_t BATTERY_X_OFFSET = 15; // pixels
const uint8_t BATTERY_Y_OFFSET = 15;
const uint8_t BATTERY_WIDTH = 37;

void WatchyFaceX::drawFace0(bool enableDarkMode) {
  display.fillScreen(enableDarkMode ? GxEPD_BLACK : GxEPD_WHITE);

  drawBattery(enableDarkMode);

  #ifdef ARDUINO_ESP32S3_DEV
  if(USB_PLUGGED_IN){
    uint8_t chargeXPosn = BATTERY_X_OFFSET + 18;
    uint8_t chargeYPosn = BATTERY_Y_OFFSET + 2;
    display.drawBitmap(chargeXPosn, chargeYPosn, charge, 16, 18, enableDarkMode ? GxEPD_WHITE : GxEPD_BLACK);
  }
  #endif

  // DATE 
  
  int16_t  x1, y1, lasty;
  uint16_t w, h;

  lasty = 200 - 16;

  //draw steps
  //display.setFont(&DIN_1451_Engschrift_Regular12pt7b);
  display.setFont(&DSEG7_Classic_Bold_25);
  display.setTextColor(enableDarkMode ? GxEPD_WHITE : GxEPD_BLACK);

  lasty += -8 - h;

  String dateString;

   // draw year
  dateString = currentTime.Year + 1970;
  display.getTextBounds(dateString, 0, 0, &x1, &y1, &w, &h);
  display.setCursor(16, lasty);
  display.print(dateString);
  lasty += -20;

  // draw date
  dateString = monthShortStr(currentTime.Month);
  dateString += " ";
  dateString += currentTime.Day;
  display.getTextBounds(dateString, 0, 0, &x1, &y1, &w, &h);
  display.setCursor(16, lasty);
  display.print(dateString);
  lasty += -20;

  // draw day
  dateString = dayStr(currentTime.Wday);
  display.getTextBounds(dateString, 0, 0, &x1, &y1, &w, &h);
  display.setCursor(16, lasty);
  display.print(dateString);
  lasty += -40;


  // TIME:
  display.setTextWrap(false);

  String timeString = "";

  //draw hours
  timeString = currentTime.Hour;
  display.getTextBounds(timeString, 0, 0, &x1, &y1, &w, &h);
  display.setCursor(183 - w, 100 - 5);
  display.print(timeString);

  //draw minutes
  if (currentTime.Minute < 10) {
    timeString = "0";
  } else {
    timeString = "";
  }
  timeString += currentTime.Minute;
  display.getTextBounds(timeString, 0, 0, &x1, &y1, &w, &h);
  display.setCursor(183 - w, 100 + 3 + h);
  display.print(timeString);
}

void WatchyFaceX::drawBattery(bool enableDarkMode){
  // battery IMAGE
  display.drawBitmap(BATTERY_X_OFFSET, BATTERY_Y_OFFSET, battery, BATTERY_WIDTH, 21, enableDarkMode ? GxEPD_WHITE : GxEPD_BLACK);

  uint8_t segmentXOffset = BATTERY_X_OFFSET + 5;
  uint8_t segmentYOffset = BATTERY_Y_OFFSET + 5;

  uint8_t segmentHeight = 11;

  // battery clear segments
  display.fillRect(segmentXOffset, segmentYOffset, 27, segmentHeight, enableDarkMode ? GxEPD_BLACK : GxEPD_WHITE);

  uint8_t batteryLevel = 0;
  float VBAT = getBatteryVoltage();
  if(VBAT > 4.0){
      batteryLevel = 3;
  }
  else if(VBAT > 3.6 && VBAT <= 4.0){
      batteryLevel = 2;
  }
  else if(VBAT > 3.20 && VBAT <= 3.6){
      batteryLevel = 1;
  }
  else if(VBAT <= 3.20){
      batteryLevel = 0;
  }

  uint8_t xPosn = 0; // x position
  uint8_t segmentWidth = 7;
  uint8_t segmentSpacing = 9;

  for(int8_t batterySegments = 0; batterySegments < batteryLevel; batterySegments++){
    xPosn = segmentXOffset + (batterySegments * segmentSpacing);

    display.fillRect(xPosn, segmentYOffset, segmentWidth, segmentHeight, enableDarkMode ? GxEPD_WHITE : GxEPD_BLACK);
  }
}

