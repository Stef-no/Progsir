#include <ctime>
#include <vector>

time_t now;
int d = 0;

int ConvToSec(int days) {
  int sec;
  sec = 86400 * days;

  return sec;
}

auto FinalDate(int days) {
  time(&now);
  now += ConvToSec(days);

  return &now;
}

std::string ConvToString(int month) {
  std::vector<std::string> Months{
      "Gennaio", "Febbraio", "Marzo",     "Aprile",  "Maggio",   "Giugno",
      "Luglio",  "Agosto",   "Settembre", "Ottobre", "Novembre", "Dicembre"};

  return Months[month];
}