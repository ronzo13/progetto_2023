#include "sir.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>
#include <stdexcept>

SIR::SIR(double s, double i, double r, Param par)
    : m_s{s}, m_i{i}, m_r{r}, m_par{par} {};

bool SIR::check_state() const{
  return (m_s >= 0 && m_i >=0 && m_r >= 0 && m_par.beta >= 0 && m_par.beta <= 1 && m_par.gamma >= 0 && m_par.gamma <= 1);
}

int SIR::total() const {
  double total{m_s + m_i + m_r};
  assert(total == round(total));
  int int_total = static_cast<int>(total);
  return int_total;
};

int SIR::get_s() const { return m_s; };

int SIR::get_i() const { return m_i; };

int SIR::get_r() const { return m_r; };

void SIR::evolve() {
  const int N = total();
  
  if(!SIR::check_state()){
    throw std::runtime_error{"Invalid data"};
  }

  double s = m_s - m_par.beta * (m_s / N) * m_i;
  double i = m_i + m_par.beta * (m_s / N) * m_i - m_par.gamma * m_i;
  double r = m_r + m_par.gamma * m_i;

  m_s = round(s);
  m_i = round(i);
  m_r = round(r);

  double sum{m_s + m_i + m_r};

  int int_sum = static_cast<int>(sum);

  int diff{std::abs(N - int_sum)};

  if (N > int_sum) {
    for (int i{}; i < diff; ++i) {
      ++m_i;
    }
  } else if (N < int_sum) {
    for (int j{}; j < diff; ++j) {
      --m_s;
    }
  } else {
  };

  int_sum = static_cast<int>(m_s + m_i + m_r);
  assert(N == int_sum);
};

int main() {
  SIR sir{95, 5, 0, {0.6, 0.3}};
  int s = sir.get_s();
  int i = sir.get_i();
  int r = sir.get_r();
  std::cout << "totale: " << sir.total() << '\n';
  for (int j{}; j < 10; ++j) {
    sir.evolve();
    s = sir.get_s();
    i = sir.get_i();
    r = sir.get_r();
    std::cout << "s: " << s << '\n';
    std::cout << "i: " << i << '\n';
    std::cout << "r: " << r << '\n';
    std::cout << "totale: " << sir.total() << '\n';
    std::cout << "------" << '\n';
  }
}
