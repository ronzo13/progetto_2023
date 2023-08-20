#include "grid.hpp"

#include <cassert>
#include <cmath>
#include <random>

#include "cell.hpp"

Grid::Grid(int side) : m_side{side}, m_cells(side * side){};

int Grid::get_side() const { return m_side; }

Cell& Grid::get_cell(int pos) { return m_cells[pos]; };

Cell const& Grid::get_cell(int pos) const { return m_cells[pos]; }

int Grid::inf_neigh(Grid& init_grid) const {
  int count{};
  int pos{};
  int g_side{init_grid.get_side()};
  int prow{pos - g_side};
  int srow{pos + g_side};

  for (int i = -1; i <= 1; ++i) {
    int cell_prow = prow + i;  // celle della fila precedente
    if (init_grid.get_cell(cell_prow).get_state() == State::Infected) {
      ++count;
    }
  }

  for (int i = -1; i <= 1; ++i) {
    int cell_crow = pos + i;  // celle della fila in cui si trova pos
    if (init_grid.get_cell(cell_crow).get_state() == State::Infected) {
      ++count;
    }
  }

  for (int i = -1; i <= 1; ++i) {
    int cell_srow = srow + i;  // celle della fila successiva
    if (init_grid.get_cell(cell_srow).get_state() == State::Infected) {
      ++count;
    }
  }

  if (init_grid.get_cell(pos).get_state() == State::Infected) {
    count += -1;
  }

  return count;
}

void Grid::evolution(Grid& init_grid, double beta, double gamma) {
  int const side = init_grid.get_side();
  Grid next_grid{side};

  std::default_random_engine generator{std::random_device{}()};
  std::uniform_real_distribution<double> distribution(0.0, 1.0);
  double random_n = distribution(generator);

  // infection and removal rules
  for (int j = 0; j != (side * side) - 1; ++j) {
    State i_person{init_grid.get_cell(j).get_state()};

    switch (i_person) {
      case State::Susceptible: {
        double const p_i = 1.0 - pow(1.0 - beta, inf_neigh(init_grid));
        assert(p_i >= 0 && p_i <= 1);
        if (random_n < p_i) {
          next_grid.get_cell(j).set_state(State::Infected);
        } else {
          next_grid.get_cell(j).set_state(State::Susceptible);
        }
      } break;
      case State::Infected: {
        if (random_n < gamma) {
          next_grid.get_cell(j).set_state(State::Removed);
        } else {
          next_grid.get_cell(j).set_state(State::Infected);
        }
      } break;
      case State::Removed: {
        next_grid.get_cell(j).set_state(State::Removed);
      } break;
      case State::Void: {
        next_grid.get_cell(j).set_state(State::Void);
      } break;
    }
  }
}
