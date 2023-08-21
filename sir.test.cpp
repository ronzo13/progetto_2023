#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "sir.hpp"

#include "doctest.h"

TEST_CASE("Testing what happens with beta or gamma out of range") {
  SUBCASE("Beta out of range") {
    Param param;
    param.beta = 2;
    param.gamma = 0.4;

    CHECK_THROWS(SIR(350, 1, 0, param));
  }

  SUBCASE("Gamma out of range") {
    Param param;
    param.beta = 0.65;
    param.gamma = 4;

    CHECK_THROWS(SIR(350, 1, 0, param));
  }
}

TEST_CASE("Testing the check_state function") {
  SUBCASE("Negative values for m_s") {
    SIR sir{-500, 2, 0, {0.5, 0.4}};
    int days{5};

    CHECK(sir.check_state() == false);
    CHECK_THROWS(sir.evolve(days));
  }

  SUBCASE("Negative values for m_i") {
    SIR sir{850, -1, 0, {0.8, 0.2}};
    int days{5};

    CHECK(sir.check_state() == false);
    CHECK_THROWS(sir.evolve(days));
  }

  SUBCASE("Negative values for m_r") {
    SIR sir{200, 3, -10, {0.7, 0.4}};
    int days{10};

    CHECK(sir.check_state() == false);
    CHECK_THROWS(sir.evolve(days));
  }
}

TEST_CASE("Testing the class handling the evolution of a sir status") {
  SUBCASE("1 day") {
    SIR sir{93, 7, 0, {0.7, 0.2}};
    int days{1};
    std::vector<SIR> epidemic = sir.evolve(days);
    auto const& _sir = epidemic[1];

    CHECK(_sir.get_s() == 88);
    CHECK(_sir.get_i() == 11);
    CHECK(_sir.get_r() == 1);
    CHECK(sir.get_total() == (_sir.get_s() + _sir.get_i() + _sir.get_r()));
  }

  SUBCASE("2 days") {
    SIR sir{93, 7, 0, {0.7, 0.2}};
    int days{2};
    std::vector<SIR> epidemic = sir.evolve(days);
    auto const& _sir = epidemic[2];

    CHECK(_sir.get_s() == 81);
    CHECK(_sir.get_i() == 16);
    CHECK(_sir.get_r() == 3);
    CHECK(sir.get_total() == (_sir.get_s() + _sir.get_i() + _sir.get_r()));
  }

  SUBCASE("3 days") {
    SIR sir{93, 7, 0, {0.7, 0.2}};
    int days{3};
    std::vector<SIR> epidemic = sir.evolve(days);
    auto const& _sir = epidemic[3];

    CHECK(_sir.get_s() == 72);
    CHECK(_sir.get_i() == 22);
    CHECK(_sir.get_r() == 6);
    CHECK(sir.get_total() == (_sir.get_s() + _sir.get_i() + _sir.get_r()));
  }
}