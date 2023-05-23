#ifndef SIR_HPP
#define SIR_HPP

#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>
#include <iomanip>

// cambiare if riga 47 di Previous 's' con y e n 

struct SirData {
  int Susc;
  int Inf;
  int Rec;
  double Beta;
  double Gamma;
};

bool operator==(const std::vector<SirData> a,
                const std::vector<SirData> b) {
  bool res = true;
  int i = 0;
  for (auto it = a.begin(), end = a.end(); it != end; it++) {
    if (it->Susc == b[i].Susc && it->Inf == b[i].Inf &&
        it->Beta == b[i].Beta && it->Gamma == b[i].Gamma) {
      res = true;
    } else {
      return false;
    }
    i++;
  }  // guardare iteratori e for particolare più veloce
  return res;
}

void control_print(int day, int susc, int inf, int rec,
                  double beta, double gamma, int pop) {
  assert(susc >= 0 && susc <= pop);
  assert(inf >= 0 && inf <= pop);
  assert(rec >= 0 && rec <= pop);;
  assert(beta >= 0 && beta <= 1);
  assert(gamma >= 0 && gamma <= 1);
  assert(pop == susc + inf + rec);
  assert(day >= 0);

  std::cout << std::setw(9) << day << "|" << std::setw(12) << susc << "|"
            << std::setw(12) << inf << "|" << std::setw(12) << rec << "|" 
            << std::setw(12) << beta << "|" << std::setw(12) << gamma << "|" 
            << std::setw(12) << pop
            << "|\n";
}

class Simulation {
 private:
  SirData newstate;

 public:
  Simulation(SirData& initial_state)
      : newstate{initial_state} {}

  std::vector<SirData> generate_data(int Duration_) {
    std::vector<SirData> result{newstate};
    SirData state = result.back();

    for (int i = 0; i < Duration_; ++i) {
      int Pop_ = newstate.Susc + newstate.Inf + newstate.Rec;
      int NewRec = std::round(newstate.Gamma * state.Inf);
      int NewInf = std::round(newstate.Beta / Pop_ * state.Susc * state.Inf);
     

      state.Susc = state.Susc - NewInf;
      state.Inf += NewInf - NewRec;
      state.Rec += NewRec;

      result.push_back(state);  // vengono immagazzinati tutti i valori di state
                                // giorno per giorno
    }
    return result;
  }
};

#endif

// aggiungere giorni mancanti che fa il conto alla rovescia, utile per i doctest
// mettere le nascite