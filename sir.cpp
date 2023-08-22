#include "sir.hpp"

#include <cassert>
#include <cmath>
#include <stdexcept>
#include <vector>

State::State(int n_s, int n_i, int n_r)
    : s{static_cast<double>(n_s)},
      i{static_cast<double>(n_i)},
      r{static_cast<double>(n_r)} {};

SIR::SIR(State const& state, Param const& par) : m_state{state}, m_par{par} {
  if (!SIR::check_param()) {
    throw std::runtime_error{"Invalid parameters beta and gamma"};
  }
  m_total = static_cast<int>(m_state.s + m_state.i + m_state.r);
};

bool SIR::check_param() const {
  return m_par.beta >= 0 && m_par.beta <= 1 && m_par.gamma >= 0 &&
         m_par.gamma <= 1;
}

bool SIR::check_state() const {
  return (m_state.s >= 0 && m_state.i >= 0 && m_state.r >= 0);
}

int SIR::get_total() const { return m_total; };

std::vector<State> SIR::evolve(int days) {
  if (!SIR::check_state()) {
    throw std::runtime_error{"Invalid data"};
  }

  std::vector<State> v_evo{m_state};

  int const N = get_total();

  for (int y{}; y < days; ++y) {
    State const& prev_st = v_evo.back();  // referenza all'ultimo elemento

    m_state.s = prev_st.s - m_par.beta * (prev_st.s / N) * prev_st.i;

    m_state.i = prev_st.i + m_par.beta * (prev_st.s / N) * prev_st.i -
                m_par.gamma * prev_st.i;

    m_state.r = prev_st.r + m_par.gamma * prev_st.i;

    m_state.s = round(m_state.s);
    m_state.i = round(m_state.i);
    m_state.r = round(m_state.r);

    double sum{m_state.s + m_state.i + m_state.r};

    int int_sum = static_cast<int>(sum);

    int diff{std::abs(N - int_sum)};

    if (N > int_sum) {
      for (int i{}; i < diff; ++i) {
        ++m_state.i;
      }
    } else if (N < int_sum) {
      for (int j{}; j < diff; ++j) {
        --m_state.s;
      }
    } else {
    }

    int_sum = static_cast<int>(m_state.s + m_state.i + m_state.r);
    assert(N == int_sum);

    if (m_state == prev_st) {
      break;
    } else {
      v_evo.push_back(m_state);  // aggiunge il nuovo stato in fondo al vector
    }
  }

  return v_evo;
};

bool operator==(State const& state, State const& prev_st) {
  return (state.s == prev_st.s) && (state.i == prev_st.i) &&
         (state.r == prev_st.r);
};