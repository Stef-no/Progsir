#ifndef SIR_OPERATOR_HPP
#define SIR_OPERATOR_HPP

#include "sir_epidemic.hpp"
#include <vector>

inline bool operator==(const std::vector<epidemic::SirData> a,
                const std::vector<epidemic::SirData> b) {
  bool res = true;
  int i = 0;
  for (auto it = a.begin(), end = a.end(); it != end; it++) {
    if (it->Susc == b[i].Susc && it->Inf == b[i].Inf && it->Rec == b[i].Rec) {
      res = true;
    } else {
      return false;
    }
    i++;
  }
  return res;
}

#endif