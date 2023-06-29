#ifndef MY_EPIDEMIC_HPP
#define MY_EPIDEMIC_HPP

#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

struct PandemicData {
  int Susc;          // Popolazione suscettibile
  int Inf;           // Popolazione infetta
  int Dead;          // Popolazione morta
  int Heal;          // Popolazione guarita
  int Rec;           // Popolazione rimossa
  int NewSusc;       // Nuovi suscettibili
  double Beta;       // Indice di contagione
  double Gamma;      // Indice di rimozione
  double DeadIndex;  // Indice di mortalità
  double VaxIndex;   // Indice di vaccinazione
};

struct VarIndex {
  char Var;
  int VarStart;
  int VarTime;
};

class Contagion {
 private:
  PandemicData newstate;
  VarIndex DI;
  VarIndex beta;
  VarIndex gamma;
  VarIndex Vax;
  const int ImmDur;    // Durata immunità dei guariti
  const int PanStart;  // Giorni di Pandemia già trascorsi

 public:
  // Le variabili in Contagion corrispondo alle sigle delle variabili
  // inizializzate nella parte privata
  Contagion(PandemicData const& initial_state, VarIndex const& di,
            VarIndex const& b, VarIndex const& g, VarIndex const& vax,
            const int id, const int ps)
      : newstate{initial_state},
        DI{di},
        beta{b},
        gamma{g},
        Vax{vax},
        ImmDur{id},
        PanStart{ps} {}

  std::vector<PandemicData> generate_data(int Duration_) {
    std::vector<PandemicData> result{newstate};
    PandemicData state = result.back();

    const int Pop =
        result[0].Susc + result[0].Inf + result[0].Dead + result[0].Heal;

    for (int i = 0; i < Duration_; ++i) {
      int NewRec = std::round(newstate.Gamma * state.Inf);
      int NewInf = std::round(newstate.Beta / Pop * state.Susc * state.Inf);
      int NewDead = std::round(NewRec * newstate.DeadIndex);

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
        newstate.NewSusc =
            result[j].Heal - result[j - 1].Heal + result[j].NewSusc;
      }

      int NewVax = 0;
      if (Vax.Var == 'Y' || Vax.Var == 'y')
        if (state.Inf > Pop * 0.001) {
          if (Vax.VarStart <= i && Vax.VarStart + Vax.VarTime > i) {
            NewVax = (state.Susc + newstate.NewSusc - NewInf) *
                     newstate.VaxIndex * ((i - Vax.VarStart + 1.0) / Vax.VarTime);
          } else if (Vax.VarStart + Vax.VarTime <= i) {
            NewVax =
                (state.Susc + newstate.NewSusc - NewVax) * newstate.VaxIndex;
          }
        } else {
          NewVax = 0;
        }
      else {
        NewVax = 0;
      }

      state.Susc += newstate.NewSusc - NewInf - NewVax;
      state.Inf += NewInf - NewRec;
      state.Rec += NewRec + NewVax - newstate.NewSusc;
      state.Dead += NewDead;
      state.Heal += NewRec - NewDead + NewVax - newstate.NewSusc;
      state.NewSusc = newstate.NewSusc;

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
  }
};

#endif