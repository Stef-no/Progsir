#ifndef MY_EPIDEMIC_HPP
#define MY_EPIDEMIC_HPP

#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

namespace epidemic {

struct PandemicData {
  int Susc;          // Popolazione suscettibile
  int Inf;           // Popolazione infetta
  int Dead;          // Popolazione morta
  int Heal;          // Popolazione guarita
  int Rec;           // Popolazione rimossa
  int NewSusc;       // Nuovi suscettibili
  double Beta;       // Indice di contagiosità
  double Gamma;      // Indice di rimozione
  double DeadIndex;  // Indice di mortalità
};

struct VarIndex {
  char Var;      // L'indice varia?
  int VarStart;  // Giorno di inizio della variazione dell'indice
  int VarTime;   // Tempo di variazione dell'indice
};

class Contagion {
 private:
  PandemicData state_0;
  VarIndex DI;
  VarIndex beta;
  VarIndex gamma;
  VarIndex Vax;
  double VaxIndex;   // Indice di vaccinazione
  const int ImmDur;    // Durata immunità dei guariti
  const int PanStart;  // Giorni di Pandemia già trascorsi

 public:
  // Le variabili in Contagion corrispondo alle sigle delle variabili
  // inizializzate nella parte privata
  Contagion(PandemicData const &, VarIndex const &, VarIndex const &,
            VarIndex const &, VarIndex const &, const double, const int, const int);

  std::vector<PandemicData> generate_data(int);
};

}  // namespace epidemic

#endif