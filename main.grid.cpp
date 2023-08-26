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

  double s_percentage;
  double i_percentage;
  std::cout << "Percentage of susceptible people you want - between ]0;1[: \n";
  std::cin >> s_percentage;
  std::cout << "Percentage of infected people you want - between ]0;1[: \n";
  std::cin >> i_percentage;
  int s = s_percentage * side * side;
  int i = i_percentage * side * side;
  my_grid.fill(s, i);
  /*
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
    */
  int S = my_grid.count_s();
  int I = my_grid.count_i();
  int R = my_grid.count_r();
  int voids = side * side - (S + I + R);
  std::cout << "\n";
  std::cout << "Number of S: " << S << '\n';
  std::cout << "Number of I: " << I << '\n';
  std::cout << "Number of R: " << R << '\n';
  std::cout << "Number of Void: " << voids << '\n';

  Param param{};
  int days{};

  std::cout << "Insert how many days you want the epidemic lasts: \n";
  std::cin >> days;
  std::cout << "Insert beta and gamma parameters: \n";
  std::cin >> param.beta >> param.gamma;

  for (int i{}; i < days; ++i) {
    std::cout << '\n';
    std::cout << "---------------------------";

    Grid new_grid = my_grid.evolution(param.beta, param.gamma);
    assert(my_grid.count_r() <= new_grid.count_r());
    my_grid = new_grid;
    /*
        for (int i{0}; i < side; ++i) {
          std::cout << "\n";
          for (int j{0}; j < side; ++j) {
            int cell = i * side + j;
            if (new_grid.get_cell(cell).get_condition() ==
       Condition::Susceptible) { std::cout << " S ";
            }
            if (new_grid.get_cell(cell).get_condition() == Condition::Infected)
       { std::cout << " I ";
            }
            if (new_grid.get_cell(cell).get_condition() == Condition::Removed) {
              std::cout << " R ";
            }
            if (new_grid.get_cell(cell).get_condition() == Condition::Void) {
              std::cout << " □ ";
            }
          }
        }
        */
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
  State state{s, i, 0};
  SIR sir{state, param};
  auto epidemic = sir.evolve(days);

  int size = epidemic.size();
  State last_state = epidemic.back();
  std::cout << "First part S: " << last_state.s << '\n';
  std::cout << "First part I: " << last_state.i << '\n';
  std::cout << "First part R: " << last_state.r << '\n';
  std::cout << "the epidemic lasts for: " << size - 1 << " days" << '\n';
}
