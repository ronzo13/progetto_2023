#include "grid.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include <random>

#include "cell.hpp"

Grid::Grid(int side) : m_side{side}, m_cells(side * side){};

int Grid::get_side() const { return m_side; }

Cell const& Grid::get_cell(int pos) const {
  assert(pos >= 0);
  return m_cells[pos];
}

double Grid::random_value() const {
  std::random_device rd;
  std::default_random_engine generator(rd());
  std::uniform_real_distribution<double> distribution(0.0, 1.0);
  double random_n = distribution(generator);

  return random_n;
}

int Grid::inf_neigh(Grid const& init_grid, int pos) const {
  assert(pos >= 0);
  int count{};
  int g_side = init_grid.get_side();
  int prow = pos - g_side;
  int srow = pos + g_side;

  for (int i{-1}; i <= 1; ++i) {
    int cell_prow = prow + i;  // celle della fila precedente
    if (init_grid.get_cell(cell_prow).get_state() == State::Infected) {
      ++count;
    }
  }

  for (int i{-1}; i <= 1; ++i) {
    int cell_crow = pos + i;  // celle della fila in cui si trova pos
    if (init_grid.get_cell(cell_crow).get_state() == State::Infected) {
      ++count;
    }
  }

  for (int i{-1}; i <= 1; ++i) {
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

// crea e ritorna la griglia successiva
Grid Grid::evolution(Grid const& init_grid, double beta, double gamma) {
  int const side = init_grid.get_side();
  Grid next_grid{side};

  // infection and removal rules
  for (int j{}; j < side * side; ++j) {
    State i_person = init_grid.get_cell(j).get_state();

    switch (i_person) {
      case State::Susceptible: {
        double const p_i = 1.0 - pow(1.0 - beta, inf_neigh(init_grid, j));
        assert(p_i >= 0 && p_i <= 1);
        if (random_value() < p_i) {
          next_grid.get_cell(j).set_state(State::Infected);
        } else {
          next_grid.get_cell(j).set_state(State::Susceptible);
        }
      } break;
      case State::Infected: {
        if (random_value() < gamma) {
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
  return next_grid;
}

// aggiungere funzione che conti il numero di suscettibili, infetti e rimossi

int Grid::count_s() const {
  return std::accumulate(
    m_cells.begin(), m_cells.end(), 0,
    [](int sum, const Cell& cell) {
      return sum + (cell.get_state() == State::Susceptible ? 1 : 0);
    }
  );
}

int Grid::count_i() const {
  return std::accumulate(
    m_cells.begin(), m_cells.end(), 0,
    [](int sum, const Cell& cell) {
      return sum + (cell.get_state() == State::Infected ? 1 : 0);
    }
  );
}

int Grid::count_r() const {
  return std::accumulate(
    m_cells.begin(), m_cells.end(), 0,
    [](int sum, const Cell& cell) {
      return sum + (cell.get_state() == State::Removed ? 1 : 0);
    }
  );
}



int main() {
  int side;
  std::cout << "Insert the side of the grid: \n";
  std::cin >> side;
  Grid my_grid{side};

  // assegnazione casuale degli stati alle celle
  for (int i{}; i < side * side; ++i) {
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<> dist{0, 3};
    int random_num = dist(gen);
    switch (random_num) {
      case 0: {
        my_grid.get_cell(i).set_state(State::Susceptible);
      } break;
      case 1: {
        my_grid.get_cell(i).set_state(State::Infected);
      } break;
      case 2: {
        my_grid.get_cell(i).set_state(State::Removed);
      } break;
      case 3: {
        my_grid.get_cell(i).set_state(State::Void);
      } break;
    }
  }

  int days{};
  double gamma{};
  double beta{};

  std::cout << "Insert the epidemic duration (in days), gamma and beta: \n";
  std::cin >> days >> gamma >> beta;

  // qui deve succedere qualcosa
}
