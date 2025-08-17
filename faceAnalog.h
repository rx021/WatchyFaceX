
void WatchyFaceX::drawFaceAnalog(bool enableDarkMode) {
  uint16_t bgColor = enableDarkMode ? GxEPD_BLACK : GxEPD_WHITE; 
  uint16_t textColor = enableDarkMode ? GxEPD_WHITE : GxEPD_BLACK; 

  display.fillScreen(bgColor);
  display.setTextColor(textColor);
  display.setFont(&DSEG7_Classic_Bold_25);


}

// helper function for hands drawing
void WatchyFaceX::drawHand(
    uint8_t _radius_,
    float _angle_,
    bool _light_
) {
  float x = _radius_*cos(_angle_);
  float y = _radius_*sin(_angle_);
  display.drawLine(99, 99, 99+x, 99+y, _light_ ? GxEPD_BLACK : GxEPD_WHITE);
  display.drawLine(99, 100, 99+x, 100+y, _light_ ? GxEPD_BLACK : GxEPD_WHITE);
  display.drawLine(99, 101, 99+x, 101+y, _light_ ? GxEPD_BLACK : GxEPD_WHITE);
  display.drawLine(100, 99, 100+x, 99+y, _light_ ? GxEPD_BLACK : GxEPD_WHITE);
  display.drawLine(100, 100, 100+x, 100+y, _light_ ? GxEPD_BLACK : GxEPD_WHITE);
  display.drawLine(100, 101, 100+x, 101+y, _light_ ? GxEPD_BLACK : GxEPD_WHITE);
  display.drawLine(101, 99, 101+x, 99+y, _light_ ? GxEPD_BLACK : GxEPD_WHITE);
  display.drawLine(101, 100, 101+x, 100+y, _light_ ? GxEPD_BLACK : GxEPD_WHITE);
  display.drawLine(101, 101, 101+x, 101+y, _light_ ? GxEPD_BLACK : GxEPD_WHITE);
}

