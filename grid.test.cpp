#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "grid.hpp"

#include "doctest.h"

TEST_CASE("Testing the get_side function") {
  SUBCASE("#1") {
    Grid grid(4);

    CHECK(grid.get_side() == 4);
  }
}

TEST_CASE("Testing the get_cell function"){}

TEST_CASE("Testing the inf_neigh function"){}

TEST_CASE("Testing the evolution function"){}