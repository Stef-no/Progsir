#include <iostream>
#include <iomanip>

#include "my_epidemic.hpp"
#include "my_date.hpp"


int main() {

    int Pop_, Inf_, Dead_, Heal_, Duration_, Imm_, PanStart_, VaxStart_, VaxMax_, NewSusc_;
    double Beta_, Gamma_, HealIndex_, VaxIndex_;  // so che Giacomini non apprezza
    char Previous_;
    
    Pop_ = 1010;
    Inf_ = 10;
    Dead_ = 0;
    Heal_ = 0;
    Beta_ = 0.3;
    Gamma_ = 0.05;
    HealIndex_ = 0.5;
    Duration_ = 10;
    Imm_ = 1; // tempo di guarigione
    PanStart_ = 0;
    VaxStart_ = 1; // quando iniziano i vaccini
    Previous_ = 'n'; // pandemia già in corso?
    VaxIndex_ = 0.3;
    VaxMax_ = 1;
    NewSusc_ = 0;
    char View_ = 'y';

  /*
    std::cout << "Inserire \n";
    int Pop_;
    std::cout << "Popolazione totale:\t";
    std::cin >> Pop_;
    while ( Pop_ <= 0 ) {
        std::cout << " Population has to be > than 0.\n ";
        std::cin >> Pop_;
    }

    int Inf_;
    std::cout << "Popolazione infetta:\t";
    std::cin >> Inf_;
    while ( Inf_ < 0 || Inf_ > Pop_ ) {
        std::cout << " Inf's value has to be between 0 and Pop's value.\n ";
        std::cin >> Inf_;
    }

    double Beta_;
    std::cout << "Indice di contagiosità:\t";
    std::cin >> Beta_;
    while ( Beta_ < 0 || Beta_ > 1 ) {
        std::cout << " Beta's value has to be between 0 and 1.\n ";
        std::cin >> Beta_;
    }

    double Gamma_;
    std::cout << "Indice di rimozione:\t";
    std::cin >> Gamma_;
    while ( Gamma_ < 0 || Gamma_ > 1 ) {
        std::cout << " Gamma's value has to be between 0 and 1.\n ";
        std::cin >> Gamma_;
    }

    double HealIndex_;
    std::cout << "Indice di guarigione:\t";
    std::cin >> HealIndex_;
    while ( HealIndex_ < 0 || HealIndex_ > 1 ) {
        std::cout << " HealIndex's value has to be between 0 and 1.\n ";
        std::cin >> HealIndex_;
    }

    double VaxIndex_;
    std::cout << "Indice di vaccinazione:\t";
    std::cin >> VaxIndex_;
    while ( VaxIndex_ < 0 || VaxIndex_ > 1 ) {
        std::cout << " VaxIndex's value has to be between 0 and 1.\n ";
        std::cin >> VaxIndex_;
    }

    int Duration_;
    std::cout << "Durata simulazione:\t";
    std::cin >> Duration_;
    while ( Duration_ <= 0 ) {
        std::cout << " Duration has to be > than 0.\n ";
        std::cin >> Duration_;
    }

    int Imm_;
    std::cout << "Durata immunità:\t";
    std::cin >> Imm_;
    while ( Imm_ <= 0 ) {
        std::cout << " Imm has to be > than 0.\n ";
        std::cin >> Imm_;
    }

    int VaxStart_;
    std::cout << "Giorno di inizio dei vaccini:\t";
    std::cin >> VaxStart_;
    while ( VaxStart_ <= 0 ) {
        std::cout << " VaxStart has to be > than 0.\n ";
        std::cin >> VaxStart_;
    }

    int VaxMax_;
    std::cout << "Giorni per raggiungere la massima velocità percentuale di vaccinazione:\t";
    std::cin >> VaxMax_;
    while ( VaxMax_ <= 0 ) {
        std::cout << " VaxMax has to be > than 0.\n ";
        std::cin >> VaxMax_;
    }

    char Previous_;
    std::cout << "La pandemia è già in corso?\t";
    std::cin >> Previous_;
    while ( Previous_ != 'N' && Previous_ != 'Y' && Previous_  != 'n' && Previous_ != 'y' ) {
        std::cout << " Previous has to be Y/n.\n ";
        std::cin >> Previous_;
    }

    int PanStart_;
    if ( Previous_ == 'Y' || Previous_ == 'y') {
        std::cout << " Da quanti giorni? \t";
        std::cin >> PanStart_;
        while ( PanStart_ < 0 ) {
            std::cout << " PanStart has to be major than 0.\n ";
            std::cin >> PanStart_;
        }
    } else {
        PanStart_ = 0;
    } 


    int Dead_;
    if ( Previous_ == 'Y' || Previous_ == 'y') {
        std::cout << " Dead: \t";
        std::cin >> Dead_;
        while ( Dead_ < 0 || Dead_ > Pop_ - Inf_) {
            std::cout << " Dead has to be between 0 and Pop - Inf.\n ";
            std::cin >> Dead_;
        }
    } else {
        Dead_ = 0;
    } 

    int Heal_;
    if ( Previous_ == 'Y' || Previous_ == 'y') {
        std::cout << " Heal: \t";
        std::cin >> Heal_;
        while ( Heal_ < 0 || Heal_ > Pop_ - Inf_ - Dead_) {
            std::cout << " Heal has to be between 0 and Pop - Inf - Dead.\n ";
            std::cin >> Heal_;
        }
    } else {
        Heal_ = 0;
    } 
    
    int NewSusc_ = 0;

    char View_;
    std::cout << "Vuoi vedere tutti i giorni in stampa?\t";
    std::cin >> View_;
    while ( View_ != 'N' && View_ != 'Y' && View_ != 'n' && View_ != 'y' ) {
        std::cout << " View has to be Y/n.\n ";
        std::cin >> View_;
    }
    */
   
    PandemicData initial_state  {Pop_ - Inf_ - Dead_ - Heal_, Inf_, Dead_, Heal_, Dead_ + Heal_, Imm_, PanStart_, VaxStart_, 
                                 VaxMax_, NewSusc_, Beta_, Gamma_, HealIndex_, VaxIndex_};  // aggiungere c
    Contagion epidemic{initial_state,Previous_};
    std::vector<PandemicData> data = epidemic.generate_data(Duration_ - 1);
    int d = 0;
    std::cout << '\n' << std::setw(9) << "Giorno  " << "|" << std::setw(12) << "Suscettibili" << "|" 
              << std::setw(12) << "Infetti  " << "|" << std::setw(12) << "Morti   " << "|"
              << std::setw(12) << "Guariti  " << "|" << std::setw(12) << "Rimossi  " << "|" 
              << std::setw(12) << "NewSusc  " << "|" << std::setw(12) << "Infettività " << "|" 
              << std::setw(12) << "Rimozione  " << "|" << std::setw(12) << "Guarigione " << "|" 
              << std::setw(12) << "Vaccinazione" << "|" << std::setw(12) << "Popolation " << "|\n"
              << "---------------------------------------------------------------------------------------------------------------------------------------------------------" << '\n';

    if ( View_ == 'Y' || View_ == 'y') {
        while (d < Duration_+1) {
                control_print   ( d, data[d].Susc, data[d].Inf, data[d].Dead, data[d].Heal, data[d].Rec,
                                  data[d].NewSusc, data[d].Beta,  data[d].Gamma, data[d].HealIndex,
                                  data[d].VaxIndex, Pop_ ); 
                ++d;
            }
    } else if ( View_ == 'N' || View_ == 'n') {
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
                while (d < Duration_+1) {
                    control_print   ( d, data[d].Susc, data[d].Inf, data[d].Dead, data[d].Heal, data[d].Rec,
                                      data[d].NewSusc, data[d].Beta,  data[d].Gamma, data[d].HealIndex, 
                                      data[d].VaxIndex, Pop_ ); 
                    ++d;
                }
                break;

            case 'y':
                while (d < Duration_+1) {
                    control_print   ( d, data[d].Susc, data[d].Inf, data[d].Dead, data[d].Heal, data[d].Rec,
                                      data[d].NewSusc, data[d].Beta,  data[d].Gamma, data[d].HealIndex, 
                                      data[d].VaxIndex, Pop_ );
                    d += 10;
                    if (d > Duration_ && d != Duration_ + 10) {
                        control_print   ( Duration_, data[Duration_].Susc, data[Duration_].Inf, data[Duration_].Dead, 
                                          data[Duration_].Heal, data[Duration_].Rec, data[Duration_].NewSusc, 
                                          data[Duration_].Beta,  data[Duration_].Gamma, data[Duration_].HealIndex,
                                          data[Duration_].VaxIndex, Pop_ );
                    }
                }
                break;

            case 'z':
                while (d < Duration_+1) {
                    control_print   ( d, data[d].Susc, data[d].Inf, data[d].Dead, data[d].Heal, data[d].Rec,
                                      data[d].NewSusc, data[d].Beta,  data[d].Gamma, data[d].HealIndex, 
                                      data[d].VaxIndex, Pop_ );
                    d += 20;
                    if (d > Duration_ && d != Duration_ + 20 ) {
                        control_print   ( Duration_, data[Duration_].Susc, data[Duration_].Inf, data[Duration_].Dead, 
                                          data[Duration_].Heal, data[Duration_].Rec, data[Duration_].NewSusc, 
                                          data[Duration_].Beta,  data[Duration_].Gamma, data[Duration_].HealIndex,
                                          data[Duration_].VaxIndex, Pop_ );
                    }
                }
                break;
        }
    }
    
    std::cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------\n";

    now = time(0) + ConvToSec(Duration_);
    tm *ldt = localtime(&now);
    std::cout << "La simulazione termina il " << ldt->tm_mday << ' ' << ConvToString(ldt->tm_mon) << ' '
              << 1900 + ldt->tm_year << std::endl;
}
// grafici (Sani, Infetti, Morti, Guariti, Suscettibili, (Vaccinati)).
// variazioni automatiche b, g || variazioni predefinite in momenti
// giaco-defined (eventualmente con slider). Molto eventualmente mappa.
// aggiunta varianti tramite variabile (sigma) in base alle variazioni di b e g
// con spostamento di tutti i guariti nei suscettibili fino a (20) giorni prima.