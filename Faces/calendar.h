
//namespace calendar_face {

static const uint16_t WIDTH  = 200;
static const uint16_t HEIGHT = 200;
static const uint8_t  MARGIN = 8;
static const uint8_t  GRID_TOP = 52;
static const uint8_t  CELL_W = 26;
static const uint8_t  CELL_H = 20;

static const char *WEEK_HEADER[7] = {"S","M","T","W","T","F","S"};
static const char *MONTH_HDR[12] = {
  "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"
};

inline int dayOfWeekZeller(int year, int month, int day){
  if (month < 3) { month += 12; year -= 1; }

  // K = year of century; J = zero-based century
  int K = year % 100, J = year / 100;
  int h = (day + (13*(month + 1))/5 + K + (K/4) + (J/4) + 5*J) % 7;
  // Saturday starts as 0

  return (h + 6) % 7; // Sunday=0
}

inline bool isLeapYear(int year){
  return (
    (year % 4 == 0 && year % 100 != 0)
    || (year % 400 == 0)
  );
}

inline int daysInMonth(int year, int month){
  static const int days[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

  return month == 2
    ? days[1] + (isLeapYear(year) ? 1 : 0)
    : days[month-1];
}


template<typename GFX>
inline void centerText(GFX &display, const String &s, int cx, int baselineY){
  int16_t x1,y1; uint16_t w,h;
  display.getTextBounds(s, 0, baselineY, &x1, &y1, &w, &h);
  display.setCursor(cx - (int)w/2, baselineY);
  display.print(s);
}

template<typename GFX>
inline void drawWeekHeader(GFX &display){
  //display.setFont(&FreeMonoBold9pt7b);
  display.setFont(&FreeSansBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  int x0 = (WIDTH - (7*CELL_W)) / 2;
  int y  = GRID_TOP - 16;
  for(int col = 0; col < 7; col++){
    int cx = x0 + col*CELL_W + CELL_W/2;
    centerText(display, WEEK_HEADER[col], cx, y);
  }
}

template<typename GFX>
inline void drawTitle(GFX &display, int year, int month){
  //display.setFont(&FreeMonoBold12pt7b);
  display.setFont(&FreeSansBold12pt7b);
  display.setTextColor(GxEPD_BLACK);
  String title = String(MONTH_HDR[month-1]) + " " + String(year);
  centerText(display, title, WIDTH/2, 24);
}

template<typename GFX>
inline void drawGrid(
  GFX &display,
  int uiYear,
  int uiMonth,
  int todayY,
  int todayM,
  int todayD,
  int bgColor,
  int textColor
){
  int firstDayOfWeek = dayOfWeekZeller(uiYear, uiMonth, 1);
  int dim = daysInMonth(uiYear, uiMonth);

  int x0 = (WIDTH - (7*CELL_W)) / 2;
  int y0 = GRID_TOP;

  //display.setFont(&FreeMono9pt7b);
  display.setFont(&FreeSans9pt7b);
  for(int day=1; day<=dim; ++day){
    int index = firstDayOfWeek + (day-1);
    int row = index / 7, col = index % 7;

    int cx = x0 + col*CELL_W + CELL_W/2;
    int cy = y0 + row*CELL_H + 14;

    bool isToday = (uiYear==todayY && uiMonth==todayM && day==todayD);

    if(isToday){
      int rx = x0 + col*CELL_W + 2;
      int ry = y0 + row*CELL_H + 3;
      display.fillRoundRect(rx, ry, CELL_W-4, CELL_H-6, 4, GxEPD_BLACK);
      display.setTextColor(bgColor);
    }else{
      display.setTextColor(textColor);
    }
    centerText(display, String(day), cx, cy);
  }
  display.drawRect(x0-1, y0-2, 7*CELL_W+2, 6*CELL_H+4, textColor);
}

// Top-level renderer
/*
template<typename GFX>
inline void render(GFX &display, int uiYear, int uiMonth,
                   int todayY, int todayM, int todayD){
  display.fillScreen(GxEPD_WHITE);
  drawTitle(display, uiYear, uiMonth);
  drawWeekHeader(display);
  drawGrid(display, uiYear, uiMonth, todayY, todayM, todayD);
}
*/

//} // namespace calendar_face

void WatchyFaceX::drawFaceCalendar(
  bool enableDarkMode,
  bool enableInteractive
) {
  uint16_t bgColor = enableDarkMode ? GxEPD_BLACK : GxEPD_WHITE; 
  uint16_t textColor = enableDarkMode ? GxEPD_WHITE : GxEPD_BLACK; 
  display.fillScreen(bgColor);

  tmElements_t t = currentTime;
  int year  = tmYearToCalendar(t.Year); // or (1970 + t.Year)
  int month = t.Month;
  int day   = t.Day;
  int uiYear  = year;
  int uiMonth = month;

  drawTitle(display, uiYear, uiMonth);

  drawWeekHeader(display);

  drawGrid(
    display,
    uiYear, //state.calendarYear,
    uiMonth, //state.calendarMonth,
    year,
    month,
    day,
    bgColor,
    textColor
  );
}

