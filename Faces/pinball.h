#include "face_utils.hpp" 
using namespace face_utils;

void WatchyFaceX::drawFacePinball(bool enableDarkMode) {
  uint16_t bgColor = enableDarkMode ? GxEPD_BLACK : GxEPD_WHITE; 
  uint16_t textColor = enableDarkMode ? GxEPD_WHITE : GxEPD_BLACK; 

  display.setFullWindow();
  display.fillScreen(bgColor);
  display.setFont(&FreeSans9pt7b);
  display.setTextColor(textColor);

  Accel accelerationData;

  long previousMillis = 0;
  long intervalMillis = 100;

  uint8_t centerX = DISPLAY_WIDTH / 2;
  uint8_t centerY = DISPLAY_HEIGHT / 2;

  // NOTE: circle center is X,Y
  uint8_t ballX = centerX;
  uint8_t ballY = centerY;
  uint8_t ballRadius = 4;
  uint8_t ballIncrements = 16;

  uint8_t minBallX = ballRadius;
  uint8_t maxBallX = DISPLAY_WIDTH - ballRadius;
  uint8_t minBallY = ballRadius;
  uint8_t maxBallY = DISPLAY_HEIGHT - ballRadius;

  while (1) {
    unsigned long currentMillis = millis();

    if (digitalRead(BACK_BTN_PIN) == 0) {
      // ACITVE_LOW (0 or 1) taken from Watchy github
      break;
    }

    if ((currentMillis - previousMillis) <= intervalMillis) {
      continue;
    }

    // ACTION PER INTERVAL
    
    previousMillis = currentMillis;

    // Get acceleration data
    bool accelerationReadOk = sensor.getAccel(accelerationData);
    uint8_t direction = sensor.getDirection();

    display.fillScreen(bgColor);
    display.setCursor(3, 10);

    if (!accelerationReadOk) {
      display.println("Acceleration read failed");
      display.display(true); // full refresh
      continue;
    }

    switch (direction) {
    case DIRECTION_DISP_DOWN:
      display.println("FACE DOWN");
      break;
    case DIRECTION_DISP_UP:
      display.println("FACE UP");
      break;
    case DIRECTION_RIGHT_EDGE:
      display.println("RIGHT EDGE");
      ballX = decrementCoordinate(
          ballX,
          ballIncrements,
          minBallX
      );
      break;
    case DIRECTION_LEFT_EDGE:
      display.println("LEFT EDGE");
      ballX = incrementCoordinate(
          ballX,
          ballIncrements,
          maxBallX
      );
      break;
    case DIRECTION_BOTTOM_EDGE:
      display.println("BOTTOM EDGE");
      ballY = decrementCoordinate(
          ballY,
          ballIncrements,
          minBallY
      );
      break;
    case DIRECTION_TOP_EDGE:
      display.println("TOP EDGE");
      ballY = incrementCoordinate(
          ballY,
          ballIncrements,
          maxBallY
      );
      break;
    default:
      display.println("ERROR!!!");
      break;
    }
    display.print("X:"); display.println(accelerationData.x);
    display.print("Y:"); display.println(accelerationData.y);
    display.print("Z:"); display.println(accelerationData.z);

    display.fillCircle(
      ballX,
      ballY,
      ballRadius,
      textColor
    );

    display.display(true); // full refresh
  }

}

