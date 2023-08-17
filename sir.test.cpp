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

    CHECK(sir.check_state() == false);
    CHECK_THROWS(sir.evolve());
  }

  SUBCASE("Negative values for m_i") {
    SIR sir{850, -1, 0, {0.8, 0.2}};

    CHECK(sir.check_state() == false);
    CHECK_THROWS(sir.evolve());
  }

  SUBCASE("Negative values for m_r") {
    SIR sir{200, 3, -10, {0.7, 0.4}};

    CHECK(sir.check_state() == false);
    CHECK_THROWS(sir.evolve());
  }
}

TEST_CASE("Testing what happens with 0 infected") {  // se ci sono 0 infetti
                                                     // l'epidemia non parte
  SIR sir{100, 0, 0, {0.8, 0.2}};
  sir.evolve();
  sir.evolve();
  sir.evolve();

  CHECK(sir.get_s() == 100);
  CHECK(sir.get_i() == 0);
  CHECK(sir.get_r() == 0);
  CHECK(sir.total() == (sir.get_s() + sir.get_i() + sir.get_r()));
}

TEST_CASE("Testing the class handling the evolution of a sir status") {
  SUBCASE("1 day") {
    SIR sir{93, 7, 0, {0.7, 0.2}};
    sir.evolve();

    CHECK(sir.get_s() == 88);
    CHECK(sir.get_i() == 11);
    CHECK(sir.get_r() == 1);
    CHECK(sir.total() == (sir.get_s() + sir.get_i() + sir.get_r()));
  }

  SUBCASE("2 days") {
    SIR sir{93, 7, 0, {0.7, 0.2}};
    sir.evolve();
    sir.evolve();
    CHECK(sir.get_s() == 81);
    CHECK(sir.get_i() == 16);
    CHECK(sir.get_r() == 3);
    CHECK(sir.total() == (sir.get_s() + sir.get_i() + sir.get_r()));
  }

  SUBCASE("3 days") {
    SIR sir{93, 7, 0, {0.7, 0.2}};
    sir.evolve();
    sir.evolve();
    sir.evolve();

    CHECK(sir.get_s() == 72);
    CHECK(sir.get_i() == 22);
    CHECK(sir.get_r() == 6);
    CHECK(sir.total() == (sir.get_s() + sir.get_i() + sir.get_r()));
  }
}
