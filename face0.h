
// NOTE: top left is X=0, Y=0
// NOTE: bottom right is X=200, Y=200

const uint8_t BATTERY_X_OFFSET = 15; // pixels
const uint8_t BATTERY_Y_OFFSET = 15;
const uint8_t BATTERY_WIDTH = 37;

void WatchyFaceX::drawFace0(bool enableDarkMode) {
  uint16_t bgColor = enableDarkMode ? GxEPD_BLACK : GxEPD_WHITE; 
  uint16_t textColor = enableDarkMode ? GxEPD_WHITE : GxEPD_BLACK; 
  display.fillScreen(bgColor);

  drawBattery(
    enableDarkMode,
    BATTERY_X_OFFSET,
    BATTERY_Y_OFFSET,
    BATTERY_WIDTH
  );

  uint8_t iconSpacing = 5;
  uint8_t chargeXPosn = BATTERY_X_OFFSET + BATTERY_WIDTH + iconSpacing;
  uint8_t chargeYPosn = BATTERY_Y_OFFSET + 2;
  uint8_t chargeWidth = 16;

  #ifdef ARDUINO_ESP32S3_DEV
  if(USB_PLUGGED_IN){
    display.drawBitmap(
      chargeXPosn,
      chargeYPosn,
      charge,
      chargeWidth,
      18,
      textColor
    );
  }
  #endif

  uint8_t wifiXPosn = chargeXPosn + chargeWidth + iconSpacing;
  uint8_t wifiWidth = 26;
  display.drawBitmap(
    116,
    chargeYPosn,
    WIFI_CONFIGURED ? wifi : wifioff,
    wifiWidth,
    18,
    textColor
  );

  uint8_t bluetoothXPosn = wifiXPosn + wifiWidth + iconSpacing;
  if(BLE_CONFIGURED){
    display.drawBitmap(
      bluetoothXPosn,
      chargeYPosn,
      bluetooth,
      13,
      21,
      textColor
    );
  }


  // DATETIME SETUP:
  
  int16_t  x1, y1;
  uint16_t w, h;

  display.setTextColor(textColor);

  // TIME:
  String timeString = "";
  display.setFont(&DSEG7_Classic_Bold_25);
  display.setTextWrap(false);

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


  // DATE from bottom-up: 
  String dateString;
  int16_t lastY = 200 - 16;
  display.setFont(&DIN_1451_Engschrift_Regular12pt7b);

  // draw weekday
  dateString = dayStr(currentTime.Wday);

  display.getTextBounds(dateString, 0, 0, &x1, &y1, &w, &h);
  display.setCursor(BATTERY_X_OFFSET, lastY);
  display.print(dateString);
  lastY += -40;

  // draw date
  dateString = monthShortStr(currentTime.Month);
  dateString += " ";
  dateString += currentTime.Day;

  display.getTextBounds(dateString, 0, 0, &x1, &y1, &w, &h);
  display.setCursor(BATTERY_X_OFFSET, lastY);
  display.print(dateString);
  lastY += -40;

   // draw year
  dateString = currentTime.Year + 1970;

  display.getTextBounds(dateString, 0, 0, &x1, &y1, &w, &h);
  display.setCursor(BATTERY_X_OFFSET, lastY);
  display.print(dateString);
  lastY += -80;

}

void WatchyFaceX::drawBattery(
    bool enableDarkMode,
    uint8_t batteryXOffset,
    uint8_t batteryYOffset,
    uint8_t batteryWidth
){
  uint16_t bgColor = enableDarkMode ? GxEPD_BLACK : GxEPD_WHITE; 
  uint16_t textColor = enableDarkMode ? GxEPD_WHITE : GxEPD_BLACK; 
  // battery IMAGE
  display.drawBitmap(
    batteryXOffset,
    batteryYOffset,
    battery,
    batteryWidth,
    21,
    textColor
  );

  uint8_t segmentXOffset = batteryXOffset + 5;
  uint8_t segmentYOffset = batteryYOffset + 5;

  uint8_t segmentHeight = 11;

  // battery clear segments
  display.fillRect(
    segmentXOffset,
    segmentYOffset,
    27,
    segmentHeight,
    bgColor
  );

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

    // battery filled segments
    display.fillRect(
      xPosn,
      segmentYOffset,
      segmentWidth,
      segmentHeight,
      textColor
    );
  }
}

