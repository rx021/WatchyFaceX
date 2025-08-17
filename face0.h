
const uint8_t BATTERY_SEGMENT_WIDTH = 7; // pixels
const uint8_t BATTERY_SEGMENT_HEIGHT = 11;
const uint8_t BATTERY_SEGMENT_SPACING = 9;
const uint8_t BATTERY_X_OFFSET = 163;
const uint8_t BATTERY_Y_OFFSET = 78;

void WatchyFaceX::drawFace0(bool enableDarkMode) {
  // toggle appears to work now; but greys don't work
  // test black and white instead
  display.fillScreen(enableDarkMode ? GxEPD_BLACK : GxEPD_WHITE);

  display.setTextColor(enableDarkMode ? GxEPD_WHITE : GxEPD_BLACK);
  display.setFont(&DSEG7_Classic_Bold_25);
  display.setCursor(5, 110);

  String timeString = "";

  if (currentTime.Hour < 10){
    timeString += "0";
  }
  timeString += currentTime.Hour;
  timeString += ":";

  if (currentTime.Minute < 10){
    timeString += "0";
  }
  timeString += currentTime.Minute;
  timeString += "-:.";

  display.println(timeString);

  #ifdef ARDUINO_ESP32S3_DEV
  if(USB_PLUGGED_IN){
    display.drawBitmap(140, 75, charge, 16, 18, enableDarkMode ? GxEPD_WHITE : GxEPD_BLACK);
  }
  #endif

  drawBattery(enableDarkMode);
}

void WatchyFaceX::drawBattery(bool enableDarkMode){
  // battery IMAGE
  display.drawBitmap(158, 73, battery, 37, 21, enableDarkMode ? GxEPD_WHITE : GxEPD_BLACK);

  // battery clear segments
  display.fillRect(BATTERY_X_OFFSET, BATTERY_Y_OFFSET, 27, BATTERY_SEGMENT_HEIGHT, enableDarkMode ? GxEPD_BLACK : GxEPD_WHITE);

  int8_t batteryLevel = 0;
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

  int8_t xPosn = 0; // x position

  for(int8_t batterySegments = 0; batterySegments < batteryLevel; batterySegments++){
    xPosn = BATTERY_X_OFFSET + (batterySegments * BATTERY_SEGMENT_SPACING);

    display.fillRect(xPosn, BATTERY_Y_OFFSET, BATTERY_SEGMENT_WIDTH, BATTERY_SEGMENT_HEIGHT, enableDarkMode ? GxEPD_WHITE : GxEPD_BLACK);
  }
}

