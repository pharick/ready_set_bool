#include <catch2/catch_test_macros.hpp>

#include "ready_set_bool.hpp"

using namespace m42;

TEST_CASE("sat subject cases", "[sat]") {
    REQUIRE(sat("AB|") == true);
    REQUIRE(sat("AB&") == true);
    REQUIRE(sat("AA!&") == false);
    REQUIRE(sat("AA^") == false);
}

TEST_CASE("sat simple cases", "[sat]") {
    REQUIRE(sat("A") == true);
    REQUIRE(sat("A!") == true);
    REQUIRE(sat("1") == true);
    REQUIRE(sat("0") == false);
    REQUIRE(sat("10&") == false);
    REQUIRE(sat("10|") == true);
    REQUIRE(sat("10^") == true);
    REQUIRE(sat("10>") == false);
    REQUIRE(sat("10=") == false);
    REQUIRE(sat("AA!&") == false);
    REQUIRE(sat("AA!|") == true);
}
