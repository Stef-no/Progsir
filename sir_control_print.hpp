#ifndef SIR_CONTROL_PRINT
#define SIR_CONTROL_PRINT

#include <iomanip>
#include <iostream>
#include <string>
#include <cassert>

#include "sir_epidemic.hpp"

inline void control_print(int day, int susc, int inf, int rec, double beta,
                          double gamma, int pop) {
  assert(susc >= 0 && susc <= pop &&
         "I suscettibili non sono compresi tra 0 e la popolazione totale.");
  assert(inf >= 0 && inf <= pop &&
         "Gli infetti non sono compresi tra 0 e la popolazione totale.");
  assert(rec >= 0 && rec <= pop &&
         "I rimossi non sono compresi tra 0 e la popolazione totale.");
  assert(beta >= 0 && beta <= 1 &&
         "L'indice di contagiosità non è compreso tra 0 e 1.");
  assert(gamma >= 0 && gamma <= 1 &&
         "L'indice di rimozione non è compreso tra 0 e 1.");
  assert(pop == susc + inf + rec &&
         "La popolazione è diversa dalla somma di suscettibili, infetti e "
         "rimossi.");
  assert(day >= 0 && "I giorni hanno valore negativo");

  std::cout << std::setw(9) << day << "|" << std::setw(12) << susc << "|"
            << std::setw(12) << inf << "|" << std::setw(12) << rec << "|"
            << std::setw(12) << beta << "|" << std::setw(12) << gamma << "|"
            << std::setw(12) << pop << "|\n";
}

#endif