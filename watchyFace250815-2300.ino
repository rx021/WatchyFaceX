
#include "main.h"
#include "settings.h"
#include "secrets.h"

WatchyFaceX watchy(settings); //instantiate watch face

void setup() {
  const char* timezone = "PST8PDT,M3.2.0,M11.1.0"; // America/Vancouver
  // https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv

  setenv("TZ", timezone, 1);

  watchy.init();
}

void loop() {
  // put your main code here, to run repeatedly:
}
