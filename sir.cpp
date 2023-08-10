#include "sir.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>

SIR::SIR(double s, double i, double r, Param par)
    : m_s{s}, m_i{i}, m_r{r}, m_par{par} {};

int SIR::total() const {
  double total{m_s + m_i + m_r};
  assert(total == round(total));
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

  m_s = round(m_s);
  m_i = round(m_i);
  m_r = round(m_r);

  double sum{m_s + m_i + m_r};

  if (N > sum) {
    ++m_i;
  } else if (N < sum) {
    --m_s;
  } else {
  };

  sum = m_s + m_i + m_r;
  sum = static_cast<int>(sum);
  assert(N == sum);
};

int main() {
  SIR sir{98, 2, 0, {0.4, 0.2}};
  int s = sir.get_s();
  int i = sir.get_i();
  int r = sir.get_r();
  std::cout << "totale: " << sir.total() << '\n';
  for (int j{}; j < 50; ++j) {
    sir.evolve();
    s = sir.get_s();
    i = sir.get_i();
    r = sir.get_r();
    std::cout << "s: " << s << '\n';
    std::cout << "i: " << i << '\n';
    std::cout << "r: " << r << '\n';
    std::cout << "totale: " << sir.total() << '\n';
  }
}