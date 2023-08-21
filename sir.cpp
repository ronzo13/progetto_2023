#include "sir.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

SIR::SIR(int s, int i, int r, Param const& par)
    : m_s{static_cast<double>(s)},
      m_i{static_cast<double>(i)},
      m_r{static_cast<double>(r)},
      m_par{par} {
  if (!SIR::check_param()) {
    throw std::runtime_error{"Invalid parameters beta and gamma"};
  }
  m_total = static_cast<int>(m_s + m_i + m_r);
};

bool SIR::check_param() const {
  return m_par.beta >= 0 && m_par.beta <= 1 && m_par.gamma >= 0 &&
         m_par.gamma <= 1;
}

bool SIR::check_state() const { return (m_s >= 0 && m_i >= 0 && m_r >= 0); }

int SIR::get_total() const { return m_total; };

int SIR::get_s() const { return m_s; };

int SIR::get_i() const { return m_i; };

int SIR::get_r() const { return m_r; };

std::vector<SIR> SIR::evolve(int days) {
  if (!SIR::check_state()) {
    throw std::runtime_error{"Invalid data"};
  }

  /*in questo modo i valori assegnati all'oggetto sono uguali a quelli
   * dell'oggetto su cui viene chiamata la funzione (per via della
   * deferenziazione di this)
   *
   * meglio usare una refernce?
  uso di una copia come nel tuo codice originale offre una maggiore sicurezza
  contro tali modifiche accidentali
   */
  SIR state = *this;

  /*genera un vector contenente in ogni cella una dlle giornate in cui si è
   * sviluppata l'epidemia*/
  std::vector<SIR> v_evo{state};

  int const N = state.get_total();

  for (int y{}; y < days; ++y) {
    SIR const& prev_st = v_evo.back();  // referenza all'ultimo elemento

    state.m_s =
        prev_st.m_s - prev_st.m_par.beta * (prev_st.m_s / N) * prev_st.m_i;

    state.m_i = prev_st.m_i +
                prev_st.m_par.beta * (prev_st.m_s / N) * prev_st.m_i -
                prev_st.m_par.gamma * prev_st.m_i;

    state.m_r = prev_st.m_r + prev_st.m_par.gamma * prev_st.m_i;

    state.m_s = round(state.m_s);
    state.m_i = round(state.m_i);
    state.m_r = round(state.m_r);

    double sum{state.m_s + state.m_i + state.m_r};

    int int_sum = static_cast<int>(sum);

    int diff{std::abs(N - int_sum)};

    if (N > int_sum) {
      for (int i{}; i < diff; ++i) {
        ++state.m_i;
      }
    } else if (N < int_sum) {
      for (int j{}; j < diff; ++j) {
        --state.m_s;
      }
    } else {
    }

    int_sum = static_cast<int>(state.m_s + state.m_i + state.m_r);
    assert(N == int_sum);

    if (state == prev_st) {
      break;
    } else {
      v_evo.push_back(state);  // aggiunge il nuovo stato in fondo al vector
    }
  }

  return v_evo;
};

bool operator==(SIR const& state, SIR const& prev_st) {
  return (state.get_s() == prev_st.get_s()) &&
         (state.get_i() == prev_st.get_i()) &&
         (state.get_r() == prev_st.get_r());
};