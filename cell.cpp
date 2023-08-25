#include "cell.hpp"

Cell::Cell()
    : m_condition{Condition::Void} {};  // scelgo che di default una casella è vuota

Cell::Cell(Condition const& init_condition) : m_condition{init_condition} {}

Condition Cell::get_condition() const { return m_condition; }

Condition Cell::set_condition(Condition const& new_condition) {
  m_condition = new_condition;
  return new_condition;
}