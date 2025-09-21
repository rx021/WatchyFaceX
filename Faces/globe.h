
RTC_DATA_ATTR int globeIndex = 0;
RTC_DATA_ATTR int globeCount = 14;

void WatchyFaceX::drawFaceGlobe(
  bool enableDarkMode,
  bool enableInteractive
) {
  uint16_t bgColor = enableDarkMode ? GxEPD_BLACK : GxEPD_WHITE; 
  uint16_t textColor = enableDarkMode ? GxEPD_WHITE : GxEPD_BLACK; 

  display.setFullWindow();

  auto drawImageAtIndex = [&]() {
    display.fillScreen(bgColor);
    const unsigned char *curr = globes[globeIndex];
    display.drawBitmap(0, 0, curr, 200, 200, textColor);
    display.display(true); // full refresh
  };

  if (!enableInteractive) {
    drawImageAtIndex();
    drawFaceTitle(display, "GLOBE", textColor);
    return;
  }

  long lastMs = 0;
  long updateIntervalMs = 400;

  const unsigned char* currGlobe;

  while (1) {
    unsigned long now = millis();

    // ACITVE_LOW (0 or 1) taken from Watchy github
    if (digitalRead(BACK_BTN_PIN) == 0) { break; }
    if ((now - lastMs) <= updateIntervalMs) { continue; }

    // ACTION PER INTERVAL
    lastMs = now;

    drawImageAtIndex();
                           
    globeIndex = (globeIndex + 1) % globeCount;

    // only show initially so that we can switch between faces
    if (!enableInteractive) { break; }
  }

  // After exiting game loop, show one navigation frame
  drawImageAtIndex();
  drawFaceTitle(display, "GLOBE", textColor);
}

