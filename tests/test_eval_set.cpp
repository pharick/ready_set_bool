#include <catch2/catch_test_macros.hpp>

#include "ready_set_bool.hpp"

using namespace m42;

TEST_CASE("eval_set subject cases", "[eval_set]") {
    std::map<char, std::set<int>> vars1{
        {'A', std::set{0, 1, 2}},
        {'B', std::set{0, 3, 4}},
    };
    REQUIRE(eval_set("AB&", vars1) == std::set{0});

    std::map<char, std::set<int>> vars2{
        {'A', std::set{0, 1, 2}},
        {'B', std::set{3, 4, 5}},
    };
    REQUIRE(eval_set("AB|", vars2) == std::set{0, 1, 2, 3, 4, 5});

    std::map<char, std::set<int>> vars3{
        {'A', std::set{0, 1, 2}},
    };
    REQUIRE(eval_set("A!", vars3).empty());
}
