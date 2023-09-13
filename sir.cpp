#include "sir.hpp"

#include <cassert>
#include <cmath>
#include <vector>

State::State(int n_s, int n_i, int n_r)
    : s{static_cast<double>(n_s)},
      i{static_cast<double>(n_i)},
      r{static_cast<double>(n_r)} {}

/* SIR constructor */
SIR::SIR(State const& state, Param const& par) : m_state{state}, m_par{par} {
  m_total = static_cast<int>(m_state.s + m_state.i + m_state.r);
}

/* public methods */
int SIR::get_total() const { return m_total; }

std::vector<State> SIR::evolve(int days) {
  std::vector<State> v_evo{m_state};

  int const N = get_total();

  for (int y{}; y < days; ++y) {
    /* reference to the last element */
    State const& prev_st = v_evo.back();

    assert(m_state.s >= 0);
    assert(m_state.i >= 0);
    assert(m_state.r >= 0);

    m_state.s = prev_st.s - m_par.beta * (prev_st.s / N) * prev_st.i;

    m_state.i = prev_st.i + m_par.beta * (prev_st.s / N) * prev_st.i -
                m_par.gamma * prev_st.i;

    m_state.r = prev_st.r + m_par.gamma * prev_st.i;

    m_state.s = std::round(m_state.s);
    m_state.i = std::round(m_state.i);
    m_state.r = std::round(m_state.r);

    double sum{m_state.s + m_state.i + m_state.r};

    int int_sum = static_cast<int>(sum);

    int diff{std::abs(N - int_sum)};

    if (N > int_sum) {
      for (int i{}; i < diff; ++i) {
        ++m_state.i;
      }
    } else if (N < int_sum) {
      for (int j{}; j < diff; ++j) {
        if (m_state.s > 0) {
          --m_state.s;
        } else if (m_state.i > 0) {
          --m_state.i;
        } else {
          --m_state.r;
        }
      }
    }

    int_sum = static_cast<int>(m_state.s + m_state.i + m_state.r);
    assert(N == int_sum);

    if (m_state == prev_st) {
      break;
    } else {
      /* add the new state at the end of the vector */
      v_evo.push_back(m_state);
    }
  }

  return v_evo;
}

bool operator==(State const& state, State const& prev_st) {
  return (state.s == prev_st.s) && (state.i == prev_st.i) &&
         (state.r == prev_st.r);
}