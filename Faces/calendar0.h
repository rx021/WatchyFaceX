
// NOTE: fillRect() - top left is X=0, Y=0
// NOTE: setCursor() - bottom left is needed for TEXT to print properly

const uint8_t CELL_X_WIDTH = 26; // pixels
const uint8_t CELL_X_GAP = 1; // pixels
const uint8_t CELL_Y_HEIGHT = 18; // pixels
const uint8_t CELL_Y_GAP = 6; // pixels

void WatchyFaceX::drawFaceCalendar(
  bool enableDarkMode,
  bool enableInteractive
) {
  uint16_t bgColor = enableDarkMode ? GxEPD_BLACK : GxEPD_WHITE; 
  uint16_t textColor = enableDarkMode ? GxEPD_WHITE : GxEPD_BLACK; 
  display.fillScreen(bgColor);

  // CALENDAR
  uint8_t totalRows = (DISPLAY_HEIGHT - CELL_Y_GAP) / (CELL_Y_HEIGHT + CELL_Y_GAP);
  uint8_t totalCols = (DISPLAY_WIDTH - CELL_X_GAP) / (CELL_X_WIDTH + CELL_X_GAP);
  uint8_t cellX = 0;
  uint8_t cellY = 0;
  uint8_t textX = 0;
  uint8_t textY = 0;

  display.setFont(&FreeSans9pt7b);
  String message = "";

  for (uint8_t rowIndex = 0; rowIndex < (totalRows); rowIndex++) {
    for (uint8_t colIndex = 0; colIndex < (totalCols); colIndex++) {
      message += (rowIndex * 7) + (colIndex + 1);
      cellX = (colIndex * (CELL_X_WIDTH + CELL_X_GAP));
      cellY = (rowIndex * (CELL_Y_HEIGHT + CELL_Y_GAP));
      display.fillRect(
        cellX,
        cellY,
        CELL_X_WIDTH,
        CELL_Y_HEIGHT,
        textColor
      );
      textX = cellX;
      textY = cellY + CELL_Y_HEIGHT;
      display.setCursor(textX, textY);
      display.setTextColor(bgColor);
      display.print(message);
      message = ""; // reset message
    }
  }
}
