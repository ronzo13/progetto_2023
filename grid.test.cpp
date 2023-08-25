#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "grid.hpp"

#include "doctest.h"

TEST_CASE("Testing basics") {
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

  SUBCASE("Testing the inf_neigh function") {}

  SUBCASE("Testing the evolution function") {}
}