#ifndef MY_OPERATOR_HPP
#define MY_OPERATOR_HPP

#include "my_epidemic.hpp"

inline bool operator==(const std::vector<epidemic::PandemicData> a,
                       const std::vector<epidemic::PandemicData> b) {
  bool res = true;
  int i = 0;
  for (auto it = a.begin(), end = a.end(); it != end; it++) {
    if (it->Susc == b[i].Susc && it->Inf == b[i].Inf && it->Dead == b[i].Dead &&
        it->Heal == b[i].Heal && it->Rec == b[i].Rec &&
        it->NewSusc == b[i].NewSusc && it->Beta == b[i].Beta &&
        it->Gamma == b[i].Gamma && it->DeadIndex == b[i].DeadIndex &&
        it->VaxIndex == b[i].VaxIndex) {
      res = true;
    } else {
      return false;
    }
    i++;
  }
  return res;
}

#endif