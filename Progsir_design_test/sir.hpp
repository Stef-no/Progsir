#ifndef SIR_HPP
#define SIR_HPP

#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

namespace epidemic {

struct SirData {
  int Susc;  // Popolazione suscettibile
  int Inf;   // Popolazione infetta
  int Rec;   // Popolazione rimossa
};

class Simulation {
 private:
  SirData newstate;
  double Beta;   // Indice di contagiosità
  double Gamma;  // Indice di mortalità

 public:
  Simulation(SirData const&, const double, const double);

  std::vector<SirData> generate_data(int);
};
}
#endif