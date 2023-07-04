#ifndef DATE_HPP
#define DATE_HPP

#include <chrono>

inline std::chrono::system_clock::time_point FinalDate(int days) {
  std::chrono::system_clock::time_point const today =
      std::chrono::system_clock::now();
  std::chrono::system_clock::time_point future_date =
      today + std::chrono::hours(24 * days);

  return future_date;
}

#endif