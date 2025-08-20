

void WatchyFaceX::drawFaceMessages(bool enableDarkMode) {
  uint8_t PADDING_X = 5; // pixels
  uint8_t PADDING_Y = 5; // pixels
  uint16_t bgColor = enableDarkMode ? GxEPD_BLACK : GxEPD_WHITE; 
  uint16_t textColor = enableDarkMode ? GxEPD_WHITE : GxEPD_BLACK; 
  display.fillScreen(bgColor);

  // MESSAGES
  display.setTextColor(textColor);

  int16_t  x1, y1;
  uint16_t width, height;
  String message = "";

  // QUESTIONS:
  display.setFont(&FreeSans12pt7b);
  message = "Kinesthete? Explorer? Creator?";
  display.getTextBounds(message, 0, 0, &x1, &y1, &width, &height);
  //uint8_t msg2x = DISPLAY_WIDTH - PADDING_X;
  //uint8_t msg2y = msg1y + PADDING_Y + height;
  //display.setCursor(msg2x, msg2y);
  display.print(message);
  message = "How can I play?";
  display.print(message);
  message = "What's blocking me?";
  display.print(message);

  // DATE from bottom-up: 

  uint8_t dateSpacing = 10;

  // DRAW WEEKDAY
  display.setFont(&DIN_1451_Engschrift_Regular12pt7b);
  String dateString = dayStr(currentTime.Wday);

  display.getTextBounds(dateString, 0, 0, &x1, &y1, &width, &height);
  uint8_t weekdayX = PADDING_X;
  uint8_t weekdayY = DISPLAY_HEIGHT - PADDING_Y;
  uint8_t weekdayWidth = width;
  uint8_t weekdayHeight = height;
  display.setCursor(weekdayX, weekdayY);
  display.print(dateString);

  // DRAW DATE
  display.setFont(&Technology18pt7b);
  dateString = monthShortStr(currentTime.Month);
  dateString += " ";
  dateString += currentTime.Day;

  display.getTextBounds(dateString, 0, 0, &x1, &y1, &width, &height);
  uint8_t dateX = PADDING_X;
  uint8_t dateY = weekdayY - weekdayHeight - dateSpacing;
  uint8_t dateWidth = width;
  uint8_t dateHeight = height;
  display.setCursor(dateX, dateY);
  display.print(dateString);

  // DRAW YEAR
  display.setFont(&DIN_1451_Engschrift_Regular12pt7b);
  dateString = currentTime.Year + 1970;

  display.getTextBounds(dateString, 0, 0, &x1, &y1, &w, &h);
  uint8_t yearX = PADDING_X;
  uint8_t yearY = dateY - dateHeight - dateSpacing;
  uint8_t yearWidth = width;
  uint8_t yearHeight = height;
  display.setCursor(yearX, yearY);
  display.print(dateString);
  
  // TEST 01 - [' ]
  //display.setFont(&FreeSans9pt7b);
  //message = "FreeSans9pt7b";
  //display.getTextBounds(message, 0, 0, &x1, &y1, &width, &height);
  //uint8_t msg1x = PADDING_X;
  //uint8_t msg1y = PADDING_Y + height;
  //display.setCursor(msg1x, msg1y);
  //display.print(message);
                          
  // TEST 02 - [ ']
  //display.setFont(&FreeSans12pt7b);
  //message = "FreeSans12pt7b";
  //display.getTextBounds(message, 0, 0, &x1, &y1, &width, &height);
  //uint8_t msg2x = DISPLAY_WIDTH - PADDING_X;
  //uint8_t msg2y = msg1y + PADDING_Y + height;
  //display.setCursor(msg2x, msg2y);
  //display.print(message);

  // TEST 03 - [. ]
  //display.setFont(&FreeSans18pt7b);
  //message = "FreeSans18pt7b";
  //display.getTextBounds(message, 0, 0, &x1, &y1, &width, &height);
  //uint8_t msg3x = PADDING_X;
  //uint8_t msg3y = DISPLAY_HEIGHT - PADDING_Y;
  //uint8_t msg3height = height;
  //display.setCursor(msg3x, msg3y);
  //display.print(message);

  // TEST 04 - [ .]
  //display.setFont(&FreeSans24pt7b);
  //message = "FreeSans24pt7b";
  //display.getTextBounds(message, 0, 0, &x1, &y1, &width, &height);
  //uint8_t msg4x = DISPLAY_WIDTH - PADDING_X;
  //uint8_t msg4y = msg3y - msg3height - PADDING_Y;
  //display.setCursor(msg4x, msg4y);
  //display.print(message);
}

