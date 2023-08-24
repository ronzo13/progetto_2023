#ifndef CELL_HPP
#define CELL_HPP

enum class Condition { Susceptible, Infected, Removed, Void };

using Cond = Condition;

class Cell {
 private:
  Cond m_cond;

 public:
  Cell();
  Cell(Cond const&);

  Cond get_cond() const;       // ritorna lo stato di una cella
  Cond set_cond(Cond const&);  // assegna il nuovo stato a una cella
};

#endif