#include "sir.hpp"

#include <iomanip>
#include <iostream>
#include <string>

#include "my_date.hpp"
#include "sir_control_print.hpp"

int main() {
  std::cout << "Nell'inserimento dei parametri della pandemia si richiede di "
               "seguire le seguenti indicazioni: \n";
  std::cout << "- i dati temporali e riguardanti la popolazione siano numeri "
               "interi e positivi; \n";
  std::cout << "- gli indici siano numeri decimali compresi tra 0 e 1 (estremi "
               "inclusi); \n";
  std::cout << "- il formato delle risposte, in caso affermativo, deve essere "
               "Y/y mentre, in caso negativo, N/n. \n";

  std::cout << "Inserire \n";
  int Pop_ = 0;
  std::cout << "Popolazione totale:\t";
  std::cin >> Pop_;
  while (Pop_ <= 0) {
    std::cout << " La popolazione deve essere maggiore di 0.\n ";
    std::cin >> Pop_;
  }

  int Inf_ = 0;
  std::cout << "Popolazione infetta:\t";
  std::cin >> Inf_;
  while (Inf_ < 0 || Inf_ > Pop_) {
    std::cout << " La popolazione infetta deve avere un valore compreso tra 0 "
                 "e la popolazione totale.\n ";
    std::cin >> Inf_;
  }

  int Rec_ = 0;
  std::cout << "Popolazione rimossa:\t";
  std::cin >> Rec_;
  while (Rec_ < 0 || Rec_ > Pop_) {
    std::cout << " La popolazione rimossa deve avere un valore compreso tra 0 "
                 "e la popolazione totale.\n ";
    std::cin >> Rec_;
  }

  std::string BetaMin = u8"\u03B2";
  double Beta_ = 0.0;
  std::cout << "Indice di contagiosità (" << BetaMin << "):\t";
  std::cin >> Beta_;
  while (Beta_ < 0 || Beta_ > 1) {
    std::cout << " L'indice di contagiosità deve avere un valore compreso tra "
                 "0 e 1.\n ";
    std::cin >> Beta_;
  }

  std::string GammaMin = u8"\u03B3";
  double Gamma_ = 0.0;
  std::cout << "Indice di rimozione (" << GammaMin << "):\t";
  std::cin >> Gamma_;
  while (Gamma_ < 0 || Gamma_ > 1) {
    std::cout
        << " L'indice di rimozione deve avere un valore compreso tra 0 e 1.\n";
    std::cin >> Gamma_;
  }

  int Duration_ = 0;
  std::cout << "Durata simulazione:\t";
  std::cin >> Duration_;
  while (Duration_ <= 0) {
    std::cout << " La durata deve essere maggiore di 0.\n ";
    std::cin >> Duration_;
  }

  char View_ = 'a';
  std::cout << "Vuoi vedere tutti i giorni in stampa?\t";
  std::cin >> View_;
  while (View_ != 'N' && View_ != 'Y' && View_ != 'n' && View_ != 'y') {
    std::cout << " La risposta deve essere nel formato Y/n.\n ";
    std::cin >> View_;
  }

  SirData initial_state{
      Pop_ - Inf_ - Rec_,
      Inf_,
      Rec_,
  };

  Simulation epidemic{initial_state, Beta_, Gamma_};
  std::vector<SirData> data = epidemic.generate_data(Duration_);
  int d = 0;
  std::cout << '\n'
            << std::setw(9) << "Giorno  "
            << "|" << std::setw(12) << "Suscettibili"
            << "|" << std::setw(12) << "Infetti  "
            << "|" << std::setw(12) << "Rimossi  "
            << "|" << std::setw(12) << "Infettività "
            << "|" << std::setw(12) << "Rimozione  "
            << "|" << std::setw(12) << "Popolation "
            << "|\n"
            << "---------------------------------------------------------------"
               "-------------------------"
            << '\n';

  if (View_ == 'Y' || View_ == 'y') {
    while (d <= Duration_) {
      control_print(d, data[d].Susc, data[d].Inf, data[d].Rec, Beta_, Gamma_,
                    Pop_);
      ++d;
    }
  } else if (View_ == 'N' || View_ == 'n') {
    char a = ' ';
    if (Duration_ <= 150) {
      a = 'x';
    } else if (Duration_ <= 500) {
      a = 'y';
    } else {
      a = 'z';
    }

    std::cout.precision(3);

    switch (a) {
      case 'x':
        while (d <= Duration_) {
          control_print(d, data[d].Susc, data[d].Inf, data[d].Rec, Beta_,
                        Gamma_, Pop_);
          ++d;
        }
        break;

      case 'y':
        while (d <= Duration_) {
          control_print(d, data[d].Susc, data[d].Inf, data[d].Rec, Beta_,
                        Gamma_, Pop_);
          d += 10;
          if (d > Duration_ && d != Duration_ + 10) {
            control_print(Duration_, data[Duration_].Susc, data[Duration_].Inf,
                          data[Duration_].Rec, Beta_, Gamma_, Pop_);
          }
        }
        break;

      case 'z':
        while (d <= Duration_) {
          control_print(d, data[d].Susc, data[d].Inf, data[d].Rec, Beta_,
                        Gamma_, Pop_);
          d += 20;
          if (d > Duration_ && d != Duration_ + 20) {
            control_print(Duration_, data[Duration_].Susc, data[Duration_].Inf,
                          data[Duration_].Rec, Beta_, Gamma_, Pop_);
          }
        }
        break;
    }
  }

  std::cout << "---------------------------------------------------------------"
               "-------------------------\n";

  now = time(0) + ConvToSec(Duration_);
  tm *ldt = localtime(&now);
  std::cout << "La simulazione termina il " << ldt->tm_mday << ' '
            << ConvToString(ldt->tm_mon) << ' ' << 1900 + ldt->tm_year
            << std::endl;
}