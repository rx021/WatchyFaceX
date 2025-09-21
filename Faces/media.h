
RTC_DATA_ATTR int mediaIndex = 0;
RTC_DATA_ATTR int mediaCount = 4; // match Images/media.h array size

void WatchyFaceX::drawFaceMedia(
  bool enableDarkMode,
  bool enableInteractive
) {
  // need inverse so that images look better
  uint16_t bgColor = !enableDarkMode ? GxEPD_BLACK : GxEPD_WHITE; 
  uint16_t textColor = !enableDarkMode ? GxEPD_WHITE : GxEPD_BLACK; 

  display.setFullWindow();

  // Ensure buttons are readable (active-low)
  pinMode(UP_BTN_PIN, INPUT);
  pinMode(DOWN_BTN_PIN, INPUT);
  pinMode(BACK_BTN_PIN, INPUT);

  auto drawBitmapAtIndex = [&]() {
    display.fillScreen(bgColor);
    const unsigned char *curr = medias[mediaIndex];
    display.drawBitmap(0, 0, curr, 200, 200, textColor);
    display.display(true); // full refresh
  };

  if (!enableInteractive) {
    drawBitmapAtIndex();
    drawFaceTitle(display, "IMAGES", textColor);
    return;
  }

  // Initial render = current media
  drawBitmapAtIndex();

  while (1) {
    // ACITVE_LOW (0 or 1) taken from Watchy github
    if (digitalRead(BACK_BTN_PIN) == LOW) { break; }

    if (digitalRead(UP_BTN_PIN) == LOW) {
      // previous image (wrap)
      mediaIndex = (mediaIndex - 1 + mediaCount) % mediaCount;
      drawBitmapAtIndex();
      while (digitalRead(UP_BTN_PIN) == LOW) { delay(10); } // release
      delay(120); // debounce
    }

    if (digitalRead(DOWN_BTN_PIN) == LOW) {
      // next image (wrap)
      mediaIndex = (mediaIndex + 1) % mediaCount;
      drawBitmapAtIndex();
      while (digitalRead(DOWN_BTN_PIN) == LOW) { delay(10); } // release
      delay(120); // debounce
    }

    // small idle delay to reduce busy-wait power
    delay(5);
  }

  // After exiting game loop, show one navigation frame
  drawBitmapAtIndex();
}


