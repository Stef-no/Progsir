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
      result[0].EpidemicPop.Susc + result[0].EpidemicPop.Inf + result[0].EpidemicPop.Dead + result[0].EpidemicPop.Heal;

  for (int i = 0; i < Duration_; ++i) {
    int NewRec = std::round(state.EpidemicIndex.Gamma * state.EpidemicPop.Inf);
    int NewInf = std::round(state.EpidemicIndex.Beta / Pop * state.EpidemicPop.Susc * state.EpidemicPop.Inf);
    int NewDead = std::round(NewRec * state.EpidemicIndex.DeadIndex);

    if (i > DI.VarStart - PanStart) {
      if (DI.Var == 'Y' || DI.Var == 'y') {
        double exponentialDIY =
            std::exp((DI.VarStart - PanStart - i) * log(2) / DI.VarTime);
        state.EpidemicIndex.DeadIndex = (result[0].EpidemicIndex.DeadIndex * exponentialDIY);
      } else if (DI.Var == 'N' || DI.Var == 'n') {
        state.EpidemicIndex.DeadIndex = result[0].EpidemicIndex.DeadIndex;
      };
    } else {
      state.EpidemicIndex.DeadIndex = result[0].EpidemicIndex.DeadIndex;
    }

    if (i > beta.VarStart - PanStart) {
      if (beta.Var == 'Y' || beta.Var == 'y') {
        double exponentialbY =
            std::exp((beta.VarStart - PanStart - i) * log(2) / beta.VarTime);
        state.EpidemicIndex.Beta = (result[0].EpidemicIndex.Beta * exponentialbY);
      } else if (beta.Var == 'N' || beta.Var == 'n') {
        state.EpidemicIndex.Beta = result[0].EpidemicIndex.Beta;
      };
    } else {
      state.EpidemicIndex.Beta = result[0].EpidemicIndex.Beta;
    }

    if (i > gamma.VarStart - PanStart) {
      if (gamma.Var == 'Y' || gamma.Var == 'y') {
        double exponentialgY =
            std::exp((gamma.VarStart - PanStart - i) * log(2) / gamma.VarTime);
        state.EpidemicIndex.Gamma = 1 - ((1 - result[0].EpidemicIndex.Gamma) * exponentialgY);
      } else if (gamma.Var == 'N' || gamma.Var == 'n') {
        state.EpidemicIndex.Gamma = result[0].EpidemicIndex.Gamma;
      };
    } else {
      state.EpidemicIndex.Gamma = result[0].EpidemicIndex.Gamma;
    }

    if (i > ImmDur) {
      int j = i - ImmDur;
      state.EpidemicPop.NewSusc = result[j].EpidemicPop.Heal - result[j - 1].EpidemicPop.Heal + result[j].EpidemicPop.NewSusc;
    }

    int NewVax = 0;
    if (Vax.Var == 'Y' || Vax.Var == 'y')
      if (state.EpidemicPop.Inf >
          Pop * 0.001) {  // questo perchè, se la popolazione infetta risulta
                          // molto bassa rispetto al totale, le persone saranno
                          // spinte a non vaccinarsi
        if (Vax.VarStart <= i && Vax.VarStart + Vax.VarTime > i) {
          NewVax = (state.EpidemicPop.Susc + state.EpidemicPop.NewSusc - NewInf) * VaxIndex *
                   ((i - Vax.VarStart + 1.0) / Vax.VarTime);
        } else if (Vax.VarStart + Vax.VarTime <= i) {
          NewVax = (state.EpidemicPop.Susc + state.EpidemicPop.NewSusc - NewVax) * VaxIndex;
        }
      } else {
        NewVax = 0;
      }
    else {
      NewVax = 0;
    }

    state.EpidemicPop.Susc += state.EpidemicPop.NewSusc - NewInf - NewVax;
    state.EpidemicPop.Inf += NewInf - NewRec;
    state.EpidemicPop.Rec += NewRec + NewVax - state.EpidemicPop.NewSusc;
    state.EpidemicPop.Dead += NewDead;
    state.EpidemicPop.Heal += NewRec - NewDead + NewVax - state.EpidemicPop.NewSusc;
    state.EpidemicPop.NewSusc = state.EpidemicPop.NewSusc;

    assert(state.EpidemicPop.Susc >= 0 && state.EpidemicPop.Susc <= Pop);
    assert(state.EpidemicPop.Inf >= 0 && state.EpidemicPop.Inf <= Pop);
    assert(state.EpidemicPop.Rec >= 0 && state.EpidemicPop.Rec <= Pop);
    assert(state.EpidemicPop.Heal >= 0 && state.EpidemicPop.Heal <= state.EpidemicPop.Rec);
    assert(state.EpidemicPop.Dead >= 0 && state.EpidemicPop.Dead <= state.EpidemicPop.Rec);
    assert(Pop == state.EpidemicPop.Susc + state.EpidemicPop.Inf + state.EpidemicPop.Rec);
    assert(state.EpidemicPop.Rec == state.EpidemicPop.Heal + state.EpidemicPop.Dead);

    result.push_back(state);
  }
  return result;
};
}  // namespace epidemic