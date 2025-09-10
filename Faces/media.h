
RTC_DATA_ATTR int mediaIndex = 0;
RTC_DATA_ATTR int mediaCount = 4; // match Images/media.h array size

void WatchyFaceX::drawFaceMedia(
  bool enableDarkMode,
  bool enableInteractive
) {
  uint16_t bgColor = enableDarkMode ? GxEPD_BLACK : GxEPD_WHITE; 
  uint16_t textColor = enableDarkMode ? GxEPD_WHITE : GxEPD_BLACK; 

  display.setFullWindow();

  auto drawBitmapAtIndex = [&]() {
    const unsigned char *curr = medias[mediaIndex];
    display.fillScreen(bgColor);
    display.drawBitmap(0, 0, cabin, 200, 200, textColor);
    display.display(true); // full refresh
  };

  auto drawNavFrame = [&]() {
    display.fillScreen(bgColor);
    display.drawBitmap(0, 0, cabin, 200, 200, textColor);
    display.display(true); // full refresh
  };

  if (!enableInteractive) {
    drawNavFrame();
    return;
  }

  // Initial render = current media
  drawBitmapAtIndex();

  while (1) {
    // ACITVE_LOW (0 or 1) taken from Watchy github
    if (digitalRead(BACK_BTN_PIN) == 0) { break; }

    if (digitalRead(UP_BTN_PIN) == 0) {
      // previous image (wrap)
      mediaIndex = (mediaIndex - 1 + mediaCount) % mediaCount;
      drawBitmapAtIndex();
      // wait for release + debounce
      while (digitalRead(UP_BTN_PIN) == 0) { delay(10); }
      delay(120);
    }

    if (digitalRead(DOWN_BTN_PIN) == 0) {
      // next image (wrap)
      mediaIndex = (mediaIndex + 1) % mediaCount;
      drawBitmapAtIndex();
      // wait for release + debounce
      while (digitalRead(DOWN_BTN_PIN) == 0) { delay(10); }
      delay(120);
    }

    // small idle delay to reduce busy-wait power
    delay(5);
  }

  // After exiting game loop, show one navigation frame
  drawNavFrame();
}


