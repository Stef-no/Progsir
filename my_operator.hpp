#ifndef MY_OPERATOR_HPP
#define MY_OPERATOR_HPP

#include "my_epidemic.hpp"

#include <vector>

inline bool operator==(const std::vector<epidemic::PandemicData> a,
                       const std::vector<epidemic::PandemicData> b) {
  bool res = true;
  int i = 0;
  for (auto it = a.begin(), end = a.end(); it != end; it++) {
    if (it->EpidemicPop.Susc == b[i].EpidemicPop.Susc && it->EpidemicPop.Inf == b[i].EpidemicPop.Inf && it->EpidemicPop.Dead == b[i].EpidemicPop.Dead &&
        it->EpidemicPop.Heal == b[i].EpidemicPop.Heal && it->EpidemicPop.Rec == b[i].EpidemicPop.Rec &&
        it->EpidemicPop.NewSusc == b[i].EpidemicPop.NewSusc && it->EpidemicIndex.Beta == b[i].EpidemicIndex.Beta &&
        it->EpidemicIndex.Gamma == b[i].EpidemicIndex.Gamma && it->EpidemicIndex.DeadIndex == b[i].EpidemicIndex.DeadIndex) {
      res = true;
    } else {
      return false;
    }
    i++;
  }
  return res;
}

#endif