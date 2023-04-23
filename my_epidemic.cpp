#include <iostream>
#include <iomanip>

#include "my_epidemic.hpp"
#include "my_date.hpp"


int main() {
/*
    int Pop, Inf, Dead, Heal, Duration, Imm, VaxStart, VaxMax, NewSusc;
    double Beta, Gamma, HealIndex, VaxIndex;  // so che Giacomini non apprezza
    char Previous;
    
    Pop = 1012;
    Inf = 10;
    Dead = 2;
    Heal = 0;
    Beta = 0.3;
    Gamma = 0.05;
    HealIndex = 0.5;
    Duration = 10;
    Imm = 0; // tempo di guarigione
    VaxStart = 0; // quando iniziano i vaccini
    Previous = 'y'; // pandemia già in corso?
    VaxIndex = 0.3;
    VaxMax = 0;
    NewSusc = 0;
*/
  
    std::cout << "Inserire \n";
    int Pop;
    std::cout << "Popolazione totale:\t";
    std::cin >> Pop;
    while ( Pop <= 0 ) {
        std::cout << " Population has to be > than 0.\n ";
        std::cin >> Pop;
    }

    int Inf;
    std::cout << "Popolazione infetta:\t";
    std::cin >> Inf;
    while ( Inf < 0 || Inf > Pop ) {
        std::cout << " Inf's value has to be between 0 and Pop's value.\n ";
        std::cin >> Inf;
    }

    double Beta;
    std::cout << "Indice di contagiosità:\t";
    std::cin >> Beta;
    while ( Beta < 0 || Beta > 1 ) {
        std::cout << " Beta's value has to be between 0 and 1.\n ";
        std::cin >> Beta;
    }

    double Gamma;
    std::cout << "Indice di rimozione:\t";
    std::cin >> Gamma;
    while ( Gamma < 0 || Gamma > 1 ) {
        std::cout << " Gamma's value has to be between 0 and 1.\n ";
        std::cin >> Gamma;
    }

    double HealIndex;
    std::cout << "Indice di guarigione:\t";
    std::cin >> HealIndex;
    while ( HealIndex < 0 || HealIndex > 1 ) {
        std::cout << " HealIndex's value has to be between 0 and 1.\n ";
        std::cin >> HealIndex;
    }

    double VaxIndex;
    std::cout << "Indice di vaccinazione:\t";
    std::cin >> VaxIndex;
    while ( VaxIndex < 0 || VaxIndex > 1 ) {
        std::cout << " VaxIndex's value has to be between 0 and 1.\n ";
        std::cin >> VaxIndex;
    }

    int Duration;
    std::cout << "Durata simulazione:\t";
    std::cin >> Duration;
    while ( Duration <= 0 ) {
        std::cout << " Duration has to be > than 0.\n ";
        std::cin >> Duration;
    }

    int Imm;
    std::cout << "Durata immunità:\t";
    std::cin >> Imm;
    while ( Imm <= 0 ) {
        std::cout << " Imm has to be > than 0.\n ";
        std::cin >> Imm;
    }

    int VaxStart;
    std::cout << "Giorno di inizio dei vaccini:\t";
    std::cin >> VaxStart;
    while ( VaxStart <= 0 ) {
        std::cout << " VaxStart has to be > than 0.\n ";
        std::cin >> VaxStart;
    }

    int VaxMax;
    std::cout << "Giorni per raggiungere la massima velocità percentuale di vaccinazione:\t";
    std::cin >> VaxMax;
    while ( VaxMax <= 0 ) {
        std::cout << " VaxMax has to be > than 0.\n ";
        std::cin >> VaxMax;
    }

    char Previous;
    std::cout << "La pandemia è già in corso?\t";
    std::cin >> Previous;
    while ( Previous != 'N' && Previous != 'Y' && Previous  != 'n' && Previous != 'y' ) {
        std::cout << " Previous has to be Y/n.\n ";
        std::cin >> Previous;
    }

    int PanStart;
    if ( Previous == 'Y' || Previous == 'y') {
        std::cout << " Da quanti giorni? \t";
        std::cin >> PanStart;
        while ( PanStart < 0 ) {
            std::cout << " PanStart has to be major than 0.\n ";
            std::cin >> PanStart;
        }
    } else {
        PanStart = 0;
    } 


    int Dead;
    if ( Previous == 'Y' || Previous == 'y') {
        std::cout << " Dead: \t";
        std::cin >> Dead;
        while ( Dead < 0 || Dead > Pop - Inf) {
            std::cout << " Dead has to be between 0 and Pop - Inf.\n ";
            std::cin >> Dead;
        }
    } else {
        Dead = 0;
    } 

    int Heal;
    if ( Previous == 'Y' || Previous == 'y') {
        std::cout << " Heal: \t";
        std::cin >> Heal;
        while ( Heal < 0 || Heal > Pop - Inf - Dead) {
            std::cout << " Heal has to be between 0 and Pop - Inf - Dead.\n ";
            std::cin >> Heal;
        }
    } else {
        Heal = 0;
    } 
    
    int NewSusc = 0;

    char View;
    std::cout << "Vuoi vedere tutti i giorni in stampa?\t";
    std::cin >> View;
    while ( View != 'N' && View != 'Y' && View != 'n' && View != 'y' ) {
        std::cout << " View has to be Y/n.\n ";
        std::cin >> View;
    }
   
    PandemicData initial_state  {Pop - Inf - Dead - Heal, Inf, Dead, Heal, Dead + Heal, Imm, PanStart, VaxStart, 
                                 VaxMax, NewSusc, Beta, Gamma, HealIndex, VaxIndex, Previous};  // aggiungere c
    Contagion epidemic{initial_state};
    std::vector<PandemicData> data = epidemic.generate_data(Duration - 1);
    int d = 0;
    std::cout << '\n' << std::setw(9) << "Giorno  " << "|" << std::setw(12) << "Suscettibili" << "|" 
              << std::setw(12) << "Infetti  " << "|" << std::setw(12) << "Morti   " << "|"
              << std::setw(12) << "Guariti  " << "|" << std::setw(12) << "Rimossi  " << "|" 
              << std::setw(12) << "NewSusc  " << "|" << std::setw(12) << "Infettività " << "|" 
              << std::setw(12) << "Rimozione  " << "|" << std::setw(12) << "Guarigione " << "|" 
              << std::setw(12) << "Vaccinazione" << "|" << std::setw(12) << "Popolation " << "|\n"
              << "---------------------------------------------------------------------------------------------------------------------------------------------------------" << '\n';

    if ( View == 'Y' || View == 'y') {
        while (d < Duration+1) {
                control_print   ( d, data[d].Susc_, data[d].Inf_, data[d].Dead_, data[d].Heal_, data[d].Rec_,
                                  data[d].NewSusc_, data[d].Beta_,  data[d].Gamma_, data[d].HealIndex_,
                                  data[d].VaxIndex_, Pop ); 
                ++d;
            }
    } else if ( View == 'N' || View == 'n') {
        char a = ' ';
        if (Duration <= 150) {
            a = 'x';
        } else if (Duration <= 500) {
            a = 'y';
        } else {
            a = 'z';
        }

        std::cout.precision(3);

        switch (a) {
            case 'x':
                while (d < Duration+1) {
                    control_print   ( d, data[d].Susc_, data[d].Inf_, data[d].Dead_, data[d].Heal_, data[d].Rec_,
                                      data[d].NewSusc_, data[d].Beta_, data[d].Gamma_, data[d].HealIndex_,
                                      data[d].VaxIndex_, Pop ); 
                    ++d;
                }
                break;

            case 'y':
                while (d < Duration+1) {
                    control_print   ( d, data[d].Susc_, data[d].Inf_, data[d].Dead_, data[d].Heal_, data[d].Rec_,
                                      data[d].NewSusc_, data[d].Beta_, data[d].Gamma_, data[d].HealIndex_, 
                                      data[d].VaxIndex_, Pop );;
                    d += 10;
                    if (d > Duration && d != Duration + 10) {
                        control_print   ( Duration, data[Duration].Susc_, data[Duration].Inf_, data[Duration].Dead_, 
                                          data[Duration].Heal_, data[Duration].Rec_, data[Duration].NewSusc_, 
                                          data[Duration].Beta_,  data[Duration].Gamma_, data[Duration].HealIndex_,
                                          data[Duration].VaxIndex_, Pop );
                    }
                }
                break;

            case 'z':
                while (d < Duration+1) {
                    control_print   ( d, data[d].Susc_, data[d].Inf_, data[d].Dead_, data[d].Heal_, data[d].Rec_,
                                      data[d].NewSusc_, data[d].Beta_,  data[d].Gamma_, data[d].HealIndex_, 
                                      data[d].VaxIndex_, Pop );
                    d += 20;
                    if (d > Duration && d != Duration + 20 ) {
                        control_print   ( Duration, data[Duration].Susc_, data[Duration].Inf_, data[Duration].Dead_, 
                                          data[Duration].Heal_, data[Duration].Rec_, data[Duration].NewSusc_, 
                                          data[Duration].Beta_,  data[Duration].Gamma_, data[Duration].HealIndex_,
                                          data[Duration].VaxIndex_, Pop );
                    }
                }
                break;
        }
    }
    
    std::cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------\n";

    now = time(0) + ConvToSec(Duration);
    tm *ldt = localtime(&now);
    std::cout << "La simulazione termina il " << ldt->tm_mday << ' ' << ConvToString(ldt->tm_mon) << ' '
              << 1900 + ldt->tm_year << std::endl;
}
// grafici (Sani, Infetti, Morti, Guariti, Suscettibili, (Vaccinati)).
// variazioni automatiche b, g || variazioni predefinite in momenti
// giaco-defined (eventualmente con slider). Molto eventualmente mappa.
// aggiunta varianti tramite variabile (sigma) in base alle variazioni di b e g
// con spostamento di tutti i guariti nei suscettibili fino a (20) giorni prima.