#include <catch2/catch_test_macros.hpp>

#include "ready_set_bool.hpp"

using namespace m42;

TEST_CASE("conjunctive normal form subject cases", "[conjunctive_normal_form]") {
    REQUIRE(conjunctive_normal_form("AB&!") == "A!B!|");
    REQUIRE(conjunctive_normal_form("AB|!") == "A!B!&");
    REQUIRE(conjunctive_normal_form("AB|C&") == "AB|C&");
    REQUIRE(conjunctive_normal_form("AB|C|D|") == "ABCD|||");
    REQUIRE(conjunctive_normal_form("AB&C&D&") == "ABCD&&&");
    REQUIRE(conjunctive_normal_form("AB&!C!|") == "A!B!C!||");
    REQUIRE(conjunctive_normal_form("AB|!C!&") == "A!B!C!&&");
    REQUIRE(conjunctive_normal_form("ABCD&|&") == "ABC|BD|&&");
    REQUIRE(conjunctive_normal_form("AC|!B&") == "A!C!B&&");
}
