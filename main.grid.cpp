#include <SFML/Graphics.hpp>
#include <cassert>
#include <iostream>
#include <random>

#include "cell.hpp"
#include "graphics.hpp"
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
  std::cout << "Percentage of susceptible people you want - between ]0; 1[: \n";
  std::cin >> s_percentage;
  std::cout << "Percentage of infected people you want - between ]0; 1[: \n";
  std::cin >> i_percentage;
  int s = s_percentage * side * side;
  int i = i_percentage * side * side;
  my_grid.fill(s, i);

  int S = my_grid.count_s();
  int I = my_grid.count_i();
  int R = my_grid.count_r();
  int voids = side * side - (S + I + R);
  std::cout << "\n";
  std::cout << "Initial number of S: " << S << '\n';
  std::cout << "Initial number of I: " << I << '\n';
  std::cout << "Initial number of R: " << R << '\n';
  std::cout << "Initial number of Void: " << voids << '\n';

  // display the evolution of the epidemic with days and param chosen by user
  Param param{};
  int days{};

  std::cout << "Insert how many days you want the epidemic lasts: \n";
  std::cin >> days;
  std::cout << "Insert beta and gamma parameters: \n";
  std::cin >> param.beta >> param.gamma;

  // Initialize SFML
  sf::RenderWindow window(sf::VideoMode(800, 600), "Epidemic Simulation");
  Graph graphic_part(window);

  bool finish_evolution = false;
  while (window.isOpen() && !finish_evolution) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear(sf::Color::White);

    graphic_part.draw_grid(my_grid);

    window.display();
    // display 5 seconds
    sf::sleep(sf::milliseconds(5000));
    
    for (int i{}; i < days; ++i) {
      Grid new_grid = my_grid.evolution(param.beta, param.gamma);
      assert(my_grid.count_r() <= new_grid.count_r());
      my_grid = new_grid;

      window.clear(sf::Color::White);

      // draw the updated grid
      graphic_part.draw_grid(new_grid);

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

      if (i == days - 1 || new_grid.count_r() == 0) {
        finish_evolution = true;
      }
    }
  }
  // comparing what would happen with the same values following
  // the implementation of the simulation of the first part
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
