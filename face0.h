
// NOTE: top left is X=0, Y=0
// NOTE: bottom right is X=200, Y=200

const uint8_t BATTERY_X_OFFSET = 15; // pixels
const uint8_t BATTERY_Y_OFFSET = 15;
const uint8_t BATTERY_WIDTH = 37;

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
  // timeString += "-:."; // only special characters that render

  display.println(timeString);

  #ifdef ARDUINO_ESP32S3_DEV
  if(USB_PLUGGED_IN){
    uint8_t chargeXPosn = BATTERY_X_OFFSET + 18;
    uint8_t chargeYPosn = BATTERY_Y_OFFSET + 2;
    display.drawBitmap(chargeXPosn, chargeYPosn, charge, 16, 18, enableDarkMode ? GxEPD_WHITE : GxEPD_BLACK);
  }
  #endif

  drawBattery(enableDarkMode);
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

