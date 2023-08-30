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

  /* return a modifiable reference to a cell */
  Cell& get_cell(int);

  /* return a const reference to a cell */
  Cell const& get_cell(int) const;

  /* count how many cells there are for each condition */
  int count_s() const;
  int count_i() const;
  int count_r() const;
  int count_voids() const;

  /* check if two numbers can be the coordinates for 
  an element of the vector considering it a 2D grid */
  bool valid_coord(int, int) const;

  /* fill the grid with a specified number of susceptibles and infected */
  void fill(int, int);

  /* count the number of infected neighbors for the cell in the position i-th */
  int inf_neigh(int) const;

  /* returns the grid with changed conditions of cells */
  Grid evolution(double, double);
};

double random_value();

#endif