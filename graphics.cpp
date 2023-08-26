#include <SFML/Graphics.hpp>
#include "graphics.hpp"

Graph::Graph(sf::RenderWindow& window) : m_window{window};

void Graph::draw_grid(Grid const& grid){
    int side = grid.get_side();
    float const cell_base = 800 / side;
    float const cell_height = 600 / side;
    sf::RectangleShape cell(sf::Vector2f(cell_base, cell_height));
    
    for (int row{0}; row < side; ++row) {
        for (int col{0}; col < gridSize; ++col) {
            int index = row * side + col;

            // Set the position of the cell shape based on row and col
            cell.setPosition(row * cell_base, col * cell_height);

            // Determine the color based on the cell's condition
            Condition person = get_cell(index).get_condition();
            switch (person) {
                case Condition::Susceptible: {
                    cell.setFillColor(sf::Color::Green);
                } break;
                case Condition::Infected: {
                    cell.setFillColor(sf::Color::Red);
                } break;
                case Condition::Removed: {
                    cell.setFillColor(sf:Color::Blue);
                } break;
                case Condition::Void: {
                    cell.setFillColor(sf::Color::White);
                } break;
            }
            window.draw(cell);
        }
    }
}