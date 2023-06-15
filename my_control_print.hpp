#ifndef MY_CONTROL_PRINT_HPP
#define MY_CONTROL_PRINT_HPP

#include "my_epidemic.hpp"

void control_print(int day, int susc, int inf, int dead, int heal, int rec,
                   int newsusc, double beta, double gamma, double deadindex,
                   double vaxindex, int pop) {
  assert(susc >= 0 && susc <= pop);
  assert(inf >= 0 && inf <= pop);
  assert(rec >= 0 && rec <= pop);
  assert(dead >= 0 && dead <= pop);
  assert(heal >= 0 && heal <= pop);
  assert(newsusc >= 0 && newsusc <= pop);
  assert(heal >= 0 && heal <= rec);
  assert(dead >= 0 && dead <= rec);
  assert(deadindex >= 0 && deadindex <= 1);
  assert(vaxindex >= 0 && vaxindex <= 1);
  assert(beta >= 0 && beta <= 1);
  assert(gamma >= 0 && gamma <= 1);
  assert(pop == susc + inf + rec);
  assert(rec == heal + dead);
  assert(day >= 0);

  std::cout << std::setw(9) << day << "|" << std::setw(12) << susc << "|"
            << std::setw(12) << inf << "|" << std::setw(12) << dead << "|"
            << std::setw(12) << heal << "|" << std::setw(12) << rec << "|"
            << std::setw(12) << newsusc << "|" << std::setw(12) << beta << "|"
            << std::setw(12) << gamma << "|" << std::setw(12) << deadindex
            << "|" << std::setw(12) << vaxindex << "|" << std::setw(12) << pop
            << "|\n";
}

#endif