#include "cell.hpp"

Cell::Cell()
    : m_state{State::Void} {};  // scelgo che di default una casella è vuota

Cell::Cell(State const& init_state) : m_state{init_state} {}

State Cell::get_state() const { return m_state; }

State Cell::set_state(State const& new_state) {
  m_state = new_state;
  return new_state;
}