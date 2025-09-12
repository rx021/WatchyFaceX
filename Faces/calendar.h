
//namespace calendar_face {

static const uint8_t WIDTH  = 200;
static const uint8_t HEIGHT = 200;
static const uint8_t GAP_X = 2;
static const uint8_t GAP_Y = 3;
static const uint8_t CELL_W = 26;
static const uint8_t CELL_H = 20;
static const uint8_t ORIGIN_X = (WIDTH - (7*CELL_W)) / 2;

static const char *MONTH_HEADER[12] = {
  "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"
};

// 0 = Sunday, 1 = Monday, 6 = Saturday, etc.
//static int START_OF_WEEK = 0; // Sunday start
static int START_OF_WEEK = 1; // Monday start
//static int START_OF_WEEK = 6; // Saturday start
static const char *WEEK_HEADER_BASE[7] = {"S","M","T","W","T","F","S"};

inline const char* getWeekHeader(int i) {
  return WEEK_HEADER_BASE[(i + START_OF_WEEK) % 7];
}

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
    ((year % 4) == 0 && (year % 100) != 0)
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
inline void leftText(GFX &display, const String &s, int x, int baselineY){
  display.setCursor(x, baselineY);
  display.print(s);
}

template<typename GFX>
inline void centerText(GFX &display, const String &s, int cx, int baselineY){
  int16_t x1,y1; uint16_t w,h;
  display.getTextBounds(s, 0, baselineY, &x1, &y1, &w, &h);
  display.setCursor(cx - (int)w/2, baselineY);
  display.print(s);
}

template<typename GFX>
inline int drawTitle(GFX &display, int year, int month, int textColor) {
  display.setFont(&FreeSansBold12pt7b);
  display.setTextColor(textColor);
  String title = String(year) + " " + String(MONTH_HEADER[month-1]);
  int16_t x1,y1; uint16_t w,h;
  display.getTextBounds(title, 0, 0, &x1, &y1, &w, &h);
  int baselineY = h;
  leftText(display, title, ORIGIN_X, baselineY);

  return baselineY; // new topY
}

template<typename GFX>
inline int drawWeekHeader(
  GFX &display,
  int textColor,
  int topY
){
  display.setFont(&FreeSansBold9pt7b);
  display.setTextColor(textColor);

  int16_t x1,y1; uint16_t w,h;
  String header;
  int rowY = 0;

  for(int col = 0; col < 7; col++){
    int colX = ORIGIN_X + col*CELL_W;
    header = getWeekHeader(col);
    display.getTextBounds(header, 0, 0, &x1, &y1, &w, &h);
    if (rowY == 0) { rowY = topY + h; }
    leftText(display, header, colX, rowY);
  }

  return rowY;
}

template<typename GFX>
inline void drawGrid(
  GFX &display,
  int topY,
  int uiYear,
  int uiMonth,
  int todayY,
  int todayM,
  int todayD,
  int bgColor,
  int textColor
){
  int firstDayOfWeek = dayOfWeekZeller(uiYear, uiMonth, 1);
  int totalDays = daysInMonth(uiYear, uiMonth);

  int monthX = ORIGIN_X - 1;
  int monthY = topY - 2;
  int monthWidth = 7*CELL_W + 2;
  int monthHeight = 6*CELL_H + 4;
  display.fillRect(monthX, monthY, monthWidth, monthHeight, textColor);

  display.setFont(&FreeSansBold9pt7b);
  for(int day=1; day<=totalDays; ++day){
    int index = (
        (firstDayOfWeek - START_OF_WEEK + 7) % 7
    ) + (day-1);
    int row = index / 7;
    int col = index % 7;

    int dayX = ORIGIN_X + col*CELL_W;
    int dayY = topY + row*CELL_H + 14;

    bool isToday = (uiYear==todayY && uiMonth==todayM && day==todayD);

    if(isToday){
      int paddingX = GAP_X / 2;
      int paddingY = GAP_Y / 2;
      int boxX = ORIGIN_X + col*CELL_W + paddingX;
      int boxY = topY + row*CELL_H + paddingY;
      int boxWidth = CELL_W - paddingX;
      int boxHeight = CELL_H - paddingY;
      display.fillRoundRect(boxX, boxY, boxWidth, boxHeight, 2, bgColor);
      display.setTextColor(textColor);
    }else{
      display.setTextColor(bgColor);
    }
    leftText(display, String(day), dayX, dayY);
  }
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

  int titleY = drawTitle(display, uiYear, uiMonth, textColor);
  int headerY = drawWeekHeader(display, textColor, titleY + GAP_Y);

  drawGrid(
    display,
    headerY + GAP_Y,
    uiYear, //state.calendarYear,
    uiMonth, //state.calendarMonth,
    year,
    month,
    day,
    bgColor,
    textColor
  );
}

