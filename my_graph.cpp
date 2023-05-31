#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <cmath>
#include <iostream>
#include <vector>

#include "my_epidemic.hpp"

int main() {
  std::cout << "Nell'inserimento dei dati della pandemia si richiede di "
               "seguire le seguenti indicazioni: \n";
  std::cout << "- i dati temporali e riguardanti la popolazione sono numeri "
               "interi e positivi; \n";
  std::cout << "- gli indici sono numeri decimali compresi tra 0 e 1 (estremi "
               "inclusi). \n";

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

  char bVar_;
  std::cout << "Beta varia?\t";
  std::cin >> bVar_;
  while (bVar_ != 'N' && bVar_ != 'Y' && bVar_ != 'n' && bVar_ != 'y') {
    std::cout << " Beta variation has to be Y/n.\n ";
    std::cin >> bVar_;
  }

  int bVarTime_ = 0;
  int bVarStart_ = 0;

  if (bVar_ == 'Y' || bVar_ == 'y') {
    std::cout << "Giorno di inizio della diminuzione di beta:\t";
    std::cin >> bVarStart_;
    while (bVarStart_ < 0) {
      std::cout << " bVarStart has to be > than 0.\n ";
      std::cin >> bVarStart_;
    }

    std::cout << "Quando vale il tempo di dimezzamento dell'indice di "
                 "contagione? \t";
    std::cin >> bVarTime_;
    while (bVarTime_ < 0) {
      std::cout << "bVarTime has to be > 0.\n ";
      std::cin >> bVarTime_;
    }
  }

  double Gamma_;
  std::cout << "Indice di rimozione:\t";
  std::cin >> Gamma_;
  while (Gamma_ < 0 || Gamma_ > 1) {
    std::cout << " Gamma's value has to be between 0 and 1.\n ";
    std::cin >> Gamma_;
  }

  char gVar_;
  std::cout << "Gamma varia?\t";
  std::cin >> gVar_;
  while (gVar_ != 'N' && gVar_ != 'Y' && gVar_ != 'n' && gVar_ != 'y') {
    std::cout << " Gamma variation has to be Y/n.\n ";
    std::cin >> gVar_;
  }

  int gVarStart_ = 0;
  int gVarTime_ = 0;

  if (gVar_ == 'Y' || gVar_ == 'y') {
    std::cout << "Giorno di inizio della variazione di gamma:\t";
    std::cin >> gVarStart_;
    while (gVarStart_ < 0) {
      std::cout << " gVarStart has to be > than 0.\n ";
      std::cin >> gVarStart_;
    }

    std::cout << "Quando vale il tempo di dimezzamento dell'indice di NON"
                 "rimozione? \t";
    std::cin >> gVarTime_;
    while (gVarTime_ < 0) {
      std::cout << "gVarTime has to be > 0.\n ";
      std::cin >> gVarTime_;
    }
  }

  double DeadIndex_;
  std::cout << "Indice di mortalità:\t";
  std::cin >> DeadIndex_;
  while (DeadIndex_ < 0 || DeadIndex_ > 1) {
    std::cout << " DeadIndex's value has to be between 0 and 1.\n ";
    std::cin >> DeadIndex_;
  }

  char DIVar_;
  std::cout << "La mortalità varia?\t";
  std::cin >> DIVar_;
  while (DIVar_ != 'N' && DIVar_ != 'Y' && DIVar_ != 'n' && DIVar_ != 'y') {
    std::cout << " Mortality variation has to be Y/n.\n ";
    std::cin >> DIVar_;
  }

  int DIVarTime_ = 0;
  int DIVarStart_ = 0;

  if (DIVar_ == 'Y' || DIVar_ == 'y') {
    std::cout << "Giorno di inizio della variazione della mortalità:\t";
    std::cin >> DIVarStart_;
    while (DIVarStart_ < 0) {
      std::cout << " Il giorno di inizio della variazione della mortalità has "
                   "to be > than 0.\n ";
      std::cin >> DIVarStart_;
    }

    std::cout << "Quando vale il tempo di dimezzamento dell'indice di "
                 "mortalità? \t";
    std::cin >> DIVarTime_;
    while (DIVarTime_ < 0) {
      std::cout << "DIVarTime has to be > 0.\n ";
      std::cin >> DIVarTime_;
    }
  }

  char Vax_;
  std::cout << "Ci sono i vaccini?\t";
  std::cin >> Vax_;
  while (Vax_ != 'N' && Vax_ != 'Y' && Vax_ != 'n' && Vax_ != 'y') {
    std::cout << " Vax has to be Y/n.\n ";
    std::cin >> Vax_;
  }

  double VaxIndex_ = 0;
  int VaxStart_ = 0;
  int VaxMax_ = 0;

  if (Vax_ == 'Y' || Vax_ == 'y') {
    std::cout << "Indice di vaccinazione:\t";
    std::cin >> VaxIndex_;
    while (VaxIndex_ < 0 || VaxIndex_ > 1) {
      std::cout << " VaxIndex's value has to be between 0 and 1.\n ";
      std::cin >> VaxIndex_;
    }

    std::cout << "Giorno di inizio dei vaccini:\t";
    std::cin >> VaxStart_;
    while (VaxStart_ < 0) {
      std::cout << " VaxStart has to be > than 0.\n ";
      std::cin >> VaxStart_;
    }

    std::cout << "Giorni per raggiungere la massima velocità percentuale di "
                 "vaccinazione :\t";
    std::cin >> VaxMax_;
    while (VaxMax_ < 0) {
      std::cout << " VaxMax has to be > than 0.\n ";
      std::cin >> VaxMax_;
    }
  }

  int Duration_;
  std::cout << "Durata simulazione:\t";
  std::cin >> Duration_;
  while (Duration_ <= 0) {
    std::cout << " Duration has to be > than 0.\n ";
    std::cin >> Duration_;
  }

  int ImmDur_;
  std::cout << "Durata immunità:\t";
  std::cin >> ImmDur_;
  while (ImmDur_ <= 0) {
    std::cout << " Imm has to be > than 0.\n ";
    std::cin >> ImmDur_;
  }

  char Previous_;
  std::cout << "La pandemia è già in corso?\t";
  std::cin >> Previous_;
  while (Previous_ != 'N' && Previous_ != 'Y' && Previous_ != 'n' &&
         Previous_ != 'y') {
    std::cout << " Previous has to be Y/n.\n ";
    std::cin >> Previous_;
  }

  int PanStart_;
  if (Previous_ == 'Y' || Previous_ == 'y') {
    std::cout << " Da quanti giorni? \t";
    std::cin >> PanStart_;
    while (PanStart_ < 0) {
      std::cout << " PanStart has to be major than 0.\n ";
      std::cin >> PanStart_;
    }
  } else {
    PanStart_ = 0;
  }

  int Dead_;
  if (Previous_ == 'Y' || Previous_ == 'y') {
    std::cout << " Dead: \t";
    std::cin >> Dead_;
    while (Dead_ < 0 || Dead_ > Pop_ - Inf_) {
      std::cout << " Dead has to be between 0 and Pop - Inf.\n ";
      std::cin >> Dead_;
    }
  } else {
    Dead_ = 0;
  }

  int Heal_;
  if (Previous_ == 'Y' || Previous_ == 'y') {
    std::cout << " Heal: \t";
    std::cin >> Heal_;
    while (Heal_ < 0 || Heal_ > Pop_ - Inf_ - Dead_) {
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
  while (View_ != 'N' && View_ != 'Y' && View_ != 'n' && View_ != 'y') {
    std::cout << " View has to be Y/n.\n ";
    std::cin >> View_;
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
  Contagion graph{initial_state, DIVar_,     DIVarStart_, DIVarTime_,
                     ImmDur_,       bVar_,      bVarStart_,  bVarTime_,
                     gVar_,         gVarStart_, gVarTime_,   PanStart_,
                     VaxStart_,     VaxMax_,    Previous_};


    std::vector<PandemicData> data = graph.generate_data(Duration_);
    sf::RenderWindow window(sf::VideoMode(1200, 675), "Grafico");

    while (window.isOpen()) {
        sf::Event event;

        sf::VertexArray InfGraph_(sf::LinesStrip, Duration_);
        sf::VertexArray DeadGraph_(sf::LinesStrip, Duration_);
        sf::VertexArray SuscGraph_(sf::LinesStrip, Duration_);
        sf::VertexArray HealGraph_(sf::LinesStrip, Duration_);

        sf::RectangleShape censure(sf::Vector2f(window.getSize().x / 32, window.getSize().y));
        sf::RectangleShape s(sf::Vector2f(window.getSize().x / 8, window.getSize().y / 18));
        s.setPosition(sf::Vector2f(7 * window.getSize().x / 8, 0));
        s.setOutlineThickness(1);
        s.setOutlineColor(sf::Color::Black);

        sf::RectangleShape graphx(sf::Vector2f(399 * window.getSize().x / 400, 2));
        graphx.setPosition(sf::Vector2f(window.getSize().x / 800, 17 * window.getSize().y / 18));
        graphx.setFillColor(sf::Color::Black);
        sf::RectangleShape graphy(sf::Vector2f(224 * window.getSize().y / 225, 2));
        graphy.rotate(90);
        graphy.setPosition(sf::Vector2f(window.getSize().x / 32, window.getSize().y / 450));
        graphy.setFillColor(sf::Color::Black);

        sf::CircleShape triangle1(window.getSize().x / 120, 3);
        triangle1.setPosition(sf::Vector2f(window.getSize().x, 67 * window.getSize().y / 72));
        triangle1.setFillColor(sf::Color::Black);
        triangle1.rotate(90);
        sf::CircleShape triangle2(10, 3);
        triangle2.setPosition(sf::Vector2f(11 * window.getSize().x / 512, 0));
        triangle2.setFillColor(sf::Color::Black);

        int K = 8;
        sf::VertexArray liney(sf::Lines, K * 2);
        for (int j = 0; j < K; j++) {
            double x1 = 3 * window.getSize().x / 128;
            double x2 = 5 * window.getSize().x / 128;
            double y = (15 - 2 * j) * window.getSize().y / 18;
            liney.append(sf::Vertex(sf::Vector2f(x1, y), sf::Color::Black));
            liney.append(sf::Vertex(sf::Vector2f(x2, y), sf::Color::Black));
        }

        int Z = 15;
        sf::VertexArray linex(sf::Lines, Z * 2);
        for (int j = 0; j < Z; j++) {
            double x = (3 + 2 * j) * window.getSize().x / 32;
            double y1 = 277 * window.getSize().y / 288;
            double y2 = 269 * window.getSize().y / 288;
            linex.append(sf::Vertex(sf::Vector2f(x, y1), sf::Color::Black));
            linex.append(sf::Vertex(sf::Vector2f(x, y2), sf::Color::Black));
        }

        for (int i = 0; i < Duration_ - 1; i++) {
            int x = (window.getSize().x / 32) + (15 * i * window.getSize().x / (16 * Duration_));
            int y = (17 * window.getSize().y / 18) - (8 * data[i].Inf * window.getSize().y / (9 * Pop_));
            InfGraph_.append(sf::Vertex(sf::Vector2f(x, y), sf::Color::Red));

            x = (window.getSize().x / 32) + (15 * i * window.getSize().x / (16 * Duration_));
            y = (17 * window.getSize().y / 18) - (8 * data[i].Dead * window.getSize().y / (9 * Pop_));
            DeadGraph_.append(sf::Vertex(sf::Vector2f(x, y), sf::Color::Black));

            x = (window.getSize().x / 32) + (15 * i * window.getSize().x / (16 * Duration_));
            y = (17 * window.getSize().y / 18) - (8 * data[i].Susc * window.getSize().y / (9 * Pop_));
            SuscGraph_.append(sf::Vertex(sf::Vector2f(x, y), sf::Color::Yellow));

            x = (window.getSize().x / 32) + (15 * i * window.getSize().x / (16 * Duration_));
            y = (17 * window.getSize().y / 18) - (8 * data[i].Heal * window.getSize().y / (9 * Pop_));
            HealGraph_.append(sf::Vertex(sf::Vector2f(x, y), sf::Color::Green));

            int tmpy = InfGraph_[0].position.y;
            int py = DeadGraph_[0].position.y;
            int p = SuscGraph_[0].position.y;
            int io = HealGraph_[0].position.y;

            InfGraph_[i].position.y = InfGraph_[i + 1].position.y;
            InfGraph_[Duration_ - 1].position.y = tmpy;

            DeadGraph_[i].position.y = InfGraph_[i + 1].position.y;
            DeadGraph_[Duration_ - 1].position.y = py;

            SuscGraph_[i].position.y = InfGraph_[i + 1].position.y;
            SuscGraph_[Duration_ - 1].position.y = p;

            HealGraph_[i].position.y = InfGraph_[i + 1].position.y;
            HealGraph_[Duration_ - 1].position.y = io;

            window.clear(sf::Color::White);
            window.draw(s);
            window.draw(InfGraph_);
            window.draw(DeadGraph_);
            window.draw(SuscGraph_);
            window.draw(HealGraph_);
            window.draw(censure);
            window.draw(graphx);
            window.draw(graphy);
            window.draw(linex);
            window.draw(liney);
            window.draw(triangle1);
            window.draw(triangle2);
            window.display();

            if (i == Duration_ - 1) {
                break;
            }

            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
            }
        }
    }

    return 0;
}