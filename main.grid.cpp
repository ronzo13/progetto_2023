#include <cassert>
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

  my_grid.fill(your_ps, your_pi);

  for (int i{0}; i < side; ++i) {
    std::cout << "\n";
    for (int j{0}; j < side; ++j) {
      int cell = i * side + j;
      if (my_grid.get_cell(cell).get_condition() == Condition::Susceptible) {
        std::cout << " S ";
      }
      if (my_grid.get_cell(cell).get_condition() == Condition::Infected) {
        std::cout << " I ";
      }
      if (my_grid.get_cell(cell).get_condition() == Condition::Removed) {
        std::cout << " R ";
      }
      if (my_grid.get_cell(cell).get_condition() == Condition::Void) {
        std::cout << " □ ";
      }
    }
  }
  int S = my_grid.count_s();
  int I = my_grid.count_i();
  int R = my_grid.count_r();
  int voids = side * side - (S + I + R);
  std::cout << "\n";
  std::cout << "Number of S: " << S << '\n';
  std::cout << "Number of I: " << I << '\n';
  std::cout << "Number of R: " << R << '\n';
  std::cout << "Number of Void: " << voids << '\n';

  Param param{0.4, 0.3};

  int days{10};
  for (int i{}; i < days; ++i) {
    std::cout << '\n';
    std::cout << "---------------------------";

    Grid new_grid = my_grid.evolution(param.beta, param.gamma);
    assert(my_grid.count_r() <= new_grid.count_r());
    my_grid = new_grid;

    for (int i{0}; i < side; ++i) {
      std::cout << "\n";
      for (int j{0}; j < side; ++j) {
        int cell = i * side + j;
        if (new_grid.get_cell(cell).get_condition() == Condition::Susceptible) {
          std::cout << " S ";
        }
        if (new_grid.get_cell(cell).get_condition() == Condition::Infected) {
          std::cout << " I ";
        }
        if (new_grid.get_cell(cell).get_condition() == Condition::Removed) {
          std::cout << " R ";
        }
        if (new_grid.get_cell(cell).get_condition() == Condition::Void) {
          std::cout << " □ ";
        }
      }
    }
    int S_ = new_grid.count_s();
    int I_ = new_grid.count_i();
    int R_ = new_grid.count_r();
    int voids = side * side - (S + I + R);
    std::cout << "\n";
    std::cout << "day: " << i + 1 << '\n';
    std::cout << "Number of S: " << S_ << '\n';
    std::cout << "Number of I: " << I_ << '\n';
    std::cout << "Number of R: " << R_ << '\n';
    std::cout << "Number of Void: " << voids << '\n';
  }
}
