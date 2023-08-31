#include "graphics.hpp"

#include <SFML/Graphics.hpp>

#include "grid.hpp"

Graph::Graph(sf::RenderWindow& window) : m_window{window} {}

void Graph::draw_grid(Grid const& grid) {
  int side = grid.get_side();
  float const cell_base = 800.0f / side;
  float const cell_height = 600.0f / side;
  sf::RectangleShape cell(sf::Vector2f(cell_base, cell_height));
  cell.setOutlineThickness(1.f);

  for (int row{0}; row < side; ++row) {
    for (int col{0}; col < side; ++col) {
      int index = row * side + col;

      // Set the position of the cell shape based on row and col
      cell.setPosition(row * cell_base, col * cell_height);

      // Determine the color based on the cell's condition
      Condition person = grid.get_cell(index).get_condition();
      switch (person) {
        case Condition::Susceptible: {
          cell.setFillColor(sf::Color::Green);
        } break;
        case Condition::Infectious: {
          cell.setFillColor(sf::Color::Red);
        } break;
        case Condition::Removed: {
          cell.setFillColor(sf::Color::Blue);
        } break;
        case Condition::Void: {
          cell.setFillColor(sf::Color::White);
        } break;
      }
      m_window.draw(cell);
    }
  }
}