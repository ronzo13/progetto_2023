#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <SFML/Graphics.hpp>
#include "grid.hpp"

class Graph{
    private:
    sf::RenderWindow& m_window;

    public:
    void draw_grid(Grid const&);
};

#endif