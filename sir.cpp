#include "sir.hpp"

#include <iostream>

SIR::SIR(int s, int i, int r) : s_{s}, i_{i}, r_{r} {}

Evolve::Evolve(SIR &sir) : sir_{sir} {};
