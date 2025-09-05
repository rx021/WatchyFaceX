#include "face_utils.hpp" 
using namespace face_utils;

inline int activeTiltMagnitude(
  int16_t rawAcceleration,
  const TiltScale& scale
) {
  int magnitude = std::abs(rawAcceleration);
  if (magnitude <= scale.deadZone) {return 0;}

  const int activeRange = scale.saturation - scale.deadZone;
  if (activeRange <= 0) {return 0;}

  int active = magnitude - scale.deadZone;
  // cap at saturation
  if (activeRange < active) {active = activeRange;}

  return active; // between 0 and activeRange
}

inline int normalizedStepFromActiveMagnitude(
  int activeMagnitude,
  const TiltScale& scale
) {
  if (activeMagnitude <= 0) {return 0;}

  const int activeRange = scale.saturation - scale.deadZone;
  if (activeRange <= 0) {return 0;}

  int scaled = activeMagnitude * scale.maxPixelsPerFrame;
  int rounded = (scaled + activeRange/2) / activeRange;
  if (rounded < 1) {rounded = 1;}
  if (scale.maxPixelsPerFrame < rounded) {rounded = scale.maxPixelsPerFrame;}

  return rounded;
}

inline int tiltToSignedStep(
  int16_t rawAcceleration,
  const TiltScale& scale
) {
  int sign = (rawAcceleration < 0) ? -1 : 1;
  int active = activeTiltMagnitude(rawAcceleration, scale);
  int step = normalizedStepFromActiveMagnitude(active, scale);

  return sign * step;
}

void WatchyFaceX::drawFacePinballX(
  bool enableDarkMode,
  bool enableInteractive
) {
  uint16_t bgColor = enableDarkMode ? GxEPD_BLACK : GxEPD_WHITE; 
  uint16_t textColor = enableDarkMode ? GxEPD_WHITE : GxEPD_BLACK; 

  display.setFullWindow();
  display.fillScreen(bgColor);
  display.setFont(&FreeSans9pt7b);
  display.setTextColor(textColor);

  // NOTE: circle center is X,Y
  uint8_t ballX = DISPLAY_WIDTH / 2;
  uint8_t ballY = DISPLAY_HEIGHT / 2;
  const uint8_t ballRadius = 4;

  const uint8_t minBallX = ballRadius;
  const uint8_t maxBallX = DISPLAY_WIDTH - ballRadius;
  const uint8_t minBallY = ballRadius;
  const uint8_t maxBallY = DISPLAY_HEIGHT - ballRadius;

  unsigned long lastMs = 0;
  const unsigned long updateIntervalMs = 100;

  // NAVIGATION MODE: draw once; return

  auto drawNavigationFrame = [&]() {
    display.fillScreen(bgColor);
    display.setCursor(3, 14);
    display.println("PinballX");
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
      ::enableInteractive = false;
      break;
    }

    if ((now - lastMs) <= updateIntervalMs) { continue; }

    // ACTION PER INTERVAL
    
    lastMs = now;

    // Get acceleration data
    bool accelerationReadOk = sensor.getAccel(accelerationData);

    display.fillScreen(bgColor);
    display.setCursor(3, 14);

    if (!accelerationReadOk) {
      display.println("Acceleration read failed");
      display.display(true); // full refresh
      continue;
    }

    display.print("X:"); display.println(accelerationData.x);
    display.print("Y:"); display.println(accelerationData.y);
    display.print("Z:"); display.println(accelerationData.z);

    const TiltScale ballTilt = {
      .deadZone = 140,
      .saturation = 900,
      .maxPixelsPerFrame = 4
    };

    // NOTE: X,Y appear to be switched for accelerometer
    int horizontalStep = tiltToSignedStep(
      // Y: +ve right edge up & -ve left edge up
      -accelerationData.y,
      ballTilt
    );
    int verticalStep = tiltToSignedStep(
      // X: +ve top edge up & -ve bottom edge up
      accelerationData.x,
      ballTilt
    );

    // make sure ball is in bounds
    ballX = clampToRange(ballX + horizontalStep, minBallX, maxBallX);
    ballY = clampToRange(ballY + verticalStep, minBallY, maxBallY);

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


