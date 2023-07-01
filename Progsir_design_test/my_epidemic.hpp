#ifndef MY_EPIDEMIC_HPP
#define MY_EPIDEMIC_HPP

#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

namespace epidemic {
/*
struct Index {
  double Beta;      // Indice di contagione
  double Gamma;     // Indice di rimozione
  double DeadIndex; // Indice di mortalità
  double VaxIndex;  // Indice di vaccinazione
};

struct PopulationData{
  int Susc;         // Popolazione suscettibile
  int Inf;          // Popolazione infetta
  int Dead;         // Popolazione morta
  int Heal;         // Popolazione guarita
  int Rec;          // Popolazione rimossa
  int NewSusc;      // Nuovi suscettibili
};

struct PandemicData {
  PopulationData PanPop;
  Index PanIndex;
};
*/
struct PandemicData {
  int Susc;         // Popolazione suscettibile
  int Inf;          // Popolazione infetta
  int Dead;         // Popolazione morta
  int Heal;         // Popolazione guarita
  int Rec;          // Popolazione rimossa
  int NewSusc;      // Nuovi suscettibili
  double Beta;      // Indice di contagione
  double Gamma;     // Indice di rimozione
  double DeadIndex; // Indice di mortalità
  double VaxIndex;  // Indice di vaccinazione
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
  const int ImmDur;   // Durata immunità dei guariti
  const int PanStart; // Giorni di Pandemia già trascorsi

public:
  // Le variabili in Contagion corrispondo alle sigle delle variabili
  // inizializzate nella parte privata
  Contagion(PandemicData const &, VarIndex const &, VarIndex const &,
            VarIndex const &, VarIndex const &, const int, const int);

  std::vector<PandemicData> generate_data(int);
};

} // namespace epidemic

#endif