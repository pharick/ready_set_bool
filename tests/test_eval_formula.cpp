#include <catch2/catch_test_macros.hpp>

#include "ready_set_bool.hpp"

using namespace m42;

TEST_CASE("subject examples", "[eval_formula]") {
    REQUIRE(eval_formula("10&") == false);
    REQUIRE(eval_formula("10|") == true);
    REQUIRE(eval_formula("11>") == true);
    REQUIRE(eval_formula("10=") == false);
    REQUIRE(eval_formula("1011||=") == true);
    REQUIRE(eval_formula("0!") == true);
    REQUIRE(eval_formula("1!") == false);
}

TEST_CASE("invalid formulas", "[eval_formula]") {
    REQUIRE_THROWS(eval_formula(""));
    REQUIRE_THROWS(eval_formula("1|"));
    REQUIRE_THROWS(eval_formula("1&0"));
    REQUIRE_THROWS(eval_formula("01&v"));
}
