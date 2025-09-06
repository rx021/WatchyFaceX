#include "face_utils.hpp" 
using namespace face_utils;

void WatchyFaceX::drawFacePinball(
  bool enableDarkMode,
  bool enableInteractive
) {
  uint16_t bgColor = enableDarkMode ? GxEPD_BLACK : GxEPD_WHITE; 
  uint16_t textColor = enableDarkMode ? GxEPD_WHITE : GxEPD_BLACK; 

  display.setFullWindow();
  display.fillScreen(bgColor);
  display.setFont(&FreeSansBold12pt7b);
  display.setTextColor(textColor);

  // NOTE: circle center is X,Y
  uint8_t ballX = DISPLAY_WIDTH / 2;
  uint8_t ballY = DISPLAY_HEIGHT / 2;
  uint8_t ballRadius = 4;
  uint8_t ballIncrements = 16;

  uint8_t minBallX = ballRadius;
  uint8_t maxBallX = DISPLAY_WIDTH - ballRadius;
  uint8_t minBallY = ballRadius;
  uint8_t maxBallY = DISPLAY_HEIGHT - ballRadius;

  long lastMs = 0;
  long updateIntervalMs = 100;

  // NAVIGATION MODE: draw once; return

  auto drawNavigationFrame = [&]() {
    uint8_t PADDING_X = 1; // pixels
    uint8_t PADDING_Y = 1; // pixels
    int16_t  x1, y1;
    uint16_t w, h;

    String message = "PINBALL";
    display.getTextBounds(message, 0, 0, &x1, &y1, &w, &h);
    uint8_t mX = PADDING_X;
    int8_t mY = PADDING_Y + (-1 *  y1);

    display.fillScreen(bgColor);
    display.setCursor(mX, mY);
    display.println(message);
    display.fillCircle(ballX, ballY, ballRadius, textColor);
    display.display(true); // full refresh
  };

  if (!enableInteractive) {
    drawNavigationFrame();
    return;
  }

  // GAME MODE: loop
  
  Accel accelerationData;

  while (1) {
    unsigned long now = millis();

    if (digitalRead(BACK_BTN_PIN) == 0) {
      // ACITVE_LOW (0 or 1) taken from Watchy github
      break;
    }

    if ((now - lastMs) <= updateIntervalMs) {
      continue;
    }

    // ACTION PER INTERVAL
    
    lastMs = now;

    // Get acceleration data
    bool accelerationReadOk = sensor.getAccel(accelerationData);

    display.fillScreen(bgColor);
    display.setCursor(3, 10);

    if (!accelerationReadOk) {
      display.println("Acceleration read failed");
      display.display(true); // full refresh
      continue;
    }

    uint8_t direction = sensor.getDirection();
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

    display.fillCircle(ballX, ballY, ballRadius, textColor);
    display.display(true); // full refresh

    if (!enableInteractive) {
      // only show initially so that we can switch between faces
      break;
    }
  }

  // After exiting game loop, show one navigation frame
  drawNavigationFrame();
}

