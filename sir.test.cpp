#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "sir.hpp"

#include <iostream>
#include <sstream>
#include <exception>

#include "doctest.h"

TEST_CASE("Testing what happens with beta or gamma out of range") {
  SUBCASE("Beta out of range") {
    Param param;
    param.beta = 2;
    param.gamma = 0.4;
    State state(350, 1, 0);

    CHECK_THROWS(SIR(state, param));
  }

  SUBCASE("Gamma out of range") {
    Param param;
    param.beta = 0.65;
    param.gamma = 4;
    State state(350, 1, 0);

    CHECK_THROWS(SIR(state, param));
  }
}

TEST_CASE("Testing the check_state function") {
  SUBCASE("Negative values for s") {
    State state(-500, 2, 0);
    SIR sir{state, {0.5, 0.4}};
    int days{5};

    CHECK(sir.check_state() == false);
    CHECK_THROWS(sir.evolve(days));
  }

  SUBCASE("Negative values for i") {
    State state(850, -1, 0);
    SIR sir{state, {0.8, 0.2}};
    int days{5};

    CHECK(sir.check_state() == false);
    CHECK_THROWS(sir.evolve(days));
  }

  SUBCASE("Negative values for r") {
    State state(200, 3, -10);
    SIR sir{state, {0.7, 0.4}};
    int days{10};

    CHECK(sir.check_state() == false);
    CHECK_THROWS(sir.evolve(days));
  }
}

TEST_CASE("Testing the class handling the evolution of a sir status") {
  SUBCASE("1 day") {
    State state(93, 7, 0);
    SIR sir{state, {0.7, 0.2}};
    int days{1};
    std::vector<State> epidemic = sir.evolve(days);
    auto const& _sir = epidemic[days];

    CHECK(_sir.s == 88);
    CHECK(_sir.i == 11);
    CHECK(_sir.r == 1);
    CHECK(sir.get_total() == (_sir.s + _sir.i + _sir.r));
  }

  SUBCASE("2 days") {
    State state(93, 7, 0);
    SIR sir{state, {0.7, 0.2}};
    int days{2};
    std::vector<State> epidemic = sir.evolve(days);
    auto const& _sir = epidemic[days];

    CHECK(_sir.s == 81);
    CHECK(_sir.i == 16);
    CHECK(_sir.r == 3);
    CHECK(sir.get_total() == (_sir.s + _sir.i + _sir.r));
  }

  SUBCASE("3 days") {
    State state(93, 7, 0);
    SIR sir{state, {0.7, 0.2}};
    int days{3};
    std::vector<State> epidemic = sir.evolve(days);
    auto const& _sir = epidemic[days];

    CHECK(_sir.s == 72);
    CHECK(_sir.i == 22);
    CHECK(_sir.r == 6);
    CHECK(sir.get_total() == (_sir.s + _sir.i + _sir.r));
  }
}


bool inputValidation(double check_value, bool& valid_input) {
    if (check_value == static_cast<int>(check_value) && check_value >= 0) {
        valid_input = true;
        return true;
    } else {
        valid_input = false;
        throw std::invalid_argument("Invalid value.");
    }
}


TEST_CASE("Test input validation") {
    bool valid_input{false}; // Initialize valid_input to false

    SUBCASE("Valid input") {
        CHECK_NOTHROW(inputValidation(42.0, valid_input)); // No exception should be thrown
        CHECK(valid_input == true);
    }

    SUBCASE("Valid input - integer") {
        CHECK_NOTHROW(inputValidation(10.0, valid_input)); // No exception should be thrown
        CHECK(valid_input == true);
    }

    SUBCASE("Invalid input - negative number") {
        CHECK_THROWS_AS(inputValidation(-5.0, valid_input), std::invalid_argument);
        CHECK(valid_input == false);
    }

    SUBCASE("Invalid input - decimal number") {
        CHECK_THROWS_AS(inputValidation(3.14, valid_input), std::invalid_argument);
        CHECK(valid_input == false);
    }


}

bool inputValidation2(double check_value, bool& valid_input) {
    if (check_value >= 0 && check_value <= 1) {
        valid_input = true;
        return true;
    } else {
        valid_input = false;
        throw std::invalid_argument("Invalid value.");
    }
}

TEST_CASE("Test input validation") {
    bool valid_input{false}; // Initialize valid_input to false

    SUBCASE("Valid input") {
        CHECK_NOTHROW(inputValidation2(0.6, valid_input)); // No exception should be thrown
        CHECK(valid_input == true);
    }

    SUBCASE("Valid input") {
        CHECK_NOTHROW(inputValidation2(0.3, valid_input)); // No exception should be thrown
        CHECK(valid_input == true);
    }

    SUBCASE("Invalid input - negative number") {
        CHECK_THROWS_AS(inputValidation2(-5.0, valid_input), std::invalid_argument);
        CHECK(valid_input == false);
    }

    SUBCASE("Invalid input - out of range") {
        CHECK_THROWS_AS(inputValidation2(2.13, valid_input), std::invalid_argument);
        CHECK(valid_input == false);
    }

    
}