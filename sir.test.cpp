#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "sir.hpp"

#include "doctest.h"

TEST_CASE("Testing basics") {
  SUBCASE("Testing the get_total() function") {
    Param param{0.7, 0.2};
    State state{93, 7, 0};
    SIR sir{state, param};

    CHECK(sir.get_total() == 100);
  }

  SUBCASE("Testing the operator == for equal states") {
    State state_one{100, 25, 0};
    State state_two{100, 25, 0};

    CHECK((state_one == state_two) == true);
  }

  SUBCASE("Testing the operator == for different states") {
    State state_one{100, 25, 0};
    State state_two{115, 25, 0};

    CHECK((state_one == state_two) == false);
  }
}

TEST_CASE("Testing the class handling the evolution of a sir status") {
  SUBCASE("0 day") {
    Param param{0.7, 0.2};
    State state{93, 7, 0};
    SIR sir{state, param};
    int days{0};
    std::vector<State> epidemic = sir.evolve(days);
    auto const& _sir = epidemic[days];

    CHECK(_sir.s == 93);
    CHECK(_sir.i == 7);
    CHECK(_sir.r == 0);
    CHECK(sir.get_total() == (_sir.s + _sir.i + _sir.r));
  }

  SUBCASE("1 day") {
    Param param{0.7, 0.2};
    State state{93, 7, 0};
    SIR sir{state, param};
    int days{1};
    std::vector<State> epidemic = sir.evolve(days);
    auto const& _sir = epidemic[days];

    CHECK(_sir.s == 88);
    CHECK(_sir.i == 11);
    CHECK(_sir.r == 1);
    CHECK(sir.get_total() == (_sir.s + _sir.i + _sir.r));
  }

  SUBCASE("2 days") {
    Param param{0.7, 0.2};
    State state{93, 7, 0};
    SIR sir{state, param};
    int days{2};
    std::vector<State> epidemic = sir.evolve(days);
    auto const& _sir = epidemic[days];

    CHECK(_sir.s == 81);
    CHECK(_sir.i == 16);
    CHECK(_sir.r == 3);
    CHECK(sir.get_total() == (_sir.s + _sir.i + _sir.r));
  }

  SUBCASE("3 days") {
    Param param{0.7, 0.2};
    State state{93, 7, 0};
    SIR sir{state, param};
    int days{3};
    std::vector<State> epidemic = sir.evolve(days);
    auto const& _sir = epidemic[days];

    CHECK(_sir.s == 72);
    CHECK(_sir.i == 22);
    CHECK(_sir.r == 6);
    CHECK(sir.get_total() == (_sir.s + _sir.i + _sir.r));
  }
}

TEST_CASE("Testing the 's = -1' parameters") {
  Param param{0.3, 0.03};
  State state{1000, 10, 1};
  SIR sir{state, param};
  int days{1000};
  std::vector<State> epidemic = sir.evolve(days);

  for (auto const& _sir : epidemic) {
    CHECK(_sir.s >= 0);
    CHECK(_sir.i >= 0);
    CHECK(_sir.r >= 0);
  }
}