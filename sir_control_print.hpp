#ifndef SIR_CONTROL_PRINT
#define SIR_CONTROL_PRINT

#include <iostream>

#include "my_epidemic.hpp"

void control_print(int day, int susc, int inf, int rec, double beta, double gamma, int pop) {
    assert(susc >= 0 && susc <= pop);
    assert(inf >= 0 && inf <= pop);
    assert(rec >= 0 && rec <= pop);
    assert(beta >= 0 && beta <= 1);
    assert(gamma >= 0 && gamma <= 1);
    assert(pop == susc + inf + rec);
    assert(day >= 0);

    std::cout << std::setw(9) << day << "|" << std::setw(12) << susc << "|"
              << std::setw(12) << inf << "|" << std::setw(12) << rec << "|"
              << std::setw(12) << beta << "|" << std::setw(12) << gamma << "|"
              << std::setw(12) << pop << "|\n";
}

#endif