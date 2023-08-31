#ifndef CELL_HPP
#define CELL_HPP

enum class Condition { Susceptible, Infectious, Removed, Void };

class Cell {
 private:
  Condition m_condition;

 public:
  /* create a cell giving it the Void condition by default*/
  Cell();

  /* create a cell giving it a condition different from Void */
  Cell(Condition const&);

  /*return the condition of a cell*/
  Condition get_condition() const;

  /*give a certain condition to a cell and return it*/
  Condition set_condition(Condition const&);
};

#endif