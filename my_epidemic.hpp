#ifndef MY_EPIDEMIC_HPP
#define MY_EPIDEMIC_HPP

#include <cmath>
#include <vector>
#include <cassert>
#include <iostream>

//cambiare if riga 47 di Previous 's' con y e n  e cambiare funzione di aumento healindex 

struct PandemicData {                      
    int Susc;
    int Inf;
    int Dead;
    int Heal;
    int Rec;
    //int ImmDur;
    //int PanStart;
    //int VaxStart;
    //int VaxMax;
    int NewSusc;  
    double Beta;
    double Gamma;
    double HealIndex;
    double VaxIndex;          
    //char Previous;                         
};

bool operator== ( const std::vector<PandemicData> a, const std::vector<PandemicData> b) { 
    bool res = true;
    int i=0;
    for(auto it = a.begin(), end = a.end(); it!=end;it++){ 
        if( it->Susc==b[i].Susc && it->Inf==b[i].Inf && it->Dead==b[i].Dead && it->Heal==b[i].Heal &&
            /*it->Rec==b[i].Rec && it->ImmDur==b[i].ImmDur && it->PanStart==b[i].PanStart && 
            it->VaxStart==b[i].VaxStart && it->VaxMax==b[i].VaxMax &&*/ it->NewSusc==b[i].NewSusc && 
            it->Beta==b[i].Beta && it->Gamma==b[i].Gamma && it->HealIndex==b[i].HealIndex && 
            it->VaxIndex==b[i].VaxIndex) {
        res = true;
        }
        else {
            return false;
        }
        i++;
    }//guardare iteratori e for particolare più veloce 
    return res;
} 

void control_print ( int day, int susc, int inf, int dead, int heal, int rec, int newsusc,
                     double beta, double gamma, double healindex, double vaxindex, int pop ) {

    assert ( susc >= 0 && susc <= pop );
    assert ( inf >= 0 && inf <= pop );
    assert ( rec >= 0 && rec <= pop );
    assert ( dead >= 0 && dead <= pop );
    assert ( heal >= 0 && heal <= pop );
    assert ( newsusc >= 0 && newsusc <= pop );
    assert ( rec >= 0 && rec <= pop );
    assert ( heal >= 0 && heal <= rec );
    assert ( dead >= 0 && dead <= rec );
    assert ( healindex >= 0 && healindex <= 1 );
    assert ( vaxindex >= 0 && vaxindex <= 1 );
    assert ( beta >= 0 && beta <= 1 );
    assert ( gamma >= 0 && gamma <= 1 );
    assert ( pop == susc + inf + rec );
    assert ( rec == heal + dead); 
    assert ( day >= 0 );

    std::cout << std::setw(9) << day << "|" << std::setw(12) << susc << "|" << std::setw(12) << inf << "|" 
              << std::setw(12) << dead << "|" << std::setw(12) << heal << "|" << std::setw(12) << rec << "|" 
              << std::setw(12) << newsusc << "|" << std::setw(12) << beta << "|" 
              << std::setw(12) << gamma << "|" << std::setw(12) << healindex << "|" 
              << std::setw(12) << vaxindex << "|" << std::setw(12) << pop <<"|\n";
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
    Contagion(PandemicData& initial_state, int id, int ps, int vs, int vm, char p) : newstate{initial_state}, ImmDur{id}, PanStart{ps}, 
                                                                                     VaxStart{vs}, VaxMax{vm}, Previous {p}{}

    std::vector<PandemicData> generate_data(int Duration_) {
        //int Const = std::round(25 * tan(M_PI * (newstate.HealIndex - 0.5)));
        int hd = std::round (50 * exp( -2.0 * newstate.Beta ) + 30); //giorno di aumento dell'indice di guarigione
        std::vector<PandemicData> result{newstate};
        PandemicData state = result.back();

        for (int i = 0; i < Duration_; ++i) {
            int Pop_ = newstate.Susc + newstate.Inf + newstate.Dead + newstate.Heal;
            int NewRec = std::round(newstate.Gamma * state.Inf);
            int NewInf = std::round(newstate.Beta / Pop_ * state.Susc * state.Inf);
            int NewHeal = std::round(NewRec * newstate.HealIndex);  // l è la gente che guarisce.

            if ( Previous == 'Y' || Previous == 'y' ) {           // se la pandemia è già in corso
                if (i > hd - PanStart) {  // si può modificare. Forse mettere fuori come int
                    // deve essere inv prop a beta
                    //state.HealIndex = ((atan((i + Const) / 50)) / M_PI) + 0.5;
                    int eY =  ((i - hd + PanStart));
                    double exponentialY = std::exp(-eY/260.0);
                    state.HealIndex = (( 1 - result[0].HealIndex ) * ( 1 - exponentialY) + result[0].HealIndex );
                } else {
                    state.HealIndex = newstate.HealIndex;
                }
            } else if ( Previous == 'N' || Previous == 'n' ) {
                //state.HealIndex = ((atan((i + Const) / 50)) / M_PI) + 0.5;
                if (i > hd) {  // si può modificare. Forse mettere fuori come int
                    // deve essere inv prop a beta
                    //state.HealIndex = ((atan((i + Const) / 50)) / M_PI) + 0.5;
                    int eN =  ((i - hd));
                    double exponentialN = std::exp(-eN/260.0);
                    state.HealIndex = (( 1 - result[0].HealIndex ) * ( 1 - exponentialN) + result[0].HealIndex );
                } else {
                    state.HealIndex = newstate.HealIndex;
                }
            };

            // da inizializzare fuori per farlo inserire all'utente
            if (i > ImmDur) {  // il giorno 1 erano 0 i guariti, perciò sarebbe inutile
                int j = i - ImmDur;
                newstate.NewSusc = result[j].Heal - result[j - 1].Heal + result[j].NewSusc;  // diventa state.h
            }

            int NewVax_ = 0;
            if (state.Inf > Pop_ * 0.001) {
                if (VaxStart <= i && VaxStart + VaxMax > i) {
                    NewVax_ = (state.Susc + newstate.NewSusc - NewInf) * newstate.VaxIndex * ((i - VaxStart + 1) / VaxMax);
                } else if (VaxStart + VaxMax <= i) {
                    NewVax_ = (state.Susc + newstate.NewSusc - NewVax_) * newstate.VaxIndex;
                }
            } else {
                NewVax_ = 0;
            }

            state.Susc += newstate.NewSusc - NewInf - NewVax_;
            state.Inf += NewInf - NewRec;
            state.Rec += NewRec + NewVax_ - newstate.NewSusc;  // via. è da eliminare.
            state.Dead += NewRec - NewHeal;         // l è una frazione di k, quindi sempre minore. Io (Stefano) so cosa intendo.
            state.Heal += NewHeal + NewVax_ - newstate.NewSusc;
            state.NewSusc = newstate.NewSusc;

            result.push_back(state); //vengono immagazzinati tutti i valori di state giorno per giorno
        }
        return result;
    }
};

#endif

//aggiungere giorni mancanti che fa il conto alla rovescia, utile per i doctest
//mettere le nascite