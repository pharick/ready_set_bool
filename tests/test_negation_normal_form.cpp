#include <catch2/catch_test_macros.hpp>

#include "ready_set_bool.hpp"

using namespace m42;

TEST_CASE("negation normal form subject cases", "[negation_normal_form]") {
    REQUIRE(negation_normal_form("AB=") == "AB&A!B!&|");
    REQUIRE(negation_normal_form("AB&!") == "A!B!|");
    REQUIRE(negation_normal_form("AB|!") == "A!B!&");
    REQUIRE(negation_normal_form("AB>") == "A!B|");
    REQUIRE(negation_normal_form("AB|C&!") == "A!B!&C!|");
}

TEST_CASE("negation normal form simple cases", "[negation_normal_form]") {
    REQUIRE(negation_normal_form("A!!") == "A");
    REQUIRE(negation_normal_form("A!!!") == "A!");
    REQUIRE(negation_normal_form("db|") == "DB|");
    REQUIRE(negation_normal_form("db|!") == "D!B!&");
    REQUIRE(negation_normal_form("db|!!") == "DB|");
    REQUIRE(negation_normal_form("db|!!!") == "D!B!&");
    REQUIRE(negation_normal_form("d!b!|!") == "DB&");
}
