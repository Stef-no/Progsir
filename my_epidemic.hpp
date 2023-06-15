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

class Contagion {
 private:
  PandemicData newstate;
  char DIVar;      // Varia mortalità?
  int DIVarStart;  // Giorno inizio variazione mortalità
  int DIVarTime;   // Tempo di dimezzamento mortalità
  int ImmDur;      // Durata immunità dei guariti
  char bVar;       // Varia beta?
  int bVarStart;   // Giorno inizio variazione beta
  int bVarTime;    // Tempo di dimezzamento di beta
  char gVar;       // Varia gamma?
  int gVarStart;   // Giorno inizio variazione gamma
  int gVarTime;    // Tempo di dimezzamento di 1-gamma
  int PanStart;    // Giorni di Pandemia già trascorsi
  char Vax;        // Vaccini?
  int VaxStart;    // Giorno inizio vaccini
  int VaxMax;      // Giorni per raggiungere massima velocità di vaccinazione
  char Previous;   // Pandemia già in corso?

 public:
  // Le variabili in Contagion corrispondo alle sigle delle variabili
  // inizializzate nella parte privata
  Contagion(PandemicData& initial_state, char div, int divs, int divt, int id,
            char bv, int bvs, int bvt, char gv, int gvs, int gvt, int ps,
            char v, int vs, int vm, char p)
      : newstate{initial_state},
        DIVar{div},
        DIVarStart{divs},
        DIVarTime{divt},
        ImmDur{id},
        bVar{bv},
        bVarStart{bvs},
        bVarTime{bvt},
        gVar{gv},
        gVarStart{gvs},
        gVarTime{gvt},
        PanStart{ps},
        Vax{v},
        VaxStart{vs},
        VaxMax{vm},
        Previous{p} {}

  std::vector<PandemicData> generate_data(int Duration_) {
    std::vector<PandemicData> result{newstate};
    PandemicData state = result.back();

    for (int i = 0; i < Duration_; ++i) {
      int Pop_ = newstate.Susc + newstate.Inf + newstate.Dead + newstate.Heal;
      int NewRec = std::round(newstate.Gamma * state.Inf);
      int NewInf = std::round(newstate.Beta / Pop_ * state.Susc * state.Inf);
      int NewDead = std::round(NewRec * newstate.DeadIndex);

      if (Previous == 'Y' || Previous == 'y') {
        if (i > DIVarStart - PanStart) {
          if (DIVar == 'Y' || DIVar == 'y') {
            double exponentialDIY =
                std::exp((DIVarStart - PanStart - i) * log(2) / DIVarTime);
            state.DeadIndex = (result[0].DeadIndex * exponentialDIY);
          } else if (bVar == 'N' || bVar == 'n') {
            state.DeadIndex = result[0].DeadIndex;
          };
        } else {
          state.DeadIndex = result[0].DeadIndex;
        }

        if (i > bVarStart - PanStart) {
          if (bVar == 'Y' || bVar == 'y') {
            double exponentialbY =
                std::exp((bVarStart - PanStart - i) * log(2) / bVarTime);
            state.Beta = (result[0].Beta * exponentialbY);
          } else if (bVar == 'N' || bVar == 'n') {
            state.Beta = result[0].Beta;
          };
        } else {
          state.Beta = result[0].Beta;
        }

        if (i > gVarStart - PanStart) {
          if (gVar == 'Y' || gVar == 'y') {
            double exponentialgY =
                std::exp((gVarStart - PanStart - i) * log(2) / gVarTime);
            state.Gamma = 1 - ((1 - result[0].Gamma) * exponentialgY);
          } else if (gVar == 'N' || gVar == 'n') {
            state.Gamma = result[0].Gamma;
          };
        } else {
          state.Gamma = result[0].Gamma;
        }

      } else if (Previous == 'N' || Previous == 'n') {
        if (i > DIVarStart) {
          if (DIVar == 'Y' || DIVar == 'y') {
            double exponentialDIY =
                std::exp((DIVarStart - i) * log(2) / DIVarTime);
            state.DeadIndex = (result[0].DeadIndex * exponentialDIY);
          } else if (bVar == 'N' || bVar == 'n') {
            state.DeadIndex = result[0].DeadIndex;
          };
        } else {
          state.DeadIndex = result[0].DeadIndex;
        }

        if (i > bVarStart - PanStart) {
          if (bVar == 'Y' || bVar == 'y') {
            double exponentialbY =
                std::exp((bVarStart - i) * log(2) / bVarTime);
            state.Beta = (result[0].Beta * exponentialbY);
          } else if (bVar == 'N' || bVar == 'n') {
            state.Beta = result[0].Beta;
          };
        } else {
          state.Beta = result[0].Beta;
        }

        if (i > gVarStart - PanStart) {
          if (gVar == 'Y' || gVar == 'y') {
            double exponentialgY =
                std::exp((gVarStart - i) * log(2) / gVarTime);
            state.Gamma = 1 - ((1 - result[0].Gamma) * exponentialgY);
          } else if (gVar == 'N' || gVar == 'n') {
            state.Gamma = result[0].Gamma;
          };
        } else {
          state.Gamma = result[0].Gamma;
        }
      };

      if (i > ImmDur) { 
        int j = i - ImmDur;
        newstate.NewSusc =
            result[j].Heal - result[j - 1].Heal + result[j].NewSusc;
      }

      int NewVax = 0;
      if (Vax == 'Y' || Vax == 'y')
        if (state.Inf > Pop_ * 0.001) {
          if (VaxStart <= i && VaxStart + VaxMax > i) {
            NewVax = (state.Susc + newstate.NewSusc - NewInf) *
                     newstate.VaxIndex * ((i - VaxStart + 1.0) / VaxMax);
          } else if (VaxStart + VaxMax <= i) {
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

      result.push_back(state);  
    }
    return result;
  }
};

#endif