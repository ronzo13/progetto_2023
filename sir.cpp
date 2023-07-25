#include "sir.hpp"

int SIR::evo_s(int &s_, int &i_, double &beta) {
  const int N{sum()};
  s_ = s_ - beta * (s_ / N) * i_;
  return s_;
};

int SIR::evo_i(){};

int SIR::evo_r(){};
