#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "sir.hpp"

#include "doctest.h"

TEST_CASE("Testing the check_state function"){
    SUBCASE("Negative values for m_s"){
        SIR sir{-500, 2, 0, {0.5, 0.4}};
        
        CHECK(sir.check_state() == false);
        CHECK_THROWS(sir.evolve());
    }

    SUBCASE("Negative values for m_i"){
        SIR sir{850, -1, 0, {0.8, 0.2}};
        
        CHECK(sir.check_state() == false);
        CHECK_THROWS(sir.evolve());
    }

    SUBCASE("Beta out of range"){
        SIR sir{500, 2, 0, {2, 0.3}};

        CHECK(sir.check_state() == false);
        CHECK_THROWS(sir.evolve());
    }

    SUBCASE("Gamma out of range"){
        SIR sir{500, 2, 0, {0.6, 3}};

        CHECK(sir.check_state() == false);
        CHECK_THROWS(sir.evolve());
    }    
}

TEST_CASE("Testing the class handling the evolution of a sir status in a day") {
    SUBCASE("#1"){
        SIR sir{95, 5, 0, {0.6, 0.3}};
        sir.evolve();
        
        CHECK(sir.get_s() == 92);
        CHECK(sir.get_i() == 6);
        CHECK(sir.get_r() == 2);
        CHECK(sir.total() == (sir.get_s() + sir.get_i() + sir.get_r()));
    }

    SUBCASE("#2"){
    }
}

TEST_CASE("Testing the class handling the evolution of a sir status in two days") {
    SUBCASE("#1"){

    }

    SUBCASE("#2"){
        
    }
}
