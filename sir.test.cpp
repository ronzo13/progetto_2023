#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "sir.hpp"

#include "doctest.h"

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