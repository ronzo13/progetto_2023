#include "grid.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>
#include <random>

#include "cell.hpp"

/* constructor */
Grid::Grid(int side) : m_side{side}, m_cells(side * side) {}

/* public methods */
int Grid::get_side() const { return m_side; }

Cell& Grid::get_cell(int cell_pos) {
  assert(cell_pos >= 0 && cell_pos < m_side * m_side);
  return m_cells[cell_pos];
}

Cell const& Grid::get_cell(int cell_pos) const {
  assert(cell_pos >= 0 && cell_pos < m_side * m_side);
  return m_cells[cell_pos];
}

int Grid::count_s() const {
  return std::accumulate(
      m_cells.begin(), m_cells.end(), 0, [](int sum, const Cell& cell) {
        return sum + (cell.get_condition() == Condition::Susceptible ? 1 : 0);
      });
}

int Grid::count_i() const {
  return std::accumulate(
      m_cells.begin(), m_cells.end(), 0, [](int sum, const Cell& cell) {
        return sum + (cell.get_condition() == Condition::Infectious ? 1 : 0);
      });
}

int Grid::count_r() const {
  return std::accumulate(
      m_cells.begin(), m_cells.end(), 0, [](int sum, const Cell& cell) {
        return sum + (cell.get_condition() == Condition::Removed ? 1 : 0);
      });
}

int Grid::count_voids() const {
  return std::accumulate(
      m_cells.begin(), m_cells.end(), 0, [](int sum, const Cell& cell) {
        return sum + (cell.get_condition() == Condition::Void ? 1 : 0);
      });
}

bool Grid::valid_coord(int row, int col) const {
  return row >= 0 && row < m_side && col >= 0 && col < m_side;
}

void Grid::fill(int s, int i) {
  std::fill(m_cells.begin(), m_cells.begin() + s, Condition::Susceptible);

  std::fill(m_cells.begin() + s, m_cells.begin() + s + i,
            Condition::Infectious);

  std::random_device rd;
  std::default_random_engine generator(rd());
  std::shuffle(m_cells.begin(), m_cells.end(), generator);
}

int Grid::inf_neigh(int cell_pos) const {
  int count{};
  int g_side = get_side();
  assert(cell_pos >= 0 && cell_pos < g_side * g_side);
  int row = cell_pos / g_side;
  int col = cell_pos % g_side;

  for (int i : {-1, 0, 1}) {
    for (int j : {-1, 0, 1}) {
      if (valid_coord(row + i, col + j) == true) {
        int index = (row + i) * g_side + (col + j);
        if (get_cell(index).get_condition() == Condition::Infectious) {
          ++count;
        }
      }
    }
  }

  if (get_cell(cell_pos).get_condition() == Condition::Infectious) {
    count -= 1;
  }

  return count;
}

Grid Grid::evolution(double beta, double gamma) {
  int const side = get_side();
  Grid next_grid{side};

  /* infection and removal rules */
  for (int j{}; j < side * side; ++j) {
    Condition init_condition = get_cell(j).get_condition();

    switch (init_condition) {
      case Condition::Susceptible: {
        double const prob_infection = 1.0 - std::pow(1.0 - beta, inf_neigh(j));
        assert(prob_infection >= 0 && prob_infection <= 1);
        if (random_value() < prob_infection) {
          next_grid.get_cell(j).set_condition(Condition::Infectious);
        } else {
          next_grid.get_cell(j).set_condition(Condition::Susceptible);
        }
      } break;
      case Condition::Infectious: {
        if (random_value() < gamma) {
          next_grid.get_cell(j).set_condition(Condition::Removed);
        } else {
          next_grid.get_cell(j).set_condition(Condition::Infectious);
        }
      } break;
      case Condition::Removed: {
        next_grid.get_cell(j).set_condition(Condition::Removed);
      } break;
      case Condition::Void: {
        next_grid.get_cell(j).set_condition(Condition::Void);
      } break;
    }
  }
  return next_grid;
}

/* global scope function */
double random_value() {
  std::random_device rd;
  std::default_random_engine generator(rd());
  std::uniform_real_distribution<double> distribution(0.0, 1.0);
  double random_n = distribution(generator);

  return random_n;
}