#ifndef CELL_HPP
#define CELL_HPP

enum class State { Susceptible, Infected, Removed, Void };

class Cell {
 private:
  State m_state{};

 public:
  Cell();
  Cell(State const&);

  State get_state() const;        // ritorna lo stato di una cella
  State set_state(State const&);  // assegna il nuovo stato a una cella
};

#endif