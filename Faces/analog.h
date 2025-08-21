
void WatchyFaceX::drawFaceAnalog(bool enableDarkMode) {
  uint16_t bgColor = enableDarkMode ? GxEPD_BLACK : GxEPD_WHITE; 
  uint16_t textColor = enableDarkMode ? GxEPD_WHITE : GxEPD_BLACK; 

  display.fillScreen(bgColor);
  display.setTextColor(textColor);
  display.setFont(&Technology18pt7b);

  float pi = 3.1415926535897932384626433832795;
  float circumference = 2 * pi;

  uint8_t centerX = DISPLAY_WIDTH / 2;
  uint8_t centerY = DISPLAY_HEIGHT / 2;

  // CLOCK TICK SCALE:
  uint8_t tickOuterRadius = centerX - 2;

  // DRAW MINUTE SCALE
  uint8_t minuteCount = 60;
  float angle_minuteScale = circumference / minuteCount;
  float minuteAngle;
  for (uint8_t minuteIndex = 0; minuteIndex < minuteCount; minuteIndex++) {
    minuteAngle = angle_minuteScale * minuteIndex;
    display.drawLine(
      centerX,
      centerY,
      centerX + tickOuterRadius * cos(minuteAngle),
      centerY + tickOuterRadius * sin(minuteAngle),
      textColor
    );
  }
  uint8_t minuteCircleOverlayRadius = 93;
  display.fillCircle(centerX, centerY, minuteCircleOverlayRadius, bgColor);

  // DRAW HOUR SCALE
  uint8_t hourCount = 12;
  float angle_hourScale = circumference / hourCount;
  for (uint8_t hourIndex = 0; hourIndex < hourCount; hourIndex++) {
    drawHandX(
      tickOuterRadius,
      (angle_hourScale * hourIndex),
      2, // lineThickness must be even number
      textColor
    );
  }
  uint8_t hourCircleOverlayRadius = minuteCircleOverlayRadius - 5;
  display.fillCircle(centerX, centerY, hourCircleOverlayRadius, bgColor);


  // DRAW QUARTER HOUR SCALE
  uint8_t tickCount = 4;
  float angle_tickScale = circumference / tickCount;
  for (uint8_t tickIndex = 0; tickIndex < tickCount; tickIndex++) {
    drawHandX(
      tickOuterRadius,
      (angle_tickScale * tickIndex),
      2, // lineThickness must be even number
      textColor
    );
  }
  uint8_t quarterHourCircleOverlayRadius = hourCircleOverlayRadius - 15;
  display.fillCircle(centerX, centerY, quarterHourCircleOverlayRadius, bgColor);

  // CLOCK HANDS:

  bool isAfternoon = currentTime.Hour > 12;
  uint8_t myHour = isAfternoon ? currentTime.Hour - 12 : currentTime.Hour;
  uint8_t myMinute = currentTime.Minute;

  // DRAW MINUTE HAND
  uint8_t minuteCountQuarter = minuteCount / 4;
  float angle_minuteHand = angle_minuteScale * (myMinute - minuteCountQuarter);
  // NOTE: if myMinute was 0 then angle_minuteHand would be 0 radians
  // - this would have myMinute 0 pointing to the right
  // - but to point myMinute 0 to the top, 
  //   we need to subtract by 15 minutes which is 90 degrees

  drawHandX(
    tickOuterRadius,
    angle_minuteHand,
    4, // lineThickness must be even number
    textColor
  );

  // DRAW HOUR HAND
  uint8_t hourHandOverlayRadius = 45;

  // will be half the length of the minute hand
  uint8_t hourHandLength = (tickOuterRadius - hourHandOverlayRadius) / 2;
  uint8_t hourHandOuterRadius = hourHandOverlayRadius + hourHandLength;

  uint8_t myHour12 = myHour % 12;
  float hourFraction = myMinute / minuteCount;
  float hourValue = myHour12 + hourFraction;

  uint8_t hourCountQuarter = hourCount / 4;
  float angle_hourHand = angle_hourScale * (hourValue - hourCountQuarter);

  drawHandX(
    hourHandOuterRadius,
    angle_hourHand,
    6, // lineThickness must be even number
    textColor
  );
  display.fillCircle(centerX, centerY, hourHandOverlayRadius, bgColor);


  // CENTER DATETIME DISPLAY:
  int16_t  x1, y1;
  uint16_t w, h;

  String dateString = "";
  uint8_t dateSpacing = 5;

  // DRAW DATE
  char* currMonth = monthShortStr(currentTime.Month);
  dateString += currMonth;
  dateString += " ";
  uint8_t currDay = currentTime.Day;
  if (currDay < 10) {dateString += "0";}
  dateString += currDay;

  display.getTextBounds(dateString, 0, 0, &x1, &y1, &w, &h);
  uint8_t dateHalfWidth = w / 2;
  uint8_t dateHalfHeight = h / 2;
  uint8_t dateX = centerX - dateHalfWidth; // to center
  uint8_t dateY = centerY + dateHalfHeight; // to center
  display.setCursor(dateX, dateY);
  display.print(dateString);

  display.setFont(&Seven_Segment10pt7b);

  // DRAW YEAR
  dateString = currentTime.Year + 1970;
  display.getTextBounds(dateString, 0, 0, &x1, &y1, &w, &h);
  uint8_t yearHalfWidth = w / 2;
  uint8_t yearX = centerX - yearHalfWidth; // to center
  uint8_t yearY = centerY - dateHalfHeight - dateSpacing; // to center above date
  display.setCursor(yearX, yearY);
  display.print(dateString);

  // DRAW WEEKDAY
  dateString = dayStr(currentTime.Wday);
  display.getTextBounds(dateString, 0, 0, &x1, &y1, &w, &h);
  uint8_t weekdayHalfWidth = w / 2;
  uint8_t weekdayX = centerX - weekdayHalfWidth; // to center
  uint8_t weekdayY = centerY + dateHalfHeight + dateSpacing + h; // to center below date
  display.setCursor(weekdayX, weekdayY);
  display.print(dateString);
}

// HELPER FUNCTION FOR HANDS DRAWING
//     99 100 101
//  99  .   .   .        
// 100  .   .   .        
// 101  .   .   .        
// draws from center spots to tickOuterRadius
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

  // SOH CAH TOA
  // O = opposite (y); A = adjacent (x); H = hypotenuse (radius)
  // sin = O/H; cos = A/H
  float handX = handRadius * cos(angle); // A = H * cos
  float handY = handRadius * sin(angle); // O = H * sin

  for (uint8_t lineX1 = startX; lineX1 < endX; lineX1++) {
    for (uint8_t lineY1 = startY; lineY1 < endY; lineY1++) {
      display.drawLine(
        lineX1, lineY1,
        (lineX1 + handX), (lineY1 + handY),
        handColor
      );
    }
  }
}


