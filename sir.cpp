#include "sir.hpp"

#include <iomanip>
#include <iostream>

#include "my_date.hpp"

int main() {
  /*int Pop_, Inf_, Duration_, NewSusc_;
  double Beta_, Gamma_;  // so che Giacomini non apprezza

  Pop_ = 1010;
  Inf_ = 10;
  Beta_ = 0.3;
  Gamma_ = 0.05;
  Duration_ = 10;
  NewSusc_ = 0;*/
 
  std::cout << "Nell'inserimento dei dati della pandemia si richiede di seguire le seguenti indicazioni: \n";
  std::cout << "- i dati temporali e riguardanti la popolazione sono numeri interi e positivi; \n";
  std::cout << "- gli indici sono numeri decimali compresi tra 0 e 1 (estremi inclusi). \n";

  std::cout << "Inserire \n";
  int Pop_;
  std::cout << "Popolazione totale:\t";
  std::cin >> Pop_;
  while (Pop_ <= 0) {
    std::cout << " Population has to be > than 0.\n ";
    std::cin >> Pop_;
  }

  int Inf_;
  std::cout << "Popolazione infetta:\t";
  std::cin >> Inf_;
  while (Inf_ < 0 || Inf_ > Pop_) {
    std::cout << " Inf's value has to be between 0 and Pop's value.\n ";
    std::cin >> Inf_;
  }

  double Beta_;
  std::cout << "Indice di contagiosità:\t";
  std::cin >> Beta_;
  while (Beta_ < 0 || Beta_ > 1) {
    std::cout << " Beta's value has to be between 0 and 1.\n ";
    std::cin >> Beta_;
  }

  double Gamma_;
  std::cout << "Indice di rimozione:\t";
  std::cin >> Gamma_;
  while (Gamma_ < 0 || Gamma_ > 1) {
    std::cout << " Gamma's value has to be between 0 and 1.\n ";
    std::cin >> Gamma_;
  }


  int Duration_;
  std::cout << "Durata simulazione:\t";
  std::cin >> Duration_;
  while (Duration_ <= 0) {
    std::cout << " Duration has to be > than 0.\n ";
    std::cin >> Duration_;
  }


  int NewSusc_ = 0;

  char View_;
  std::cout << "Vuoi vedere tutti i giorni in stampa?\t";
  std::cin >> View_;
  while (View_ != 'N' && View_ != 'Y' && View_ != 'n' && View_ != 'y') {
    std::cout << " View has to be Y/n.\n ";
    std::cin >> View_;
  }

  SirData initial_state{Pop_ - Inf_ - Rec_,
                             Inf_,
                             Rec_,
                             NewSusc_,
                             Beta_,
                             Gamma_,
                             };
  
  Simulation epidemic{initial_state};
  std::vector<PandemicData> data = epidemic.generate_data(Duration_);
  int d = 0;
  std::cout << '\n'
            << std::setw(9) << "Giorno  "
            << "|" << std::setw(12) << "Suscettibili"
            << "|" << std::setw(12) << "Infetti  "
            << "|" << std::setw(12) << "Rimossi  "
            << "|" << std::setw(12) << "NewSusc  "
            << "|" << std::setw(12) << "Infettività "
            << "|" << std::setw(12) << "Rimozione  "
            << "|" << std::setw(12) << "Popolation "
            << "|\n"
            << "---------------------------------------------------------------"   
               "---------------------------------------------------------------"
               "---------------------------"
            << '\n';

  if (View_ == 'Y' || View_ == 'y') {
    while (d <= Duration_) {
      control_print(d, data[d].Susc, data[d].Inf,data[d].Rec, data[d].NewSusc,
                    data[d].Beta, data[d].Gamma, Pop_);
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
          control_print(d, data[d].Susc, data[d].Inf, data[d].Rec, data[d].NewSusc,
                        data[d].Beta, data[d].Gamma, Pop_);
          ++d;
        }
        break;

      case 'y':
        while (d <= Duration_) {
          control_print(d, data[d].Susc, data[d].Inf, data[d].Rec, data[d].NewSusc,
                        data[d].Beta, data[d].Gamma, Pop_);
          d += 10;
          if (d > Duration_ && d != Duration_ + 10) {
            control_print(Duration_, data[Duration_].Susc, data[Duration_].Inf,
                          data[Duration_].Rec, data[Duration_].NewSusc,
                          data[Duration_].Beta, data[Duration_].Gamma, Pop_);
          }
        }
        break;

      case 'z':
        while (d <= Duration_) {
          control_print(d, data[d].Susc, data[d].Inf, data[d].Rec, data[d].NewSusc,
                        data[d].Beta, data[d].Gamma, Pop_);
          d += 20;
          if (d > Duration_ && d != Duration_ + 20) {
            control_print(Duration_, data[Duration_].Susc, data[Duration_].Inf,
                          data[Duration_].Rec, data[Duration_].NewSusc,
                          data[Duration_].Beta, data[Duration_].Gamma, Pop_);
          }
        }
        break;
    }
  }

  std::cout << "---------------------------------------------------------------"
               "---------------------------------------------------------------"
               "---------------------------\n";

  now = time(0) + ConvToSec(Duration_);
  tm *ldt = localtime(&now);
  std::cout << "La simulazione termina il " << ldt->tm_mday << ' '
            << ConvToString(ldt->tm_mon) << ' ' << 1900 + ldt->tm_year
            << std::endl;
}
// grafici (Sani, Infetti, Morti, Guariti, Suscettibili, (Vaccinati)).
// variazioni automatiche b, g || variazioni predefinite in momenti
// giaco-defined (eventualmente con slider). Molto eventualmente mappa.
// aggiunta varianti tramite variabile (sigma) in base alle variazioni di b e g
// con spostamento di tutti i guariti nei suscettibili fino a (20) giorni prima.