#include "cell.hpp"

/* constructors */
Cell::Cell() : m_condition{Condition::Void} {}

Cell::Cell(Condition const& init_condition) : m_condition{init_condition} {}

/* public methods */
Condition Cell::get_condition() const { return m_condition; }

Condition Cell::set_condition(Condition const& new_condition) {
  m_condition = new_condition;
  return new_condition;
}