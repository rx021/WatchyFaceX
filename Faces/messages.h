

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
  //display.getTextBounds(message, 0, 0, &x1, &y1, &width, &height);
  uint8_t msg2x = PADDING_X;
  uint8_t msg2y = PADDING_Y;
  display.setCursor(msg2x, msg2y);
  display.println(message);

  display.setFont(&FreeSansBold12pt7b);
  message = "How can I play?";
  display.println(message);

  display.setFont(&FreeSans12pt7b);
  message = "What's blocking me?";
  display.println(message);

  // DRAW DATE from bottom-up: 
  display.setFont(&Technology18pt7b);

  uint8_t year = currentTime.Year + 1970;
  uint8_t month = monthShortStr(currentTime.Month);
  uint8_t day = currentTime.Day;
  uint8_t weekday = dayShortStr(currentTime.Wday);
  String dateString = "" + year + " " + month + " " + day + " " + weekday;

  uint8_t dateX = PADDING_X;
  uint8_t dateY = DISPLAY_HEIGHT - PADDING_Y;
  display.setCursor(dateX, dateY);
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

