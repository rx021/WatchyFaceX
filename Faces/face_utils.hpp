#pragma once
#include <stdint>

namespace face_utils {

constexpr uint8_t decrementCoordinate(
  uint8_t currentCoordinate,
  uint8_t pixelChange,
  uint8_t lowerBound
) noexcept {
  // new temp variable to prevent calculation underflows
  int16_t newCoordinate = currentCoordinate - pixelChange;

  return (newCoordinate < lowerBound)
    ? lowerBound
    : newCoordinate;
}

constexpr uint8_t incrementCoordinate(
    uint8_t currentCoordinate,
    uint8_t pixelChange,
    uint8_t upperBound
) noexcept {
    // new temp variable to prevent calculation underflows
    int16_t newCoordinate = currentCoordinate + pixelChange;

    return (upperBound <= newCoordinate)
      ? upperBound
      : newCoordinate;
}

} // namespace face_utils
