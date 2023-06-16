#include "my_epidemic.hpp"

#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

#include "my_control_print.hpp"
#include "my_date.hpp"

int main() {
  std::cout << "\nNell'inserimento dei dati della pandemia si richiede di "
               "seguire le seguenti indicazioni: \n";
  std::cout << "- i dati temporali e riguardanti la popolazione sono numeri "
               "interi e positivi; \n";
  std::cout << "- gli indici sono numeri decimali compresi tra 0 e 1 (estremi "
               "inclusi); \n";
  std::cout << "- il formato delle risposte, in caso affermativo, deve essere "
               "Y/y mentre, in caso negativo, N/n. \n\n";

  std::cout << "\nInserire \n";

  int Pop_ = 0;
  while (true) {
    std::cout << "Popolazione totale:\t";
    std::cin >> Pop_;
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr
          << "La popolazione deve avere un valore intero maggiore di 0.\n";
    } else if (Pop_ > 0) {
      break;
    } else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr
          << "La popolazione deve avere un valore intero maggiore di 0.\n";
    }
  }

  int Inf_ = 0;
  while (true) {
    std::cout << "Popolazione infetta:\t";
    std::cin >> Inf_;
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "La popolazione infetta deve avere un valore intero "
                   "compreso tra 1 e "
                << Pop_ << ".\n";
    } else if (std::cin.peek() == '.' || std::cin.peek() == ',') {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "La popolazione infetta deve avere un valore intero "
                   "compreso tra 1 e "
                << Pop_ << ".\n";
    } else if (Inf_ > 0 && Inf_ <= Pop_) {
      break;
    } else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "La popolazione infetta deve avere un valore intero "
                   "compreso tra 1 e "
                << Pop_ << ".\n";
    }
  }

  std::string BetaMin = u8"\u03B2";
  double Beta_ = 0.0;
  while (true) {
    std::cout << "Indice di contagiosità (" << BetaMin << "):\t";
    std::cin >> Beta_;
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "L'indice di contagiosità " << BetaMin
                << " deve avere un valore compreso tra 0 e 1.\n";
    } else if (Beta_ > 0 && Beta_ <= 1) {  // se si include lo 0 dà problemi
      break;
    } else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "L'indice di contagiosità " << BetaMin
                << " deve avere un valore compreso tra 0 e 1.\n";
    }
  }

  char bVar_ = 'a';
  while (true) {
    std::cout << "L'indice di contagiosità " << BetaMin << " varia?\t";
    std::cin >> bVar_;
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "La risposta deve essere nel formato Y/n.\n";
    } else if (bVar_ == 'N' || bVar_ == 'n' || bVar_ == 'Y' || bVar_ == 'y') {
      break;
    } else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "La risposta deve essere nel formato Y/n.\n";
    }
  }

  int bVarTime_ = 0;
  int bVarStart_ = 0;

  if (bVar_ == 'Y' || bVar_ == 'y') {
    while (true) {
      std::cout << "Giorno di inizio della diminuzione di " << BetaMin << ":\t";
      std::cin >> bVarStart_;
      if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Il giorno di inzio della diminuzione di " << BetaMin
                  << " deve essere un numero positivo.\n";
      } else if (std::cin.peek() == '.' || std::cin.peek() == ',') {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Il giorno di inzio della diminuzione di " << BetaMin
                  << " deve essere un numero positivo.\n";
      } else if (bVarStart_ >= 0) {
        break;
      } else {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Il giorno di inzio della diminuzione di " << BetaMin
                  << " deve essere un numero positivo.\n";
      }
    }
    while (true) {
      std::cout << "Tempo di dimezzamento dell'indice di contagiosità:\t";
      std::cin >> bVarTime_;
      if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Il tempo di dimezzamento di " << BetaMin
                  << " deve essere un numero intero positivo.\n";
      } else if (std::cin.peek() == '.' || std::cin.peek() == ',') {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Il tempo di dimezzamento di " << BetaMin
                  << " deve essere un numero intero positivo.\n";
      } else if (bVarTime_ > 0) {
        break;
      } else {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Il tempo di dimezzamento di " << BetaMin
                  << " deve essere un numero intero positivo.\n";
      }
    }
  }

  std::string GammaMin = u8"\u03B3";
  double Gamma_ = 0.0;
  while (true) {
    std::cout << "Indice di rimozione (" << GammaMin << "):\t";
    std::cin >> Gamma_;
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "L'indice di rimozione " << GammaMin
                << " deve avere un valore compreso tra 0 e 1.\n";
    } else if (Gamma_ > 0 && Gamma_ <= 1) {
      break;
    } else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "L'indice di rimozione " << GammaMin
                << " deve avere un valore compreso tra 0 e 1.\n";
    }
  }

  char gVar_ = 'a';
  while (true) {
    std::cout << "L'indice di rimozione " << GammaMin << " varia?\t";
    std::cin >> gVar_;
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else if (gVar_ == 'N' || gVar_ == 'n' || gVar_ == 'Y' || gVar_ == 'y') {
      break;
    } else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "La risposta deve essere nel formato Y/n.\n";
    }
  }

  int gVarStart_ = 0;
  int gVarTime_ = 0;

  if (gVar_ == 'Y' || gVar_ == 'y') {
    while (true) {
      std::cout << "Giorno di inizio della variazione di gamma:\t";
      std::cin >> gVarStart_;
      if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Il giorno di inzio della variazione di " << GammaMin
                  << " deve essere un numero intero positivo.\n";
      } else if (std::cin.peek() == '.' || std::cin.peek() == ',') {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Il giorno di inzio della variazione di " << GammaMin
                  << " deve essere un numero intero positivo.\n";
      } else if (gVarStart_ > 0) {
        break;
      } else {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Il giorno di inzio della variazione di " << GammaMin
                  << " deve essere un numero intero positivo.\n";
      }
    }
    while (true) {
      std::cout
          << "Tempo di aumento dell'indice di rimozione (dimezzamento di 1-"
          << GammaMin << "):\t";
      std::cin >> gVarTime_;
      if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Il tempo di variazione dell'indice di rimozione deve "
                     "essere un numero intero positivo.\n";
      } else if (std::cin.peek() == '.' || std::cin.peek() == ',') {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Il tempo di variazione dell'indice di rimozione deve "
                     "essere un numero intero positivo.\n";
      } else if (gVarTime_ > 0) {
        break;
      } else {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Il tempo di variazione dell'indice di rimozione deve "
                     "essere un numero intero positivo.\n";
      }
    }
  }

  double DeadIndex_ = 0.0;
  while (true) {
    std::cout << "Indice di mortalità:\t";
    std::cin >> DeadIndex_;
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "L'indice di mortalità deve avere un valore compreso tra "
                   "0 e 1.\n";
    } else if (std::cin.peek() == '.' || std::cin.peek() == ',') {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "L'indice di mortalità deve avere un valore compreso tra "
                   "0 e 1.\n";
    } else if (DeadIndex_ >= 0 && DeadIndex_ <= 1) {
      break;
    } else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "L'indice di mortalità deve avere un valore compreso tra "
                   "0 e 1.\n";
    }
  }

  char DIVar_ = 'a';
  while (true) {
    std::cout << "La mortalità varia?\t";
    std::cin >> DIVar_;
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "La risposta deve essere nel formato Y/n.\n";
    } else if (DIVar_ == 'N' || DIVar_ == 'n' || DIVar_ == 'Y' ||
               DIVar_ == 'y') {
      break;
    } else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "La risposta deve essere nel formato Y/n.\n";
    }
  }

  int DIVarTime_ = 0;
  int DIVarStart_ = 0;

  if (DIVar_ == 'Y' || DIVar_ == 'y') {
    while (true) {
      std::cout << "Giorno di inizio della variazione della mortalità:\t";
      std::cin >> DIVarStart_;
      if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Il giorno di inizio della variazione della mortalità "
                     "deve essere un numero intero positivo.\n";
      } else if (std::cin.peek() == '.' || std::cin.peek() == ',') {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Il giorno di inizio della variazione della mortalità "
                     "deve essere un numero intero positivo.\n";
      } else if (DIVarStart_ >= 0) {
        break;
      } else {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Il giorno di inizio della variazione della mortalità "
                     "deve essere un numero intero positivo.\n";
      }
    }
    while (true) {
      std::cout << "Tempo di dimezzamento dell'indice di mortalità:\t";
      std::cin >> DIVarTime_;
      if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Il tempo di dimezzamento dell'indice di mortalità deve "
                     "essere un numero intero positivo.\n";
      } else if (std::cin.peek() == '.' || std::cin.peek() == ',') {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Il tempo di dimezzamento dell'indice di mortalità deve "
                     "essere un numero intero positivo.\n";
      } else if (DIVarTime_ > 0) {
        break;
      } else {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Il tempo di dimezzamento dell'indice di mortalità deve "
                     "essere un numero intero positivo.\n";
      }
    }
  }

  char Vax_ = 'a';
  while (true) {
    std::cout << "Ci sono i vaccini?\t";
    std::cin >> Vax_;
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "La risposta deve essere nel formato Y/n.\n";
    } else if (Vax_ == 'N' || Vax_ == 'n' || Vax_ == 'Y' || Vax_ == 'y') {
      break;
    } else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "La risposta deve essere nel formato Y/n.\n";
    }
  }

  double VaxIndex_ = 0;
  int VaxStart_ = 0;
  int VaxMax_ = 0;

  if (Vax_ == 'Y' || Vax_ == 'y') {
    while (true) {
      std::cout << "Indice di vaccinazione:\t";
      std::cin >> VaxIndex_;
      if (VaxIndex_ > 0 && VaxIndex_ <= 1) {
        break;
      } else {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "L'indice di vaccinazione deve avere un valore compreso "
                     "tra 0 e 1.\n";
      }
    }
    while (true) {
      std::cout << "Giorno di inizio dei vaccini:\t";
      std::cin >> VaxStart_;
      if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Il giorno di inizio dei vaccini deve essere un numero "
                     "intero positivo.\n";
      } else if (std::cin.peek() == '.' || std::cin.peek() == ',') {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Il giorno di inizio dei vaccini deve essere un numero "
                     "intero positivo.\n";
      } else if (VaxStart_ >= 0) {
        break;
      } else {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Il giorno di inizio dei vaccini deve essere un numero "
                     "intero positivo.\n";
      }
    }
    while (true) {
      std::cout << "Giorni per raggiungere la massima velocità percentuale di "
                   "vaccinazione:\t";
      std::cin >> VaxMax_;
      if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "L'intervallo di tempo deve essere un numero intero "
                     "positivo.\n";
      } else if (std::cin.peek() == '.' || std::cin.peek() == ',') {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "L'intervallo di tempo deve essere un numero intero "
                     "positivo.\n";
      } else if (VaxMax_ > 0) {
        break;
      } else {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "L'intervallo di tempo deve essere un numero intero "
                     "positivo.\n";
      }
    }
  }

  int Duration_ = 0;
  while (true) {
    std::cout << "Durata simulazione:\t";
    std::cin >> Duration_;
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "La durata della simulazione deve essere un numero intero "
                   "positivo.\n";
    } else if (std::cin.peek() == '.' || std::cin.peek() == ',') {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "La durata della simulazione deve essere un numero intero "
                   "positivo.\n";
    } else if (Duration_ > 0) {
      break;
    } else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "La durata della simulazione deve essere un numero intero "
                   "positivo.\n";
    }
  }

  int ImmDur_ = 0;
  while (true) {
    std::cout << "Durata immunità:\t";
    std::cin >> ImmDur_;
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "La durata dell'immunità deve essere un numero intero "
                   "positivo.\n";
    } else if (std::cin.peek() == '.' || std::cin.peek() == ',') {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "La durata dell'immunità deve essere un numero intero "
                   "positivo.\n";
    } else if (ImmDur_ >= 0) {
      break;
    } else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "La durata dell'immunità deve essere un numero intero "
                   "positivo.\n";
    }
  }

  char Previous_ = 'a';
  while (true) {
    std::cout << "La pandemia è già in corso?\t";
    std::cin >> Previous_;
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "La risposta deve essere nel formato Y/n.\n";
    } else if (Previous_ == 'N' || Previous_ == 'n' || Previous_ == 'Y' ||
               Previous_ == 'y') {
      break;
    } else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "La risposta deve essere nel formato Y/n.\n";
    }
  }

  int PanStart_ = 0;
  if (Previous_ == 'Y' || Previous_ == 'y') {
    while (true) {
      std::cout << "Da quanti giorni?\t";
      std::cin >> PanStart_;
      if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Il numero di giorni deve essere maggiore o uguale a 0.\n";
      } else if (std::cin.peek() == '.' || std::cin.peek() == ',') {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Il numero di giorni deve essere maggiore o uguale a 0.\n";
      } else if (PanStart_ >= 0) {
        break;
      } else {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Il numero di giorni deve essere maggiore o uguale a 0.\n";
      }
    }
  }

  int Dead_ = 0;
  int Heal_ = 0;
  if (Previous_ == 'Y' || Previous_ == 'y') {
    while (true) {
      std::cout << "Numero di morti:\t";
      std::cin >> Dead_;
      if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr
            << "Il numero dei morti deve essere intero e compreso tra 0 e "
            << Pop_ - Inf_ << ", in base ai dati inseriti in precedenza.\n";
      } else if (std::cin.peek() == '.' || std::cin.peek() == ',') {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr
            << "Il numero dei morti deve essere intero e compreso tra 0 e "
            << Pop_ - Inf_ << ", in base ai dati inseriti in precedenza.\n";
      } else if (Dead_ >= 0 && Dead_ <= Pop_ - Inf_) {
        break;
      } else {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr
            << "Il numero dei morti deve essere intero e compreso tra 0 e "
            << Pop_ - Inf_ << ", in base ai dati inseriti in precedenza.\n";
      }
    }
    while (true) {
      std::cout << "Numero di guariti:\t";
      std::cin >> Heal_;
      if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr
            << "Il numero dei guariti deve essere intero e compreso tra 0 e "
            << Pop_ - Inf_ - Dead_
            << ", in base ai dati inseriti in precedenza.\n";
      } else if (std::cin.peek() == '.' || std::cin.peek() == ',') {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr
            << "Il numero dei guariti deve essere intero e compreso tra 0 e "
            << Pop_ - Inf_ - Dead_
            << ", in base ai dati inseriti in precedenza.\n";
      } else if (Heal_ > 0 && Heal_ <= Pop_ - Inf_ - Dead_) {
        break;
      } else {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr
            << "Il numero dei guariti deve essere intero e compreso tra 0 e "
            << Pop_ - Inf_ - Dead_
            << ", in base ai dati inseriti in precedenza.\n";
      }
    }
  }
  int NewSusc_ = 0;

  char View_ = 'a';
  while (true) {
    std::cout << "Vuoi vedere tutti i giorni in stampa?\t";
    std::cin >> View_;
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "La risposta deve essere nel formato Y/n.\n";
    } else if (View_ == 'N' || View_ == 'n' || View_ == 'Y' || View_ == 'y') {
      break;
    } else {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cerr << "La risposta deve essere nel formato Y/n.\n";
    }
  }

  int Interval_ = 1;

  if (View_ == 'N' || View_ == 'n') {
    while (true) {
      std::cout << "Intervallo di stampa:\t";
      std::cin >> Interval_;
      if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "L'intervallo deve essere intero positivo.\n";
      } else if (std::cin.peek() == '.' || std::cin.peek() == ',') {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "L'intervallo deve essere intero positivo.\n";
      } else if (Interval_ > 0) {
        break;
      } else {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "L'intervallo deve essere intero positivo.\n";
      }
    }
  }

  PandemicData initial_state{Pop_ - Inf_ - Dead_ - Heal_,
                             Inf_,
                             Dead_,
                             Heal_,
                             Dead_ + Heal_,
                             NewSusc_,
                             Beta_,
                             Gamma_,
                             DeadIndex_,
                             VaxIndex_};

  Contagion epidemic{initial_state, DIVar_,     DIVarStart_, DIVarTime_,
                     ImmDur_,       bVar_,      bVarStart_,  bVarTime_,
                     gVar_,         gVarStart_, gVarTime_,   PanStart_,
                     Vax_,          VaxStart_,  VaxMax_,     Previous_};

  std::vector<PandemicData> data = epidemic.generate_data(Duration_);

  int d = 0;

  std::cout << '\n'
            << std::setw(9) << "Giorno  "
            << "|" << std::setw(12) << "Suscettibili"
            << "|" << std::setw(12) << "Infetti  "
            << "|" << std::setw(12) << "Morti   "
            << "|" << std::setw(12) << "Guariti  "
            << "|" << std::setw(12) << "Rimossi  "
            << "|" << std::setw(12) << "NewSusc  "
            << "|" << std::setw(12) << "Infettività "
            << "|" << std::setw(12) << "Rimozione  "
            << "|" << std::setw(12) << "Mortalità  "
            << "|" << std::setw(12) << "Vaccinazione"
            << "|" << std::setw(12) << "Popolation "
            << "|\n"
            << "---------------------------------------------------------------"
               "---------------------------------------------------------------"
               "---------------------------"
            << '\n';

  while (d <= Duration_) {
    control_print(d, data[d].Susc, data[d].Inf, data[d].Dead, data[d].Heal,
                  data[d].Rec, data[d].NewSusc, data[d].Beta, data[d].Gamma,
                  data[d].DeadIndex, data[d].VaxIndex, Pop_);
    d += Interval_;
    if (d > Duration_ && d != Duration_ + Interval_) {
      control_print(Duration_, data[Duration_].Susc, data[Duration_].Inf,
                    data[Duration_].Dead, data[Duration_].Heal,
                    data[Duration_].Rec, data[Duration_].NewSusc,
                    data[Duration_].Beta, data[Duration_].Gamma,
                    data[Duration_].DeadIndex, data[Duration_].VaxIndex, Pop_);
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
