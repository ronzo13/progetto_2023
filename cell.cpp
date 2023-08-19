#include "cell.hpp"

Cell::Cell() : m_state{State::Void} {}; //scelgo che di default una casella è vuota

Cell::Cell(State init_state) : m_state{init_state} {};

State Cell::get_state() const {
    return m_state;
}

void Cell::set_state(State new_state) {
    m_state = new_state;
}
