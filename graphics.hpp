#include <SFML/Graphics.hpp>

#include "grid.hpp"

#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

class Graph {
 private:
  sf::RenderWindow& m_window;

 public:
  Graph(sf::RenderWindow&);

  void draw_grid(Grid const&);
};

#endif