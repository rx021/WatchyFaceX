#pragma once
#include <cstdint>

namespace face_utils {

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
