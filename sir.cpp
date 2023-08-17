#include "sir.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include <stdexcept>

Status::Status(Param par, SIR sir, int days)
    : m_par{par}, m_sir{sir}, m_days{days} {};

bool Status::check_state() const {
  return (m_sir.s >= 0 && m_sir.i >= 0 && m_sir.i >= 0 && m_par.beta >= 0 &&
          m_par.beta <= 1 && m_par.gamma >= 0 && m_par.gamma <= 1);
}

int Status::total() const {
  double total{m_sir.s + m_sir.i + m_sir.r};
  assert(total == std::round(total));
  int int_total = static_cast<int>(total);
  return int_total;
};

int Status::get_s() const { return m_sir.s; };

int Status::get_i() const { return m_sir.i; };

int Status::get_r() const { return m_sir.r; };

void Status::evolve() {
  if (!check_state()) {
    throw std::runtime_error{"Invalid data"};
  }

  const int N = total();

  double s = m_sir.s - m_par.beta * (m_sir.s / N) * m_sir.i;
  double i = m_sir.i + m_par.beta * (m_sir.s / N) * m_sir.i - m_par.gamma * m_sir.i;
  double r = m_sir.r + m_par.gamma * m_sir.i;

  m_sir.s = std::round(s);
  m_sir.i = std::round(i);
  m_sir.r = std::round(r);

  double sum{m_sir.s + m_sir.i + m_sir.r};

  int int_sum = static_cast<int>(sum);

  int diff{std::abs(N - int_sum)};

  if (N > int_sum) {
    for (int i{}; i < diff; ++i) {
      ++m_sir.i;
    }
  } else if (N < int_sum) {
    for (int j{}; j < diff; ++j) {
      --m_sir.s;
    }
  } else {
  };

  int_sum = static_cast<int>(m_sir.s + m_sir.i + m_sir.r);
  assert(N == int_sum);
};