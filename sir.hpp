#ifndef SIR_HPP
#define SIR_HPP

#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

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
  Simulation(SirData& initial_state, double beta, double gamma)
      : newstate{initial_state}, Beta{beta}, Gamma{gamma} {}

  std::vector<SirData> generate_data(int Duration_) {
    std::vector<SirData> result{newstate};
    SirData state = result.back();

    for (int i = 0; i < Duration_; ++i) {
      int Pop_ = newstate.Susc + newstate.Inf + newstate.Rec;
      int NewRec = std::round(Gamma * state.Inf);
      int NewInf = std::round(Beta / Pop_ * state.Susc * state.Inf);

      state.Susc = state.Susc - NewInf;
      state.Inf += NewInf - NewRec;
      state.Rec += NewRec;

      result.push_back(state);
    }
    return result;
  }
};

#endif