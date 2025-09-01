
void WatchyFaceX::drawFacePinball(bool enableDarkMode) {
  uint16_t bgColor = enableDarkMode ? GxEPD_BLACK : GxEPD_WHITE; 
  uint16_t textColor = enableDarkMode ? GxEPD_WHITE : GxEPD_BLACK; 

  display.setFullWindow();
  display.fillScreen(bgColor);
  display.setFont(&FreeSans9pt7b);
  display.setTextColor(textColor);

  Accel acc;

  long previousMillis = 0;
  long interval = 200;

  while (1) {
    unsigned long currentMillis = millis();

    if (digitalRead(BACK_BTN_PIN) == 0) {
      // ACITVE_LOW (0,1) taken from Watchy github
      break;
    }

    if ((currentMillis - previousMillis) <= interval) {
      continue;
    }

    // ACTION PER INTERVAL
    
    previousMillis = currentMillis;

    // Get acceleration data
    bool res = sensor.getAccel(acc);
    uint8_t direction = sensor.getDirection();

    display.fillScreen(bgColor);
    display.setCursor(0, 30);

    if (res == false) {
      display.println("getAccel FAIL");
      display.display(true); // full refresh
      continue;
    }

    display.setCursor(30, 130);
    switch (direction) {
    case DIRECTION_DISP_DOWN:
      display.println("FACE DOWN");
      break;
    case DIRECTION_DISP_UP:
      display.println("FACE UP");
      break;
    case DIRECTION_BOTTOM_EDGE:
      display.println("BOTTOM EDGE");
      break;
    case DIRECTION_TOP_EDGE:
      display.println("TOP EDGE");
      break;
    case DIRECTION_RIGHT_EDGE:
      display.println("RIGHT EDGE");
      break;
    case DIRECTION_LEFT_EDGE:
      display.println("LEFT EDGE");
      break;
    default:
      display.println("ERROR!!!");
      break;
    }

    display.display(true); // full refresh
  }

}
