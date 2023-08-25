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

  int count_s() const;
  int count_i() const;
  int count_r() const;

  bool valid_coord(int, int) const;

  void fill(int, int);

  int inf_neigh(int) const;

  Grid evolution(double, double);
};

double random_value();

#endif