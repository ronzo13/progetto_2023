#include "sir.hpp"

#include <iostream>

SIR::SIR(int s, int i, int r, Param par)
    : m_s{s}, m_i{i}, m_r{r}, m_par{par} {};

int SIR::total() const {
  int total{m_s + m_i + m_r};
  return total;
};

int SIR::get_s() const { return m_s; };

int SIR::get_s() const { return m_i; };

int SIR::get_r() const { return m_r; };

SIR SIR::evo(SIR &sir) const {
  int N = total();
  sir.m_s = sir.m_s - sir.m_par.beta * (sir.m_s / N) * sir.m_i;
  sir.m_i = sir.m_i + sir.m_par.beta * (sir.m_s / N) * sir.m_i -
            sir.m_par.gamma * sir.m_i;
  sir.m_r = sir.m_r + sir.m_par.gamma * sir.m_i;
  return {sir.m_s, sir.m_i, sir.m_r, sir.m_par};
};

int main() {
  SIR sir_{100, 0, 0, {0.3, 0.2}};
  SIR &sir = sir_;
  SIR evo(sir);
  int s{};
  s = get_s();
  std::cout < < < < '\n';
}