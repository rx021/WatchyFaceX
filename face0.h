
// NOTE: top left is X=0, Y=0
// NOTE: bottom right is X=200, Y=200

const uint8_t SCREEN_HEIGHT = 200; // pixels
const uint8_t PADDING_X = 15; // pixels
const uint8_t PADDING_Y = 15; // pixels

void WatchyFaceX::drawFace0(bool enableDarkMode) {
  uint16_t bgColor = enableDarkMode ? GxEPD_BLACK : GxEPD_WHITE; 
  uint16_t textColor = enableDarkMode ? GxEPD_WHITE : GxEPD_BLACK; 
  display.fillScreen(bgColor);

  // BATTERY ICON
  uint8_t batteryWidth = 37;
  uint8_t batteryHeight = 21;
  drawBattery(
    enableDarkMode,
    PADDING_X,
    PADDING_Y,
    batteryWidth,
    batteryHeight
  );

  // CHARGE ICON
  uint8_t iconSpacing = 5;
  uint8_t chargeXPosn = PADDING_X + batteryWidth + iconSpacing;
  uint8_t chargeYPosn = PADDING_Y + 2;
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

  // WIFI ICON
  uint8_t wifiX = PADDING_X;
  uint8_t wifiY = PADDING_Y + batteryHeight + iconSpacing;
  uint8_t wifiWidth = 26;
  uint8_t wifiHeight = 18;
  display.drawBitmap(
    wifiX,
    wifiY,
    WIFI_CONFIGURED ? wifi : wifioff,
    wifiWidth,
    wifiHeight,
    textColor
  );

  // BLUETOOTH ICON
  uint8_t bluetoothX = wifiX + wifiWidth + iconSpacing;
  uint8_t bluetoothY = chargeYPosn;
  uint8_t bluetoothWidth = 13;
  uint8_t bluetoothHeight = 21;
  if(BLE_CONFIGURED){
    display.drawBitmap(
      bluetoothX,
      bluetoothY,
      bluetooth,
      bluetoothWidth,
      bluetoothHeight,
      textColor
    );
  }

  // DATETIME SETUP:
  
  int16_t  x1, y1;
  uint16_t w, h;

  display.setTextColor(textColor);

  uint8_t centerX = 100;
  uint8_t centerY = 100;

  // TIME:
  String timeString = "";
  display.setFont(&DIN_1451_Engschrift_Regular64pt7b);
  display.setTextWrap(false);

  //draw hours
  timeString = currentTime.Hour;
  display.getTextBounds(timeString, 0, 0, &x1, &y1, &w, &h);
  uint8_t hourX = 183 - w;
  uint8_t hourY = centerY - 5;
  display.setCursor(hourX, hourY);
  display.print(timeString);

  //draw minutes
  timeString = "";
  if (currentTime.Minute < 10) {timeString += "0";}
  timeString += currentTime.Minute;
  display.getTextBounds(timeString, 0, 0, &x1, &y1, &w, &h);
  uint8_t minuteY = centerY + 3 + h;
  display.setCursor(hourX, minuteY);
  display.print(timeString);


  // DATE from bottom-up: 

  int16_t lastY = SCREEN_HEIGHT - PADDING_Y;
  int8_t dateSpacing = 20;

  // DRAW WEEKDAY
  display.setFont(&DIN_1451_Engschrift_Regular12pt7b);
  String dateString = dayStr(currentTime.Wday);

  display.getTextBounds(dateString, 0, 0, &x1, &y1, &w, &h);
  display.setCursor(PADDING_X, lastY);
  display.print(dateString);
  lastY -= dateSpacing;

  // DRAW DATE
  display.setFont(&DSEG7_Classic_Bold_25);
  dateString = monthShortStr(currentTime.Month);
  dateString += " ";
  dateString += currentTime.Day;

  display.getTextBounds(dateString, 0, 0, &x1, &y1, &w, &h);
  display.setCursor(PADDING_X, lastY);
  display.print(dateString);
  lastY -= dateSpacing;

  // DRAW YEAR
  display.setFont(&DIN_1451_Engschrift_Regular12pt7b);
  dateString = currentTime.Year + 1970;

  display.getTextBounds(dateString, 0, 0, &x1, &y1, &w, &h);
  display.setCursor(PADDING_X, lastY);
  display.print(dateString);
}

void WatchyFaceX::drawBattery(
    bool enableDarkMode,
    uint8_t batteryXOffset,
    uint8_t batteryYOffset,
    uint8_t batteryWidth,
    uint8_t batteryHeight
){
  uint16_t bgColor = enableDarkMode ? GxEPD_BLACK : GxEPD_WHITE; 
  uint16_t textColor = enableDarkMode ? GxEPD_WHITE : GxEPD_BLACK; 

  // BATTERY IMAGE
  display.drawBitmap(
    batteryXOffset,
    batteryYOffset,
    battery,
    batteryWidth,
    batteryHeight,
    textColor
  );

  uint8_t segmentXOffset = batteryXOffset + 5;
  uint8_t segmentYOffset = batteryYOffset + 5;
  uint8_t segmentHeight = 11;

  // BATTERY CLEAR SEGMENTS
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

    // BATTERY FILLED SEGMENTS
    display.fillRect(
      xPosn,
      segmentYOffset,
      segmentWidth,
      segmentHeight,
      textColor
    );
  }
}

