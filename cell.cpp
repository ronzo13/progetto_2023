#include "cell.hpp"

Cell::Cell()
    : m_cond{Cond::Void} {};  // scelgo che di default una casella è vuota

Cell::Cell(Cond const& init_cond) : m_cond{init_cond} {}

Cond Cell::get_cond() const { return m_cond; }

Cond Cell::set_cond(Cond const& new_cond) {
  m_cond = new_cond;
  return new_cond;
}