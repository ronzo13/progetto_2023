#ifndef GRID_HPP
#define GRID_HPP

#include <vector>

#include "cell.hpp"

class Grid {
 private:
  int m_side{};
  std::vector<Cell> m_cells;

 public:
  Grid(int);

  int get_side() const;

  Cell& get_cell(
      int);  // ritorna referenza modificabile ad una cella (suo stato)
  Cell const& get_cell(
      int) const;  // ritorna referenza costante a una cella (suo stato)

  int inf_neigh(Grid&) const;

  void evolution(Grid&, double, double);
};

#endif