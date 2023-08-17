#include "sir.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include <stdexcept>

SIR::SIR(double s, double i, double r, Param par)
    : m_s{s}, m_i{i}, m_r{r}, m_par{par} {
  if (!SIR::check_param()) {
    throw std::runtime_error{"Invalid parameters beta and gamma"};
  }
};

bool SIR::check_param() const {
  return (m_par.beta >= 0 && m_par.beta <= 1 && m_par.gamma >= 0 &&
          m_par.gamma <= 1);
}

bool SIR::check_state() const { return (m_s >= 0 && m_i >= 0 && m_r >= 0); }

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
  if (!SIR::check_state()) {
    throw std::runtime_error{"Unacceptable S, I or R"};
  }

  const int N = total();

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
  int durata{};
  std::cout << "durata epidemia: ";
  std::cin >> durata;
  SIR sir{93, 7, 0, {0.7, 0.2}};
  int s = sir.get_s();
  int i = sir.get_i();
  int r = sir.get_r();
  std::cout << "totale: " << sir.total() << '\n';
  std::cout << "------" << '\n';
  for (int j{}; j < durata; ++j) {
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
