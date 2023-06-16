#include "sir.hpp"

#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

#include "my_date.hpp"
#include "sir_control_print.hpp"

int main() {
  std::cout << "\nNell'inserimento dei parametri della pandemia si richiede di "
               "seguire le seguenti indicazioni: \n";
  std::cout << "- i dati temporali e riguardanti la popolazione siano numeri "
               "interi e positivi; \n";
  std::cout << "- gli indici siano numeri decimali compresi tra 0 e 1 (estremi "
               "inclusi); \n";
  std::cout << "- il formato delle risposte, in caso affermativo, deve essere "
               "Y/y mentre, in caso negativo, N/n. \n";

  std::cout << "\nInserire \n";
  int Pop_ = 0;
  while (true) {
    std::cout << "Popolazione totale:\t";
    std::cin >> Pop_;
    if (Pop_ > 0) {
      break;
    } else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "La popolazione deve avere un valore intero maggiore di 0.\n";
    }
  }

  int Inf_ = 0;
  while (true) {
    std::cout << "Popolazione infetta:\t";
    std::cin >> Inf_;
    if (Inf_ > 0 && Inf_ <= Pop_) {
      break;
    } else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr
          << "La popolazione infetta deve avere un valore intero compreso tra 1 e "
          << Pop_ << ".\n";
    }
  }

  int Rec_ = 0;

  while (true) {
    std::cout << "Popolazione rimossa:\t";
    std::cin >> Rec_;
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr
          << "La popolazione rimossa deve avere un valore intero compreso tra 0 e "
          << Pop_ - Inf_ << ".\n ";
    } else if (Rec_ >= 0 && Rec_ <= Pop_ - Inf_) {
      break;
    } else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr
          << "La popolazione rimossa deve avere un valore intero compreso tra 0 e "
          << Pop_ - Inf_ << ".\n ";
    }
  }

  std::string BetaMin = u8"\u03B2";
  double Beta_ = 0.0;
  while (true) {
    std::cout << "Indice di contagiosità (" << BetaMin << "):\t";
    std::cin >> Beta_;
    if (Beta_ > 0 && Beta_ <= 1) {  // se si include lo 0 dà problemi
      break;
    } else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "L'indice di contagiosità " << BetaMin
                << " deve avere un valore compreso tra 0 e 1.\n";
    }
  }

  std::string GammaMin = u8"\u03B3";
  double Gamma_ = 0.0;
  while (true) {
    std::cout << "Indice di rimozione (" << GammaMin << "):\t";
    std::cin >> Gamma_;
    if (Gamma_ > 0 && Gamma_ <= 1) {
      break;
    } else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "L'indice di rimozione " << GammaMin
                << " deve avere un valore compreso tra 0 e 1.\n";
    }
  }

  int Duration_ = 0;
  while (true) {
    std::cout << "Durata simulazione:\t";
    std::cin >> Duration_;
    if (Duration_ > 0) {
      break;
    } else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "La durata della simulazione deve essere un numero intero "
                   "positivo.\n";
    }
  }

  char View_ = 'a';
  while (true) {
    std::cout << "Vuoi vedere tutti i giorni in stampa?\t";
    std::cin >> View_;
    if (View_ == 'N' || View_ == 'n' || View_ == 'Y' || View_ == 'y') {
      break;
    } else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "La risposta deve essere nel formato Y/n.\n";
    }
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