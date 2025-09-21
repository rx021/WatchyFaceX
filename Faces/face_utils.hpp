#pragma once
#include <cstdint>

namespace face_utils {


template<typename GFX>
inline void leftText(GFX &display, const String &s, int leftX, int bottomY){
  display.setCursor(leftX, bottomY);
  display.print(s);
}

template<typename GFX>
inline int centerText(
  GFX &display,
  const String &message,
  int centerX,
  int topY
){
  int16_t x1,y1; uint16_t width,height;
  display.getTextBounds(message, 0, 0, &x1, &y1, &width, &height);
  int bottomY = topY + height;

  display.setCursor(centerX - (width/2), bottomY);
  display.print(message);

  return bottomY;
}

template<typename GFX>
inline int drawFaceTitle(
  GFX &display,
  String faceTitle,
  int textColor
) {
  display.setFont(&FreeSansBold12pt7b);
  display.setTextColor(textColor);

  uint8_t PADDING_X = 1; // pixels
  uint8_t PADDING_Y = 1; // pixels

  int16_t x1,y1; uint16_t width,height;
  display.getTextBounds(faceTitle, 0, 0, &x1, &y1, &width, &height);
  int bottomY = PADDING_Y + height;
  leftText(display, faceTitle, PADDING_X, bottomY);

  return bottomY; // new topY
}

template<typename GFX>
inline int drawCenterTime(
  GFX &display,
  String timeString,
  int textColor
) {
  display.setFont(&DSEG7_Classic_Bold_25);
  display.setTextColor(textColor);

  int16_t  x1, y1;
  uint16_t w, h;
  display.getTextBounds(timeString, 0, 0, &x1, &y1, &w, &h);

  uint8_t timeX = (DISPLAY_WIDTH / 2) - (w/2);
  uint8_t timeY = (DISPLAY_HEIGHT / 2) + (h/2);
  display.setCursor(timeX, timeY);
  display.println(timeString);

  return timeY; // new topY
}

struct TiltScale {
  int deadZone; // no movement below this magnitude
  int saturation; // full speed at or above this magnitude
  int maxPixelsPerFrame; // max integer step per update
};

auto clampToRange = [](int value, int minValue, int maxValue) {
  if (value < minValue) return minValue;
  if (value > maxValue) return maxValue;
  return value;
};

[[nodiscard]] inline uint8_t decrementCoordinate(
  uint8_t currentCoordinate,
  uint8_t pixelChange,
  uint8_t lowerBound
) noexcept {
  // prevent calculation underflows
  int16_t newCoordinate = currentCoordinate - pixelChange;

  return newCoordinate < lowerBound
    ? lowerBound
    : newCoordinate;
}

[[nodiscard]] constexpr uint8_t incrementCoordinate(
    uint8_t currentCoordinate,
    uint8_t pixelChange,
    uint8_t upperBound
) noexcept {
  // new temp variable to prevent calculation underflows
  return upperBound <= (currentCoordinate + pixelChange)
    ? upperBound
    : (currentCoordinate + pixelChange);
}

} // namespace face_utils

int WatchyFaceX::getBatteryPercent() {
  uint8_t batteryPercent = 0;
  float VBAT = getBatteryVoltage();

  if (4.2 <= VBAT){
    batteryPercent = 100.0;
  }
  else if (3.3 <= VBAT) {
    batteryPercent = 100.0 * (VBAT - 3.3) / 0.9;
  }

  return batteryPercent;
}

void WatchyFaceX::drawThinBattery(
    int bgColor,
    int textColor,
    int leftX,
    int topY
) {
  // x,y - w,h - r
  // 16,16 - 34,12 - 4  // pixels
  uint8_t border = 2;
  uint8_t width = 34;
  uint8_t height = 12;
  uint8_t radius = 4;
  // OUTER
  display.fillRoundRect(leftX, topY, width, height, radius, textColor);

  //display.fillRoundRect(49,20,3,4,2,textColor);
  
  // INNER
  // 18,18
  int innerX = leftX+border;
  int innerY = topY+border;
  int innerWidth = width-(border*2); // 24-(2*2)
  int innerHeight = height-(border*2); // 12-(2*2)
  display.fillRoundRect(innerX, innerY, innerWidth, innerHeight, 3, bgColor);

  float batt = getBatteryPercent() / 100.0;
  if (batt > 0) {
    // 20,20
    int fillX = innerX+border;
    int fillY = innerY+border;
    int fillWidth = 26*batt;
    int fillHeight = innerHeight-(border*2);
    display.fillRoundRect(fillX, fillY, fillWidth, fillHeight, 2, textColor);
  }
}

