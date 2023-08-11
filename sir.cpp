#include "sir.hpp"

#include <iostream>

SIR::SIR(int s, int i, int r, Param par)
    : m_s{s}, m_i{i}, m_r{r}, m_par{par} {};

int SIR::total() const {
  int total{m_s + m_i + m_r};
  return total;
};

int SIR::get_s() const { return m_s; };

int SIR::get_i() const { return m_i; };

int SIR::get_r() const { return m_r; };

void SIR::evolve() {
  int N = total();

  m_s = m_s - m_par.beta * (m_s / N) * m_i;
  m_i = m_i + m_par.beta * (m_s / N) * m_i - m_par.gamma * m_i;
  m_r = m_r + m_par.gamma * m_i;
};

int main() {
  SIR sir_{100, 2, 0, {0.5, 0.3}};
  SIR &sir = sir_;
  SIR evo(sir);
  int s = sir.get_s();
  int i = sir.get_i();
  int r = sir.get_r();
  std::cout << s << '\n';
  std::cout << i << '\n';
  std::cout << r << '\n';
}