#include <vector>

#ifndef GRID_HPP
#define GRID_HPP

#include "cell.hpp"

class Grid {
 private:
  int m_side{};
  std::vector<Cell> m_cells;

 public:
  Grid(int);

  int get_side() const;

  Cell& get_cell(int);  // ritorna referenza modificabile ad una cella
  Cell const& get_cell(int) const;  // ritorna referenza costante a una cella

  int inf_neigh(Grid const&, int) const;

  double random_value() const;

  Grid evolution(Grid const&, double, double);

  int get_susc() const;
  int get_inf() const;
  int get_rem() const;
  int get_void() const;

  // aggiungere funzione che conti il numero di suscettibili, infetti e rimossi
};

#endif