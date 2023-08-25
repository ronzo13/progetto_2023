#ifndef CELL_HPP
#define CELL_HPP

enum class Condition { Susceptible, Infected, Removed, Void };

class Cell {
 private:
  Condition m_condition;

 public:
  Cell();
  Cell(Condition const&);

  Condition get_condition() const;       // ritorna lo stato di una cella
  Condition set_condition(Condition const&);  // assegna il nuovo stato a una cella
};

#endif