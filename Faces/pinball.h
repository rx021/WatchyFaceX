
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

    if (digitalRead(BACK_BTN_PIN) == ACTIVE_LOW) {
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

    display.display(true); // full refresh
  }

}
