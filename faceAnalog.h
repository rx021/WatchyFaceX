
void WatchyFaceX::drawFaceAnalog(bool enableDarkMode) {
  uint16_t bgColor = enableDarkMode ? GxEPD_BLACK : GxEPD_WHITE; 
  uint16_t textColor = enableDarkMode ? GxEPD_WHITE : GxEPD_BLACK; 

  display.fillScreen(bgColor);
  display.setTextColor(textColor);
  display.setFont(&DSEG7_Classic_Bold_25);

  float pi = 3.1415926535897932384626433832795;
  float circumference = 2 * pi;

  // CLOCK TICK SCALE
  uint8_t tickOuterRadius = 98;

  // DRAW MINUTE SCALE
  uint8_t minuteCount = 60;
  float angle_minuteScale = circumference / minuteCount;
  for (uint8_t minuteIndex = 0; minuteIndex < minuteCount; minuteIndex++) {
    display.drawLine(
      100,
      100,
      100 + tickOuterRadius * cos(angle_minuteScale * minuteIndex),
      100 + tickOuterRadius * sin(angle_minuteScale * minuteIndex),
      textColor
    );
  }
  display.fillCircle(100, 100, 93, bgColor);

  // DRAW HOUR SCALE
  uint8_t hourCount = 12;
  float angle_hourScale = circumference / hourCount;
  for (uint8_t hourIndex = 0; hourIndex < hourCount; hourIndex++) {
    drawHand(tickOuterRadius, (angle_hourScale * hourIndex), textColor);
  }
  display.fillCircle(100, 100, 88, bgColor);


  // DRAW QUARTER HOUR SCALE
  uint8_t tickCount = 4;
  float angle_tickScale = circumference / tickCount;
  for (uint8_t tickIndex = 0; tickIndex < tickCount; tickIndex++) {
    drawHand(tickOuterRadius, (angle_tickScale * tickIndex), textColor);
  }
  display.fillCircle(100, 100, 88, bgColor);

  // CLOCK HANDS

  uint8_t myHour = currentTime.Hour > 12 ? currentTime.Hour - 12 : currentTime.Hour;
  uint8_t myMinute = currentTime.Minute;

  // DRAW HOUR HAND
  //uint8_t hourHandRadius = 45;
  //float angle_hourHand = angle_hourScale * (myHour-3) + 2*pi/720 * myMinute;
  //drawHand(hourHandRadius, angle_hourHand, textColor);

  // DRAW MINUTE HAND
  float angle_minuteHand = angle_minuteScale * (myMinute-15);
  drawHand(tickOuterRadius, angle_minuteHand, textColor);

  // DRAW CENTER POINT
  display.fillCircle(100, 100, 45, bgColor);



  // positioning of hour display for DSEG7_Classic_Regular_39 font
  uint8_t hourYPosn = 120;
  if (currentTime.Hour > 9 && currentTime.Hour < 20) {
    display.setCursor(58, hourYPosn);
  } else {
    display.setCursor(68, hourYPosn);
  }

  // display hour (with a leading zero, if necessary)
  if(currentTime.Hour < 10){
      display.print("0");
  }
  display.print(currentTime.Hour);

}



// helper function for hands drawing
void WatchyFaceX::drawHand(
    uint8_t handRadius,
    float angle,
    uint16_t handColor
) {
  float x = handRadius * cos(angle);
  float y = handRadius * sin(angle);
  //     99 100 101
  //  99  .   .   .        
  // 100  .   .   .        
  // 101  .   .   .        
  // draws from center spots to tickOuterRadius
  display.drawLine(99, 99, 99+x, 99+y, handColor);
  display.drawLine(99, 100, 99+x, 100+y, handColor);
  display.drawLine(99, 101, 99+x, 101+y, handColor);

  display.drawLine(100, 99, 100+x, 99+y, handColor);
  display.drawLine(100, 100, 100+x, 100+y, handColor);
  display.drawLine(100, 101, 100+x, 101+y, handColor);

  display.drawLine(101, 99, 101+x, 99+y, handColor);
  display.drawLine(101, 100, 101+x, 100+y, handColor);
  display.drawLine(101, 101, 101+x, 101+y, handColor);
}

