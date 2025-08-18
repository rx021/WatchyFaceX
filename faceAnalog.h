
void WatchyFaceX::drawFaceAnalog(bool enableDarkMode) {
  uint16_t bgColor = enableDarkMode ? GxEPD_BLACK : GxEPD_WHITE; 
  uint16_t textColor = enableDarkMode ? GxEPD_WHITE : GxEPD_BLACK; 

  display.fillScreen(bgColor);
  display.setTextColor(textColor);
  display.setFont(&DSEG7_Classic_Bold_25);

  float pi = 3.1415926535897932384626433832795;
  float circumference = 2 * pi;

  uint8_t centerX = 100;
  uint8_t centerY = 100;

  // CLOCK TICK SCALE
  uint8_t tickOuterRadius = 98;

  // DRAW MINUTE SCALE
  uint8_t minuteCount = 60;
  float angle_minuteScale = circumference / minuteCount;
  for (uint8_t minuteIndex = 0; minuteIndex < minuteCount; minuteIndex++) {
    display.drawLine(
      centerX,
      centerY,
      centerX + tickOuterRadius * cos(angle_minuteScale * minuteIndex),
      centerY + tickOuterRadius * sin(angle_minuteScale * minuteIndex),
      textColor
    );
  }
  uint8_t minuteCircleOverlayRadius = 93;
  display.fillCircle(centerX, centerY, minuteCircleOverlayRadius, bgColor);

  // DRAW HOUR SCALE
  uint8_t hourCount = 12;
  float angle_hourScale = circumference / hourCount;
  for (uint8_t hourIndex = 0; hourIndex < hourCount; hourIndex++) {
    drawHand(tickOuterRadius, (angle_hourScale * hourIndex), textColor);
  }
  uint8_t hourCircleOverlayRadius = minuteCircleOverlayRadius - 5;
  display.fillCircle(centerX, centerY, hourCircleOverlayRadius, bgColor);


  // DRAW QUARTER HOUR SCALE
  uint8_t tickCount = 4;
  float angle_tickScale = circumference / tickCount;
  for (uint8_t tickIndex = 0; tickIndex < tickCount; tickIndex++) {
    drawHand(tickOuterRadius, (angle_tickScale * tickIndex), textColor);
  }
  uint8_t quarterHourCircleOverlayRadius = hourCircleOverlayRadius - 15;
  display.fillCircle(centerX, centerY, quarterHourCircleOverlayRadius, bgColor);

  // CLOCK HANDS

  bool isAfternoon = currentTime.Hour > 12;
  uint8_t myHour = isAfternoon ? currentTime.Hour - 12 : currentTime.Hour;
  uint8_t myMinute = currentTime.Minute;

  // DRAW MINUTE HAND
  float angle_minuteHand = angle_minuteScale * (myMinute - 15);
  drawHand(tickOuterRadius, angle_minuteHand, textColor);
  uint8_t minuteHandOverlayRadius = 45;
  display.fillCircle(centerX, centerY, minuteHandOverlayRadius, bgColor);

  // DRAW HOUR HAND
  uint8_t hourHandOuterRadius = 45;
  //float angle_hourHand = angle_hourScale * (myHour-3) + 2*pi/720 * myMinute;
  uint8_t lineThickness = 2; // must be even
  drawHandX(
    hourHandOuterRadius,
    angle_hourHand,
    lineThickness,
    textColor
  );



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

void WatchyFaceX::drawHandX(
    uint8_t handRadius,
    float angle,
    uint8_t lineThickness,
    uint16_t handColor
) {
  uint8_t halfThickness = lineThickness / 2 ;

  uint8_t centerX = 100;
  uint8_t startX = centerX - halfThickness;
  uint8_t endX = centerX + halfThickness;

  uint8_t centerY = 100;
  uint8_t startY = centerY - halfThickness;
  uint8_t endY = centerY + halfThickness;

  float x = handRadius * cos(angle);
  float y = handRadius * sin(angle);

  for (uint8_t lineX1 = startX; lineX1 < endX; lineX1++) {
    for (uint8_t lineY1 = startY; lineY1 < endY; lineY1++) {
      display.drawLine(
        lineX1, lineY1,
        (lineX1 + x), (lineY1 + y),
        handColor
      );
    }
  }
}

