#include <SFML/Graphics.hpp>
#include <iostream>

#include "cell.hpp"
#include "graphics.hpp"
#include "grid.hpp"
#include "validate_input.hpp"

int main() {
  int side = valid_side();
  Grid my_grid{side};
  std::cout << "The grid has a total of " << side * side << " cells" << '\n';
  int s = valid_s();
  int i = valid_i();
  valid_SIR(s, i, side);
  my_grid.fill(s, i);

  std::cout << "Initial number of S: " << my_grid.count_s() << '\n';
  std::cout << "Initial number of I: " << my_grid.count_i() << '\n';
  std::cout << "Initial number of R: " << my_grid.count_r() << '\n';
  std::cout << "Initial number of Void: " << my_grid.count_voids() << '\n';

  // display the evolution of the epidemic with days and param chosen by user
  double beta = valid_beta();
  double gamma = valid_gamma();
  valid_R0(beta, gamma);
  int days = valid_days();

  // Initialize SFML
  sf::RenderWindow window(sf::VideoMode(800, 600), "Epidemic Simulation");
  Graph graphic_part(window);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    window.clear(sf::Color::Black);
    graphic_part.draw_grid(my_grid);
    window.display();
    sf::sleep(sf::seconds(1.5));

    for (int i{}; i < days; ++i) {
      Grid new_grid = my_grid.evolution(beta, gamma);
      my_grid = new_grid;

      window.clear(sf::Color::Black);

      // draw the updated grid
      graphic_part.draw_grid(new_grid);
      window.display();
      sf::sleep(sf::seconds(1.5));

      std::cout << "day: " << i + 1 << '\n';
      std::cout << "Number of S: " << new_grid.count_s() << '\n';
      std::cout << "Number of I: " << new_grid.count_i() << '\n';
      std::cout << "Number of R: " << new_grid.count_r() << '\n';
      std::cout << "Number of Void: " << new_grid.count_voids() << '\n';
    }
  }
}
