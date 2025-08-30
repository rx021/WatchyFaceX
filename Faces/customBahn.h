
// NOTE: top left is X=0, Y=0
// NOTE: bottom right is X=200, Y=200

void WatchyFaceX::drawFaceCustomBahn(bool enableDarkMode) {
  uint8_t PADDING_X = 5; // pixels
  uint8_t PADDING_Y = 5; // pixels
  uint16_t bgColor = enableDarkMode ? GxEPD_BLACK : GxEPD_WHITE; 
  uint16_t textColor = enableDarkMode ? GxEPD_WHITE : GxEPD_BLACK; 
  display.fillScreen(bgColor);

  // BATTERY ICON
  uint8_t batteryX = PADDING_X;
  uint8_t batteryY = PADDING_Y;
  uint8_t batteryWidth = 37;
  uint8_t batteryHeight = 21;
  drawBattery(
    enableDarkMode,
    batteryX,
    batteryY,
    batteryWidth,
    batteryHeight
  );

  uint8_t halfBatteryHeight = batteryHeight / 2;

  int16_t  x1, y1;
  uint16_t w, h;

  uint8_t iconSpacing = 5;

  // BATTERY PERCENT
  uint8_t batteryPercent = 0;
  float VBAT = getBatteryVoltage();

  if (4.2 <= VBAT){
    batteryPercent = 100.0;
  }
  else if (3.3 <= VBAT) {
    batteryPercent = 100.0 * (VBAT - 3.3) / 0.9;
  }
  String percentString = "";
  percentString += batteryPercent;
  percentString += "% ";
  display.getTextBounds(percentString, 0, 0, &x1, &y1, &w, &h);
  uint8_t percentWidth = w;
  uint8_t percentHeight = h;
  uint8_t halfPercentHeight = percentHeight / 2;
  uint8_t percentX = batteryX + batteryWidth + iconSpacing;
  uint8_t percentY = batteryY + halfBatteryHeight + halfPercentHeight;
  display.setCursor(percentX, percentY);
  display.setFont(&DIN_1451_Engschrift_Regular12pt7b);
  display.setTextColor(textColor);
  display.print(percentString);

  // CHARGE ICON
  uint8_t chargeWidth = 16;
  uint8_t chargeHeight = 18;
  uint8_t halfChargeHeight = chargeHeight / 2;
  uint8_t chargeX = percentX + percentWidth + iconSpacing;
  uint8_t chargeY = batteryY + halfBatteryHeight - halfChargeHeight;
  #ifdef ARDUINO_ESP32S3_DEV
  if(USB_PLUGGED_IN){
    display.drawBitmap(
      chargeX,
      chargeY,
      charge,
      chargeWidth,
      chargeHeight,
      textColor
    );
  }
  #endif

  // WIFI ICON
  uint8_t wifiX = batteryX;
  uint8_t wifiY = batteryY + batteryHeight + iconSpacing;
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
  uint8_t bluetoothY = wifiY;
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
  
  display.setTextColor(textColor);

  uint8_t centerX = 100;
  uint8_t centerY = 100;

  // TIME:
  
  display.setFont(&DIN_1451_Engschrift_Regular64pt7b);
  display.setTextWrap(false);
  uint8_t timeSpacing = 6; // must be even number
  String timeString = ""; // must declare first to concat numbers

  //draw hours
  timeString += currentTime.Hour; // can add number to string
  display.getTextBounds(timeString, 0, 0, &x1, &y1, &w, &h);
  uint8_t hourWidth = w;
  uint8_t hourHeight = h;
  uint8_t hourX = DISPLAY_WIDTH - PADDING_X - hourWidth;
  uint8_t hourY = centerY - (timeSpacing / 2);
  display.setCursor(hourX, hourY);
  display.print(timeString);

  //draw minutes
  timeString = "";
  if (currentTime.Minute < 10) {timeString += "0";}
  timeString += currentTime.Minute;
  display.getTextBounds(timeString, 0, 0, &x1, &y1, &w, &h);
  uint8_t minuteWidth = w;
  uint8_t minuteHeight = h;
  uint8_t minuteX = DISPLAY_WIDTH - PADDING_X - minuteWidth;
  uint8_t minuteY = centerY - (timeSpacing / 2) + minuteHeight;
  display.setCursor(minuteX, minuteY);
  display.print(timeString);

  // DATE from bottom-up: 

  int8_t dateSpacing = 10;

  // DRAW WEEKDAY
  display.setFont(&DIN_1451_Engschrift_Regular12pt7b);
  String dateString = dayStr(currentTime.Wday);

  display.getTextBounds(dateString, 0, 0, &x1, &y1, &w, &h);
  uint8_t weekdayX = PADDING_X;
  uint8_t weekdayY = DISPLAY_HEIGHT - PADDING_Y;
  uint8_t weekdayWidth = w;
  uint8_t weekdayHeight = h;
  display.setCursor(weekdayX, weekdayY);
  display.print(dateString);

  // DRAW DATE
  display.setFont(&Technology18pt7b);
  dateString = monthShortStr(currentTime.Month);
  dateString += " ";
  dateString += currentTime.Day;

  display.getTextBounds(dateString, 0, 0, &x1, &y1, &w, &h);
  uint8_t dateX = weekdayX;
  uint8_t dateY = weekdayY - weekdayHeight - dateSpacing;
  uint8_t dateWidth = w;
  uint8_t dateHeight = h;
  display.setCursor(dateX, dateY);
  display.print(dateString);

  // DRAW YEAR
  display.setFont(&DIN_1451_Engschrift_Regular12pt7b);
  dateString = currentTime.Year + 1970;

  display.getTextBounds(dateString, 0, 0, &x1, &y1, &w, &h);
  uint8_t yearX = dateX;
  uint8_t yearY = dateY - dateHeight - dateSpacing;
  uint8_t yearWidth = w;
  uint8_t yearHeight = h;
  display.setCursor(yearX, yearY);
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


