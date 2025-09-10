
RTC_DATA_ATTR int mediaIndex = 0;
RTC_DATA_ATTR int mediaCount = 14;

void WatchyFaceX::drawFaceMedia(
  bool enableDarkMode,
  bool enableInteractive
) {
  uint16_t bgColor = enableDarkMode ? GxEPD_BLACK : GxEPD_WHITE; 
  uint16_t textColor = enableDarkMode ? GxEPD_WHITE : GxEPD_BLACK; 

  display.setFullWindow();

  auto drawFrame = [&]() {
    display.fillScreen(bgColor);
    display.drawBitmap(0, 0, cabin, 200, 200, textColor);
    display.display(true); // full refresh
  };

  if (!enableInteractive) {
    drawFrame();
    return;
  }

  long lastMs = 0;
  long updateIntervalMs = 400;

  const unsigned char* currMedia;

  while (1) {
    unsigned long now = millis();

    // ACITVE_LOW (0 or 1) taken from Watchy github
    if (digitalRead(BACK_BTN_PIN) == 0) { break; }
    if ((now - lastMs) <= updateIntervalMs) { continue; }

    // ACTION PER INTERVAL
    lastMs = now;
    currMedia = medias[mediaIndex];

    display.fillScreen(bgColor);
    display.drawBitmap(0, 0, currMedia, 200, 200, textColor);
    display.display(true); // full refresh
                           
    mediaIndex = (mediaIndex + 1) % mediaCount;

    // only show initially so that we can switch between faces
    if (!enableInteractive) { break; }
  }

  // After exiting game loop, show one navigation frame
  drawFrame();
}


