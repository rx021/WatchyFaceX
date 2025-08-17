const uint8_t BATTERY_SEGMENT_WIDTH = 7;
const uint8_t BATTERY_SEGMENT_HEIGHT = 11;
const uint8_t BATTERY_SEGMENT_SPACING = 9;

void WatchyFaceX::drawFace0(bool enableDarkMode) {
  // TODO: test that you use black and white instead
  display.fillScreen(enableDarkMode ? GxEPD_DARKGREY : GxEPD_LIGHTGREY);

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
    display.drawBitmap(158, 73, battery, 37, 21, enableDarkMode ? GxEPD_WHITE : GxEPD_BLACK);
    display.fillRect(163, 78, 27, BATTERY_SEGMENT_HEIGHT, enableDarkMode ? GxEPD_BLACK : GxEPD_WHITE);//clear battery segments

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

    for(int8_t batterySegments = 0; batterySegments < batteryLevel; batterySegments++){
        display.fillRect(163 + (batterySegments * BATTERY_SEGMENT_SPACING), 78, BATTERY_SEGMENT_WIDTH, BATTERY_SEGMENT_HEIGHT, enableDarkMode ? GxEPD_WHITE : GxEPD_BLACK);
    }
}

