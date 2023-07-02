#ifndef MY_CONTROL_PRINT_HPP
#define MY_CONTROL_PRINT_HPP

#include <iomanip>
#include <iostream>
#include <string>

#include "my_epidemic.hpp"

inline void control_print(int day, int susc, int inf, int dead, int heal,
                          int rec, int newsusc, double beta, double gamma,
                          double deadindex, double vaxindex, int pop) {
  assert(susc >= 0 && susc <= pop &&
         "I suscettibili non sono compresi tra 0 e la popolazione totale.");
  assert(inf >= 0 && inf <= pop &&
         "Gli infetti non sono compresi tra 0 e la popolazione totale.");
  assert(rec >= 0 && rec <= pop &&
         "I rimossi non sono compresi tra 0 e la popolazione totale.");
  assert(dead >= 0 && dead <= pop &&
         "I morti non sono compresi tra 0 e la popolazione totale.");
  assert(heal >= 0 && heal <= pop &&
         "I guariti non sono compresi tra 0 e la popolazione totale.");
  assert(newsusc >= 0 && newsusc <= pop &&
         "I nuovi suscettibili non sono compresi tra 0 e popolazione totale.");
  assert(heal >= 0 && heal <= rec &&
         "I guariti non sono compresi tra 0 e i rimossi.");
  assert(dead >= 0 && dead <= rec &&
         "I morti non sono compresi tra 0 e i rimossi.");
  assert(deadindex >= 0 && deadindex <= 1 &&
         "L'indice di mortalità non è compreso tra 0 e 1.");
  assert(vaxindex >= 0 && vaxindex <= 1 &&
         "L'indice di vaccinazione non è compreso tra 0 e 1.");
  assert(beta >= 0 && beta <= 1 &&
         "L'indice di contagiosità non è compreso tra 0 e 1.");
  assert(gamma >= 0 && gamma <= 1 &&
         "L'indice di rimozione non è compreso tra 0 e 1.");
  assert(pop == susc + inf + rec &&
         "La popolazione è diversa dalla somma di suscettibili, infetti e "
         "rimossi.");
  assert(rec == heal + dead &&
         "Il numero di rimossi è diverso dalla somma di guariti e morti.");
  assert(day >= 0 && "I giorni hanno valore negativo");

  std::cout << std::setw(9) << day << "|" << std::setw(12) << susc << "|"
            << std::setw(12) << inf << "|" << std::setw(12) << dead << "|"
            << std::setw(12) << heal << "|" << std::setw(12) << rec << "|"
            << std::setw(12) << newsusc << "|" << std::setw(12) << beta << "|"
            << std::setw(12) << gamma << "|" << std::setw(12) << deadindex
            << "|" << std::setw(12) << vaxindex << "|" << std::setw(12) << pop
            << "|\n";
}

#endif