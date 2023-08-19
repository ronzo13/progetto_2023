#ifndef GRID_HPP
#define GRID_HPP

#include "cell.hpp"
#include <vector>

class Grid{
    private:
    int m_dim{};
    std::vector<Cell> cells;

    public:
    Grid(int);

    Grid evolve(Grid const&, )
}

#endif