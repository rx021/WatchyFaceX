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
}
