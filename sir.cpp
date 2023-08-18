#include "sir.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include <stdexcept>

SIR::SIR(double s, double i, double r, Param const& par)
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
  assert(total == std::round(total));
  int int_total = static_cast<int>(total);
  return int_total;
};

int SIR::get_s() const { return m_s; };

int SIR::get_i() const { return m_i; };

int SIR::get_r() const { return m_r; };

void SIR::evolve() {
  if (!SIR::check_state()) {
    throw std::runtime_error{"Invalid data"};
  }

  const int N = SIR::total();

  double s = m_s - m_par.beta * (m_s / N) * m_i;
  double i = m_i + m_par.beta * (m_s / N) * m_i - m_par.gamma * m_i;
  double r = m_r + m_par.gamma * m_i;

  m_s = std::round(s);
  m_i = std::round(i);
  m_r = std::round(r);

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