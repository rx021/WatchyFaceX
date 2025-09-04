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

  return sign & step;
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

  Accel accelerationData;

  long lastUpdateTimeMs = 0;
  long updateIntervalMs = 100;

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
    unsigned long currentTimeMs = millis();

    if (digitalRead(BACK_BTN_PIN) == 0) {
      // ACITVE_LOW (0 or 1) taken from Watchy github
      break;
    }

    if ((currentTimeMs - lastUpdateTimeMs) <= updateIntervalMs) {
      continue;
    }

    // ACTION PER INTERVAL
    
    lastUpdateTimeMs = currentTimeMs;

    // Get acceleration data
    bool accelerationReadOk = sensor.getAccel(accelerationData);

    display.fillScreen(bgColor);
    display.setCursor(3, 10);

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

    int horizontalStep = tiltToSignedStep(
      -accelerationData.x,
      ballTilt
    );
    int verticalStep = tiltToSignedStep(
      accelerationData.y,
      ballTilt
    );

    // make sure ball is in bounds
    ballX = clampToRange(
      ballX + horizontalStep,
      minBallX,
      maxBallX
    );
    ballY = clampToRange(
      ballY + verticalStep,
      minBallY,
      maxBallY
    );

    display.fillCircle(
      ballX,
      ballY,
      ballRadius,
      textColor
    );

    display.display(true); // full refresh

    if (!enableInteractive) {
      // only show initially so that we can switch between faces
      break;
    }
  }

}


