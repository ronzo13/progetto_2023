#include <vector>

#include "cell.hpp"

#ifndef GRID_HPP
#define GRID_HPP

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

  int count_s() const;
  int count_i() const;
  int count_r() const;
};

#endif