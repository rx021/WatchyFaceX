
const uint8_t CELL_X_WIDTH = 26; // pixels
const uint8_t CELL_X_GAP = 3; // pixels
const uint8_t CELL_Y_HEIGHT = 18; // pixels
const uint8_t CELL_Y_GAP = 8; // pixels

void WatchyFaceX::drawFaceCalendar(bool enableDarkMode) {
  uint16_t bgColor = enableDarkMode ? GxEPD_BLACK : GxEPD_WHITE; 
  uint16_t textColor = enableDarkMode ? GxEPD_WHITE : GxEPD_BLACK; 
  display.fillScreen(bgColor);

  // CALENDAR
  //display.setTextColor(textColor);
  //display.setFont(&FreeSans9pt7b);
  //String textString = ""; // must declare first to concat numbers

  uint8_t totalRows = DISPLAY_HEIGHT / CELL_Y_HEIGHT;
  uint8_t totalCols = DISPLAY_WIDTH / CELL_X_WIDTH;
  uint8_t cellX = 0;
  uint8_t cellY = 0;

  for (uint8_t rowIndex = 0; rowIndex < totalRows; rowIndex++) {
    for (uint8_t colIndex = 0; colIndex < totalCols; colIndex++) {
      cellX = (rowIndex * CELL_Y_GAP) + (rowIndex * CELL_Y_HEIGHT) + CELL_Y_HEIGHT;
      cellY = (colIndex * CELL_X_GAP) + (colIndex * CELL_X_WIDTH) + CELL_X_WIDTH;
      display.fillRect(
        cellX,
        cellY,
        CELL_X_WIDTH,
        CELL_X_HEIGHT,
        textColor
      );
    }
  }
}
