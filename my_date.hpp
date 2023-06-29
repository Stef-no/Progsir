#ifndef MY_DATE_HPP
#define MY_DATE_HPP

#include <ctime>
#include <vector>
#include <string>

time_t now;

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

#endif