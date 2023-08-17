#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "sir.hpp"

#include "doctest.h"

TEST_CASE("Testing the check_state function") {
  SUBCASE("Negative values for m_s") {
    Status status{{0.5, 0.4}, {-500, 2, 0}, 10};

    CHECK(status.check_state() == false);
    CHECK_THROWS(status.evolve());
  }

  SUBCASE("Negative values for m_i") {
    Status status{{0.8, 0.2}, {850, -1, 0}, 10};

    CHECK(status.check_state() == false);
    CHECK_THROWS(status.evolve());
  }

  SUBCASE("Beta out of range") {
    Status status{{2, 0.3}, {500, 2, 0}, 10};

    CHECK(status.check_state() == false);
    CHECK_THROWS(status.evolve());
  }

  SUBCASE("Gamma out of range") {
    Status status{{0.6, 3}, {500, 2, 0}, 10};

    CHECK(status.check_state() == false);
    CHECK_THROWS(status.evolve());
  }
}

TEST_CASE("Testing the class handling the evolution of a Status status") {
  SUBCASE("1 day") {
    Status status{{0.7, 0.2}, {93, 7, 0}, 10};
    status.evolve();

    CHECK(status.get_s() == 88);
    CHECK(status.get_i() == 11);
    CHECK(status.get_r() == 1);
    CHECK(status.total() == (status.get_s() + status.get_i() + status.get_r()));
  }

  SUBCASE("2 days") {
    Status status{{0.7, 0.2}, {93, 7, 0}, 10};
    status.evolve();
    status.evolve();
    CHECK(status.get_s() == 81);
    CHECK(status.get_i() == 16);
    CHECK(status.get_r() == 3);
    CHECK(status.total() == (status.get_s() + status.get_i() + status.get_r()));
  }

  SUBCASE("3 days") {
    Status status{{0.7, 0.2}, {93, 7, 0}, 10};
    status.evolve();
    status.evolve();
    status.evolve();

    CHECK(status.get_s() == 72);
    CHECK(status.get_i() == 22);
    CHECK(status.get_r() == 6);
    CHECK(status.total() == (status.get_s() + status.get_i() + status.get_r()));
  }
}