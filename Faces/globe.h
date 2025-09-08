
void WatchyFaceX::drawFaceGlobe(
  bool enableDarkMode,
  bool enableInteractive
) {
  uint16_t bgColor = enableDarkMode ? GxEPD_BLACK : GxEPD_WHITE; 
  uint16_t textColor = enableDarkMode ? GxEPD_WHITE : GxEPD_BLACK; 

  display.setFullWindow();
  display.fillScreen(bgColor);

  auto drawNavigationFrame = [&]() {
    display.drawBitmap(0, 0, globe01, 200, 200, textColor);
    display.display(true); // full refresh
  };

  if (!enableInteractive) {
    drawNavigationFrame();
    return;
  }

  long lastMs = 0;
  long updateIntervalMs = 100;

  while (1) {
    unsigned long now = millis();

    // ACITVE_LOW (0 or 1) taken from Watchy github
    if (digitalRead(BACK_BTN_PIN) == 0) { break; }
    if ((now - lastMs) <= updateIntervalMs) { continue; }

    // ACTION PER INTERVAL
    lastMs = now;
    display.fillScreen(bgColor);
    display.drawBitmap(0, 0, globe02, 200, 200, textColor);
    //display.drawBitmap(0, 0, globe03, 200, 200, textColor);
    display.display(true); // full refresh
                           
    // only show initially so that we can switch between faces
    if (!enableInteractive) { break; }
  }

  // After exiting game loop, show one navigation frame
  drawNavigationFrame();
}

