#include "sir.hpp"

#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

#include "sir_control_print.hpp"
// #include "my_date.hpp"

using namespace epidemic;

Simulation::Simulation(SirData const& initial_state, const double beta,
                       const double gamma)
    : newstate(initial_state), Beta(beta), Gamma(gamma){};

std::vector<SirData> Simulation::generate_data(int Duration_) {
  std::vector<SirData> result{newstate};
  SirData state = result.back();

  const int Pop = newstate.Susc + newstate.Inf + newstate.Rec;

  for (int i = 0; i < Duration_; ++i) {
    int NewRec = std::round(Gamma * state.Inf);
    int NewInf = std::round(Beta / Pop * state.Susc * state.Inf);

    state.Susc = state.Susc - NewInf;
    state.Inf += NewInf - NewRec;
    state.Rec += NewRec;

    result.push_back(state);
  }
  return result;
};