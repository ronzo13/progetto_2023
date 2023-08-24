#include <iostream>
#include <random>

#include "cell.hpp"
#include "grid.hpp"
#include "sir.hpp"
#include "validate_input.hpp"

int main() {
  int side;
  std::cout << "Insert the side of the grid: \n";
  std::cin >> side;
  Grid my_grid{side};

  double your_ps;
  double your_pi;
  std::cout << "Percentage of susceptible people you want - between ]0;1[: \n";
  std::cin >> your_ps;
  std::cout << "Percentage of infected people you want - between ]0;1[: \n";
  std::cin >> your_pi;

  int n_s = side * side * your_ps;  // non metto static_cast<int> perchè con int
                                    // la conversione è forzata
  int n_i = side * side * your_pi;  // """"

  my_grid.fill(n_s, n_i, my_grid);

  for (int i{0}; i < side; ++i) {
    std::cout << "\n";
    for (int j{0}; j < side; ++j) {
      int cell = i * side + j;
      if (my_grid.get_cell(cell).get_cond() == Cond::Susceptible) {
        std::cout << " S ";
      }
      if (my_grid.get_cell(cell).get_cond() == Cond::Infected) {
        std::cout << " I ";
      }
      if (my_grid.get_cell(cell).get_cond() == Cond::Removed) {
        std::cout << " R ";
      }
      if (my_grid.get_cell(cell).get_cond() == Cond::Void) {
        std::cout << " □ ";
      }
    }
  }

  Param param{0.6, 0.3};

  int days{3};
  for (int i{}; i < days; ++i) {
    std::cout << '\n';
    std::cout << "---------------------------";
    Grid new_grid = my_grid;
    new_grid.evolution(my_grid, param.beta, param.gamma);
    for (int i{0}; i < side; ++i) {
      std::cout << "\n";
      for (int j{0}; j < side; ++j) {
        int cell = i * side + j;
        if (new_grid.get_cell(cell).get_cond() == Cond::Susceptible) {
          std::cout << " S ";
        }
        if (new_grid.get_cell(cell).get_cond() == Cond::Infected) {
          std::cout << " I ";
        }
        if (new_grid.get_cell(cell).get_cond() == Cond::Removed) {
          std::cout << " R ";
        }
        if (new_grid.get_cell(cell).get_cond() == Cond::Void) {
          std::cout << " □ ";
        }
      }
    }
  }
}
