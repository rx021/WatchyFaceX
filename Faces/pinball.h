
void WatchyFaceX::drawFacePinball(bool enableDarkMode) {
  uint16_t bgColor = enableDarkMode ? GxEPD_BLACK : GxEPD_WHITE; 
  uint16_t textColor = enableDarkMode ? GxEPD_WHITE : GxEPD_BLACK; 

  display.setFullWindow();
  display.fillScreen(bgColor);
  display.setFont(&FreeSans9pt7b);
  display.setTextColor(textColor);

  Accel acc;

  long previousMillis = 0;
  long intervalMillis = 100;

  uint8_t centerX = DISPLAY_WIDTH / 2;
  uint8_t centerY = DISPLAY_HEIGHT / 2;

  uint8_t ballR = 4;
  uint8_t ballX = centerX - ballR;
  uint8_t ballY = centerY - ballR;
  uint8_t ballIncrements = 16;

  uint8_t xLowerBound = 0 + ballR;
  uint8_t yLowerBound = 0 + ballR;
  uint8_t xUpperBound = DISPLAY_WIDTH - ballR;
  uint8_t yUpperBound = DISPLAY_HEIGHT - ballR;

  while (1) {
    unsigned long currentMillis = millis();

    if (digitalRead(BACK_BTN_PIN) == 0) {
      // ACITVE_LOW (0 or 1) taken from Watchy github
      break;
    }

    if ((currentMillis - previousMillis) <= intervalMillis) {
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

    switch (direction) {
    case DIRECTION_DISP_DOWN:
      display.println("FACE DOWN");
      break;
    case DIRECTION_DISP_UP:
      display.println("FACE UP");
      break;
    case DIRECTION_RIGHT_EDGE:
      display.println("RIGHT EDGE");
      ballX -= ballIncrements;
      if (ballX < xLowerBound) {ballX = xLowerBound;}
      break;
    case DIRECTION_LEFT_EDGE:
      display.println("LEFT EDGE");
      ballX += ballIncrements;
      if (xUpperBound <= ballX) {ballX = xUpperBound;}
      break;
    case DIRECTION_BOTTOM_EDGE:
      display.println("BOTTOM EDGE");
      ballY -= ballIncrements;
      if (ballY < yLowerBound) {ballY = yLowerBound;}
      break;
    case DIRECTION_TOP_EDGE:
      display.println("TOP EDGE");
      ballY += ballIncrements;
      if (yUpperBound <= ballY) {ballY = yUpperBound;}
      break;
    default:
      display.println("ERROR!!!");
      break;
    }

    display.fillCircle(
      ballX,
      ballY,
      ballR,
      textColor
    );

    display.display(true); // full refresh
  }

}
