#include "grid.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include <random>

#include "cell.hpp"

Grid::Grid(int side) : m_side{side}, m_cells(side * side) {}

int Grid::get_side() const { return m_side; }

Cell& Grid::get_cell(int pos) {  // referenza modificabile a una cella
  assert(pos >= 0 && pos < m_side * m_side);
  return m_cells[pos];
}

Cell const& Grid::get_cell(
    int pos) const {  // referenza non modificabile a una cella
  assert(pos >= 0 && pos < m_side * m_side);
  return m_cells[pos];
}

bool Grid::valid_coord(int row, int col) const {
  return row >= 0 && row < m_side && col >= 0 && col < m_side;
}

int Grid::random_cell() const {
  std::random_device rd;
  std::default_random_engine gen(rd());
  std::uniform_int_distribution<> dist(0, (m_side * m_side) - 1);
  int cell_pos = dist(gen);
  return cell_pos;
};

void Grid::fill(double p_s, double p_i) {
  // riempio caselle casuali della grigli con i suscettibili ottenuti dalla %
  // inserita
  int s = m_side * m_side * p_s;
  int i = m_side * m_side * p_i;
  for (int j{0}; j < s; ++j) {
    int random_num = Grid::random_cell();
    get_cell(random_num).set_condition(Condition::Susceptible);
  }

  // riempio caselle casuali della grigli con i suscettibili ottenuti dalla %
  // inserita
  for (int j{0}; j < i; ++j) {
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<> dist(0, (m_side * m_side) - 1);
    int random_num = dist(gen);

    get_cell(random_num).set_condition(Condition::Infected);
  }
}

double Grid::random_value() const {
  std::random_device rd;
  std::default_random_engine generator(rd());
  std::uniform_real_distribution<double> distribution(0.0, 1.0);
  double random_n = distribution(generator);

  return random_n;
}

int Grid::inf_neigh(int pos) const {
  int count{};
  int g_side = get_side();
  assert(pos >= 0 && pos < g_side * g_side);
  int row = pos / g_side;
  int col = pos % g_side;

  for (int i{-1}; i <= 1; ++i) {
    for (int j{-1}; j <= 1; ++j) {
      if (valid_coord(row + i, col + j) == true) {
        int index = (row + i) * g_side + (col + j);
        if (get_cell(index).get_condition() == Condition::Infected) {
          ++count;
        }
      }
    }
  }

  if (get_cell(pos).get_condition() == Condition::Infected) {
    count -= 1;
  }

  return count;
}

// crea e ritorna la griglia successiva
Grid Grid::evolution(double beta, double gamma) {
  int const side = get_side();
  Grid next_grid{side};

  // infection and removal rules
  for (int j{}; j < side * side; ++j) {
    Condition i_person = get_cell(j).get_condition();

    switch (i_person) {
      case Condition::Susceptible: {
        double const prob_infection = 1.0 - pow(1.0 - beta, inf_neigh(j));
        assert(prob_infection >= 0 && prob_infection <= 1);
        if (random_value() < prob_infection) {
          next_grid.get_cell(j).set_condition(Condition::Infected);
        } else {
          next_grid.get_cell(j).set_condition(Condition::Susceptible);
        }
      } break;
      case Condition::Infected: {
        if (random_value() < gamma) {
          next_grid.get_cell(j).set_condition(Condition::Removed);
        } else {
          next_grid.get_cell(j).set_condition(Condition::Infected);
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

int Grid::count_s() const {
  return std::accumulate(
      m_cells.begin(), m_cells.end(), 0, [](int sum, const Cell& cell) {
        return sum + (cell.get_condition() == Condition::Susceptible ? 1 : 0);
      });
}

int Grid::count_i() const {
  return std::accumulate(
      m_cells.begin(), m_cells.end(), 0, [](int sum, const Cell& cell) {
        return sum + (cell.get_condition() == Condition::Infected ? 1 : 0);
      });
}

int Grid::count_r() const {
  return std::accumulate(
      m_cells.begin(), m_cells.end(), 0, [](int sum, const Cell& cell) {
        return sum + (cell.get_condition() == Condition::Removed ? 1 : 0);
      });
}