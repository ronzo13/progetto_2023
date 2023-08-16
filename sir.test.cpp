#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "sir.hpp"

#include "doctest.h"

TEST_CASE("Testing the class handling the evolution of a sir status 1") {
  SIR sir{93, 7, 0, {0.7, 0.2}};
  sir.evolve();

  CHECK(sir.get_s() == 88);
  CHECK(sir.get_i() == 11);
  CHECK(sir.get_r() == 1);
  CHECK(sir.total() == (sir.get_s() + sir.get_i() + sir.get_r()));
}

TEST_CASE("Testing the class handling the evolution of a sir status 2") {
  SIR sir{93, 7, 0, {0.7, 0.2}};
  sir.evolve();
  sir.evolve();
  CHECK(sir.get_s() == 81);
  CHECK(sir.get_i() == 16);
  CHECK(sir.get_r() == 3);
  CHECK(sir.total() == (sir.get_s() + sir.get_i() + sir.get_r()));
}

TEST_CASE("Testing the class handling the evolution of a sir status 3") {
  SIR sir{93, 7, 0, {0.7, 0.2}};
  sir.evolve();
  sir.evolve();
  sir.evolve();

  CHECK(sir.get_s() == 72);
  CHECK(sir.get_i() == 22);
  CHECK(sir.get_r() == 6);
  CHECK(sir.total() == (sir.get_s() + sir.get_i() + sir.get_r()));
}