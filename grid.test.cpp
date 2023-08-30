#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "grid.hpp"

#include "doctest.h"

TEST_CASE("Testing methods of the Cell class") {
  SUBCASE("Testing the get_condition function") {
    Cell a;
    Cell b(Condition::Removed);

    CHECK(a.get_condition() == Condition::Void);
    CHECK(b.get_condition() == Condition::Removed);
  }

  SUBCASE("Testing the set_condition function") {
    Cell a, b;
    a.set_condition(Condition::Susceptible);
    b.set_condition(Condition::Infected);
    CHECK(a.get_condition() == Condition::Susceptible);
    CHECK(b.get_condition() == Condition::Infected);
    CHECK(a.get_condition() != b.get_condition());
  }  
}

/*Testing mehods of the Grid class*/
TEST_CASE("Testing basics"){
  SUBCASE("Testing the get_side function") {
    Grid grid(4);
    CHECK(grid.get_side() == 4);
  }

  SUBCASE("Testing the valid_coord function") {
    Grid grid(8);

    CHECK(grid.valid_coord(-1, 0) == false);
    CHECK(grid.valid_coord(0, -1) == false);
    CHECK(grid.valid_coord(10, 6) == false);
    CHECK(grid.valid_coord(6, 10) == false);
    CHECK(grid.valid_coord(5, 4) == true);
  }

  SUBCASE("Testing the non-const get_cell function") {
    int side{8};
    Grid grid{side};
    int cell_pos{5};
    Cell& cell = grid.get_cell(cell_pos);
    cell.set_condition(Condition::Susceptible);

    CHECK(grid.count_s() == 1);
    CHECK(grid.get_cell(cell_pos).get_condition() == Condition::Susceptible);
    CHECK(cell.get_condition() == Condition::Susceptible);
  }

  SUBCASE("Testing the const get_cell function") {
    int side{6};
    Grid grid{side};
    int cell_pos{5};
    Cell const& cell = grid.get_cell(cell_pos);

    CHECK(grid.get_cell(cell_pos).get_condition() == Condition::Void);
    CHECK(cell.get_condition() == Condition::Void);
  }

  SUBCASE("Testing the count_s/i/r/voids functions") {
    int side{10};
    Grid grid{side};
    grid.fill(90, 8);
    
    int S = grid.count_s();
    int I = grid.count_i();
    int R = grid.count_r();
    int voids = grid.count_voids();

    CHECK(S == 90);
    CHECK(I == 8);
    CHECK(R == 0);
    CHECK(voids == 2);
  }

  SUBCASE("Testing the inf_neigh function") {
    int side{5};
    Grid grid{side};

    grid.get_cell(1).set_condition(Condition::Infected);
    grid.get_cell(2).set_condition(Condition::Susceptible);
    grid.get_cell(5).set_condition(Condition::Infected);
    grid.get_cell(6).set_condition(Condition::Infected);
    /* m_cells[0] and m_cells[7] should be Void by default */

    CHECK(grid.inf_neigh(0) == 3);
    CHECK(grid.inf_neigh(1) == 2);
  }
}

TEST_CASE("Testing the fill function") {
  SUBCASE("#1") {
    int side{10};
    Grid grid{side};
    int s{80}, i{20};
    grid.fill(s, i);
    
    CHECK(grid.count_s() == s);
    CHECK(grid.count_i() == i);
    CHECK(grid.count_r() == 0);
    CHECK(grid.count_voids() == 0);
  }

  SUBCASE("#2") {
    int side{20};
    Grid grid{side};
    int s{80}, i{20};
    grid.fill(s, i);
    
    CHECK(grid.count_s() == s);
    CHECK(grid.count_i() == i);
    CHECK(grid.count_r() == 0);
    CHECK(grid.count_voids() == 300);
  }
}


TEST_CASE("Decrease of susceptibles and increase of removed after calling evolution function") {
  SUBCASE("After 1 day") {
    int side{12};
    Grid grid{side};
    grid.fill(90, 4);
    double beta{0.3}, gamma{0.2};
    auto new_grid = grid.evolution(beta, gamma);

    CHECK(new_grid.count_s() <= grid.count_s());
    CHECK(new_grid.count_r() >= grid.count_r());
  }

  SUBCASE("After 10 days") {
    int days{10};
    int side{10};
    Grid grid{side};
    grid.fill(75, 5);
    double beta{0.5}, gamma{0.3};
    auto first_grid = grid;
    for (int i{}; i < days; ++i) {
      auto const& new_grid = grid.evolution(beta, gamma);
      grid = new_grid;
    }

    CHECK(grid.count_s() < first_grid.count_s());
    CHECK(grid.count_r() > first_grid.count_r());
    CHECK(first_grid.count_s() == 75);
    CHECK(first_grid.count_i() == 5);
  }
}
