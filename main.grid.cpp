#include <SFML/Graphics.hpp>
#include <iostream>

#include "cell.hpp"
#include "graphics.hpp"
#include "grid.hpp"
#include "validate_input.hpp"

int main() {
  int side = valid_side();
  Grid my_grid{side};
  std::cout << "The grid has a total of " << side * side << " cells." << '\n';
  std::cout << "Therefore is the maximum number of people you can insert."
            << '\n';

  /* the sum of suscpetibles and infected cannot
  be bigger than the number of cells of the grid*/
  int s = valid_s();
  int i = valid_i();
  valid_SIR(s, i, side);
  my_grid.fill(s, i);

  std::cout << "Initial number of S: " << my_grid.count_s() << '\n';
  std::cout << "Initial number of I: " << my_grid.count_i() << '\n';
  std::cout << "Initial number of R: " << my_grid.count_r() << '\n';
  std::cout << "Initial number of Void: " << my_grid.count_voids() << '\n';

  /* display the evolution of the epidemic with days and param chosen by user */
  double beta = valid_beta();
  double gamma = valid_gamma();
  valid_R0(beta, gamma);
  int days = valid_days();

  /* Initialize SFML */
  sf::RenderWindow window(sf::VideoMode(800, 600), "Epidemic Simulation");
  Graph graphic_part(window);
  sf::Clock clock;

  if (window.isOpen()) {
    for (int i{}; i < days; ++i) {
      Grid new_grid = my_grid.evolution(beta, gamma);
      my_grid = new_grid;
      window.clear(sf::Color::Black);

      /* draw the updated grid */
      graphic_part.draw_grid(my_grid);
      window.display();

      std::cout << "day: " << i + 1 << '\n';
      std::cout << "Number of S: " << new_grid.count_s() << '\n';
      std::cout << "Number of I: " << new_grid.count_i() << '\n';
      std::cout << "Number of R: " << new_grid.count_r() << '\n';
      std::cout << "Number of Void: " << new_grid.count_voids() << '\n';

      while (clock.getElapsedTime().asSeconds() < 1.5) {
        /* wait for 2 seconds */
      }
      clock.restart();

      if (new_grid.count_i() == 0) {
        std::cout << "Since there are no more infectious the epidemic stops."
                  << '\n';
        break;
      }
    }
  }

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
  }
}