#ifndef MY_DATE_HPP
#define MY_DATE_HPP

#include <chrono>
#include <string>
#include <vector>

inline int ConvToSec(int days) {
  int sec;
  sec = 86400 * days;

  return sec;
}

inline std::chrono::system_clock::time_point FinalDate(int days) {
  std::chrono::system_clock::time_point const today =
      std::chrono::system_clock::now();
  std::chrono::system_clock::time_point future_date =
      today + std::chrono::hours(24 * days);

  return future_date;
}

inline std::string ConvToString(int month) {
  std::vector<std::string> Months{
      "Gennaio", "Febbraio", "Marzo",     "Aprile",  "Maggio",   "Giugno",
      "Luglio",  "Agosto",   "Settembre", "Ottobre", "Novembre", "Dicembre"};

  return Months[month];
}

#endif