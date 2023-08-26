#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <SFML/Graphics.hpp>

class Graph{
    private:
    sf::RenderWindow& m_window;

    public:
    void draw(Grid const&){}
};

#endif