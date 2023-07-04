#include "sir_epidemic.hpp"

#include <limits>
#include <cmath>
#include <string>
#include <cassert>

#include "sir_control_print.hpp"

namespace epidemic {

Simulation::Simulation(SirData const& initial_state, const double beta,
                       const double gamma)
    : state_0(initial_state), Beta(beta), Gamma(gamma){};

std::vector<SirData> Simulation::generate_data(int Duration_) {
  std::vector<SirData> result{state_0};
  SirData state = result.back();

  const int Pop = state_0.Susc + state_0.Inf + state_0.Rec;

  for (int i = 0; i < Duration_; ++i) {
    int NewRec = std::round(Gamma * state.Inf);
    int NewInf = std::round(Beta / Pop * state.Susc * state.Inf);

    state.Susc = state.Susc - NewInf;
    state.Inf += NewInf - NewRec;
    state.Rec += NewRec;

    assert(state.Susc >= 0 && state.Susc <= Pop);
    assert(state.Inf >= 0 && state.Inf <= Pop);
    assert(state.Rec >= 0 && state.Rec <= Pop);
    assert(Pop == state.Susc + state.Inf + state.Rec);


    result.push_back(state);
  }
  return result;
};
}  // namespace epidemic