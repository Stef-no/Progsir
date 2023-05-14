#ifndef MY_EPIDEMIC_HPP
#define MY_EPIDEMIC_HPP

#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>
#include <iomanip>

// cambiare if riga 47 di Previous 's' con y e n 

struct PandemicData {
  int Susc;
  int Inf;
  int Dead;
  int Heal;
  int Rec;
  int NewSusc;
  double Beta;
  double Gamma;
  double DeadIndex;
  double VaxIndex;
};

bool operator==(const std::vector<PandemicData> a,
                const std::vector<PandemicData> b) {
  bool res = true;
  int i = 0;
  for (auto it = a.begin(), end = a.end(); it != end; it++) {
    if (it->Susc == b[i].Susc && it->Inf == b[i].Inf && it->Dead == b[i].Dead &&
        it->Heal == b[i].Heal && it->NewSusc == b[i].NewSusc &&
        it->Beta == b[i].Beta && it->Gamma == b[i].Gamma &&
        it->DeadIndex == b[i].DeadIndex && it->VaxIndex == b[i].VaxIndex) {
      res = true;
    } else {
      return false;
    }
    i++;
  }  // guardare iteratori e for particolare più veloce
  return res;
}

void control_print(int day, int susc, int inf, int dead, int heal, int rec,
                   int newsusc, double beta, double gamma, double deadindex,
                   double vaxindex, int pop) {
  assert(susc >= 0 && susc <= pop);
  assert(inf >= 0 && inf <= pop);
  assert(rec >= 0 && rec <= pop);
  assert(dead >= 0 && dead <= pop);
  assert(heal >= 0 && heal <= pop);
  assert(newsusc >= 0 && newsusc <= pop);
  assert(heal >= 0 && heal <= rec);
  assert(dead >= 0 && dead <= rec);
  assert(deadindex >= 0 && deadindex <= 1);
  assert(vaxindex >= 0 && vaxindex <= 1);
  assert(beta >= 0 && beta <= 1);
  assert(gamma >= 0 && gamma <= 1);
  assert(pop == susc + inf + rec);
  assert(rec == heal + dead);
  assert(day >= 0);

  std::cout << std::setw(9) << day << "|" << std::setw(12) << susc << "|"
            << std::setw(12) << inf << "|" << std::setw(12) << dead << "|"
            << std::setw(12) << heal << "|" << std::setw(12) << rec << "|"
            << std::setw(12) << newsusc << "|" << std::setw(12) << beta << "|"
            << std::setw(12) << gamma << "|" << std::setw(12) << deadindex
            << "|" << std::setw(12) << vaxindex << "|" << std::setw(12) << pop
            << "|\n";
}

class Contagion {
 private:
  PandemicData newstate;
  int ImmDur;
  int PanStart;
  int VaxStart;
  int VaxMax;
  char Previous;

 public:
  Contagion(PandemicData& initial_state, int id, int ps, int vs, int vm, char p)
      : newstate{initial_state},
        ImmDur{id},
        PanStart{ps},
        VaxStart{vs},
        VaxMax{vm},
        Previous{p} {}

  std::vector<PandemicData> generate_data(int Duration_) {
    int hd = std::round(50 * exp(-2.0 * newstate.Beta) + 30);
    std::vector<PandemicData> result{newstate};
    PandemicData state = result.back();

    for (int i = 0; i < Duration_; ++i) {
      int Pop_ = newstate.Susc + newstate.Inf + newstate.Dead + newstate.Heal;
      int NewRec = std::round(newstate.Gamma * state.Inf);
      int NewInf = std::round(newstate.Beta / Pop_ * state.Susc * state.Inf);
      int NewDead = std::round(NewRec * newstate.DeadIndex);

      if (Previous == 'Y' || Previous == 'y') {
        if (i > hd - PanStart) {
          // deve essere inv prop a beta
          // int eY = ((i - hd + PanStart));
          double exponentialY = std::exp(-(i - hd + PanStart) / 260.0);
          state.DeadIndex = (result[0].DeadIndex * exponentialY);
        } else {
          state.DeadIndex = newstate.DeadIndex;
        }
      } else if (Previous == 'N' || Previous == 'n') {
        if (i > hd) {
          // int eN = ((i - hd));
          double exponentialN = std::exp(-(i - hd) / 260.0);
          state.DeadIndex = (result[0].DeadIndex * exponentialN);
        } else {
          state.DeadIndex = newstate.DeadIndex;
        }
      };

      if (i > ImmDur) {  // giorno 1, 0 i guariti -> inutile
        int j = i - ImmDur;
        newstate.NewSusc =
            result[j].Heal - result[j - 1].Heal + result[j].NewSusc;
      }

      int NewVax = 0;
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

      state.Susc += newstate.NewSusc - NewInf - NewVax;
      state.Inf += NewInf - NewRec;
      state.Rec += NewRec + NewVax - newstate.NewSusc; 
      state.Dead += NewDead;
      state.Heal += NewRec - NewDead + NewVax - newstate.NewSusc;
      state.NewSusc = newstate.NewSusc;

      result.push_back(state);  // vengono immagazzinati tutti i valori di state
                                // giorno per giorno
    }
    return result;
  }
};

#endif

// aggiungere giorni mancanti che fa il conto alla rovescia, utile per i doctest
// mettere le nascite