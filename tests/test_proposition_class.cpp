#include <catch2/catch_test_macros.hpp>

#include "ready_set_bool.hpp"

namespace m42 {

    TEST_CASE("parse formula", "[Proposition]") {
        std::string formula = "AC|!B!&";
        Proposition p(formula);
        REQUIRE(p.vars().size() == 3);
        REQUIRE(p.vars().count('A') == 1);
        REQUIRE(p.vars().count('B') == 1);
        REQUIRE(p.vars().count('C') == 1);
        REQUIRE(p.postfix_notation() == formula);
    }

    TEST_CASE("reverse polish notation", "[Proposition]") {
        std::string formula = "ACB!!&|";
        REQUIRE(Proposition(formula).postfix_notation() == formula);
        formula = "A!B&";
        REQUIRE(Proposition(formula).postfix_notation() == formula);
    }

}
