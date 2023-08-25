#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "grid.hpp"

#include "doctest.h"

TEST_CASE("Testing basics") {
  SUBCASE("Testing the get_condition function"){
    Cell a;
    Cell b(Condition::Removed);

    CHECK(a.get_condition() == Condition::Void);
    CHECK(b.get_condition() == Condition::Removed);
  }

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

  SUBCASE("Testing the get_cell function") {}

  SUBCASE("Testing the count_s/i/r functions") {
    Grid grid(10);
    grid.fill(90, 8);

    int side = grid.get_side();
    int S = grid.count_s();
    int I = grid.count_i();
     // int R = grid.count_r();
    int voids = (side * side) - (S + I);

    CHECK(S == 90);
    CHECK(I == 8);
    CHECK(voids == 2);
  }

  SUBCASE("Testing the inf_neigh function") {
    Grid grid(5);

    grid.get_cell(1).set_condition(Condition::Infected);
    grid.get_cell(2).set_condition(Condition::Susceptible);
    grid.get_cell(5).set_condition(Condition::Infected); 
    grid.get_cell(6).set_condition(Condition::Infected);
    //m_cells[0] and m_cells[7] should be Void by default

    CHECK(grid.inf_neigh(0) == 3);
    CHECK(grid.inf_neigh(1) == 2);
  }
}

TEST_CASE("Testing principal grid methods") {
  SUBCASE("Testing the fill function") {}

  SUBCASE("Testing the evolution function") {}  
}