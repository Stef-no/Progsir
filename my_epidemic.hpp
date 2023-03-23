#include <cmath>
#include <vector>
#include <cassert>

struct PandemicData {                      
    int Susc_, Inf_, Dead_, Heal_, Rec_, Imm_, VaxStart_, VaxMax_, NewSusc_;  
    double Beta_, Gamma_, HealIndex_, VaxIndex_;          
    char Previous_;                         // è se la pandemia è già in corso o se è all'inizio.
};

void control_print ( int day, int susc, int inf, int rec, int heal, int dead, double healindex, int pop ) {
    assert ( susc >= 0 && susc <= pop );
    assert ( inf >= 0 && inf <= pop );
    assert ( rec >= 0 && rec <= pop );
    assert ( heal >= 0 && heal <= rec );
    assert ( dead >= 0 && dead <= rec );
    assert ( healindex >= 0 && healindex <= 1 );
    assert ( pop == susc + inf + rec );
    assert ( rec == heal + dead);  
    assert ( day >= 0 );

    std::cout << std::setw(12) << day << "|" << std::setw(12) << susc << "|" << std::setw(12) << inf << "|" 
              << std::setw(12) << rec << "|" << std::setw(12) << heal << "|" << std::setw(12) << dead << "|"
              << std::setw(12) << healindex << "|" << std::setw(12) << pop <<"|\n";
}

class Contagion {
   private:
    PandemicData newstate;

   public:
    Contagion(PandemicData& initial_state) : newstate{initial_state} {}

    std::vector<PandemicData> generate_data(int Duration_) {
        int Const = std::round(25 * tan(M_PI * (newstate.HealIndex_ - 0.5)));
        std::vector<PandemicData> result{newstate};
        PandemicData state = result.back();

        for (int i = 0; i <= Duration_; ++i) {
            int Pop_ = newstate.Susc_ + newstate.Inf_ + newstate.Dead_ + newstate.Heal_;
            int NewRec_ = std::round(newstate.Gamma_ * state.Inf_);
            int NewInf_ = std::round(newstate.Beta_ / Pop_ * state.Susc_ * state.Inf_);
            int NewHeal_ = std::round(NewRec_ * newstate.HealIndex_);  // l è la gente che guarisce.

            if ( newstate.Previous_ == 's' ) {           // se la pandemia è già in corso
                if (i > (50 * pow(M_E, -2 * newstate.Beta_) + 30)) {  // si può modificare. Forse mettere fuori come int
                    // deve essere inv prop a beta
                    state.HealIndex_ = ((atan((i + Const) / 50)) / M_PI) + 0.5;
                } else {
                    state.HealIndex_ = newstate.HealIndex_;
                }
            } else {
                state.HealIndex_ = ((atan((i + Const) / 50)) / M_PI) + 0.5;
            };

            // da inizializzare fuori per farlo inserire all'utente
            if (i > newstate.Imm_) {  // il giorno 1 erano 0 i guariti, perciò sarebbe inutile
                int j = i - newstate.Imm_;
                newstate.NewSusc_ = result[j].Heal_ - result[j - 1].Heal_ + result[j].NewSusc_;  // diventa state.h
            }

            int NewVax_ = 0;
            if (state.Inf_ > Pop_ * 0.001) {
                if (newstate.VaxStart_ <= i && newstate.VaxStart_ + newstate.VaxMax_ > i) {
                    NewVax_ = (state.Susc_ + newstate.NewSusc_ - NewInf_) * newstate.VaxIndex_ * ((i - newstate.VaxStart_ + 1) / newstate.VaxMax_);
                } else if (newstate.VaxStart_ + newstate.VaxMax_ <= i) {
                    NewVax_ = (state.Susc_ + newstate.NewSusc_ - NewVax_) * newstate.VaxIndex_;
                }
            } else {
                NewVax_ = 0;
            }

            state.Susc_ += newstate.NewSusc_ - NewInf_ - NewVax_;
            state.Inf_ += NewInf_ - NewRec_;
            state.Rec_ += NewRec_ + NewVax_ - newstate.NewSusc_;  // via. è da eliminare.
            state.Dead_ += NewRec_ - NewHeal_;         // l è una frazione di k, quindi sempre minore. Io (Stefano) so cosa intendo.
            state.Heal_ += NewHeal_ + NewVax_ - newstate.NewSusc_;
            state.NewSusc_ = newstate.NewSusc_;

            result.push_back(state);
        }
        return result;
    }
};