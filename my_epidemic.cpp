#include "my_epidemic.hpp"

#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <cassert>

#include "my_control_print.hpp"

namespace epidemic {

Contagion::Contagion(PandemicData const &initial_state, VarIndex const &di,
                     VarIndex const &b, VarIndex const &g, VarIndex const &vax,
                     const double vi, const int id, const int ps)
    : state_0(initial_state),
      DI(di),
      beta(b),
      gamma(g),
      Vax(vax),
      VaxIndex(vi),
      ImmDur(id),
      PanStart(ps){};

std::vector<PandemicData> Contagion::generate_data(int Duration_) {
  std::vector<PandemicData> result{state_0};
  PandemicData state = result.back();

  const int Pop =
      result[0].Susc + result[0].Inf + result[0].Dead + result[0].Heal;

  for (int i = 0; i < Duration_; ++i) {
    int NewRec = std::round(state.Gamma * state.Inf);
    int NewInf = std::round(state.Beta / Pop * state.Susc * state.Inf);
    int NewDead = std::round(NewRec * state.DeadIndex);

    if (i > DI.VarStart - PanStart) {
      if (DI.Var == 'Y' || DI.Var == 'y') {
        double exponentialDIY =
            std::exp((DI.VarStart - PanStart - i) * log(2) / DI.VarTime);
        state.DeadIndex = (result[0].DeadIndex * exponentialDIY);
      } else if (DI.Var == 'N' || DI.Var == 'n') {
        state.DeadIndex = result[0].DeadIndex;
      };
    } else {
      state.DeadIndex = result[0].DeadIndex;
    }

    if (i > beta.VarStart - PanStart) {
      if (beta.Var == 'Y' || beta.Var == 'y') {
        double exponentialbY =
            std::exp((beta.VarStart - PanStart - i) * log(2) / beta.VarTime);
        state.Beta = (result[0].Beta * exponentialbY);
      } else if (beta.Var == 'N' || beta.Var == 'n') {
        state.Beta = result[0].Beta;
      };
    } else {
      state.Beta = result[0].Beta;
    }

    if (i > gamma.VarStart - PanStart) {
      if (gamma.Var == 'Y' || gamma.Var == 'y') {
        double exponentialgY =
            std::exp((gamma.VarStart - PanStart - i) * log(2) / gamma.VarTime);
        state.Gamma = 1 - ((1 - result[0].Gamma) * exponentialgY);
      } else if (gamma.Var == 'N' || gamma.Var == 'n') {
        state.Gamma = result[0].Gamma;
      };
    } else {
      state.Gamma = result[0].Gamma;
    }

    if (i > ImmDur) {
      int j = i - ImmDur;
      state.NewSusc = result[j].Heal - result[j - 1].Heal + result[j].NewSusc;
    }

    int NewVax = 0;
    if (Vax.Var == 'Y' || Vax.Var == 'y')
      if (state.Inf >
          Pop * 0.001) {  // questo perchè, se la popolazione infetta risulta
                          // molto bassa rispetto al totale, le persone saranno
                          // spinte a non vaccinarsi
        if (Vax.VarStart <= i && Vax.VarStart + Vax.VarTime > i) {
          NewVax = (state.Susc + state.NewSusc - NewInf) * VaxIndex *
                   ((i - Vax.VarStart + 1.0) / Vax.VarTime);
        } else if (Vax.VarStart + Vax.VarTime <= i) {
          NewVax = (state.Susc + state.NewSusc - NewVax) * VaxIndex;
        }
      } else {
        NewVax = 0;
      }
    else {
      NewVax = 0;
    }

    state.Susc += state.NewSusc - NewInf - NewVax;
    state.Inf += NewInf - NewRec;
    state.Rec += NewRec + NewVax - state.NewSusc;
    state.Dead += NewDead;
    state.Heal += NewRec - NewDead + NewVax - state.NewSusc;
    state.NewSusc = state.NewSusc;

    assert(state.Susc >= 0 && state.Susc <= Pop);
    assert(state.Inf >= 0 && state.Inf <= Pop);
    assert(state.Rec >= 0 && state.Rec <= Pop);
    assert(state.Heal >= 0 && state.Heal <= state.Rec);
    assert(state.Dead >= 0 && state.Dead <= state.Rec);
    assert(Pop == state.Susc + state.Inf + state.Rec);
    assert(state.Rec == state.Heal + state.Dead);

    result.push_back(state);
  }
  return result;
};
}  // namespace epidemic