#include <catch2/catch_test_macros.hpp>

#include "ready_set_bool.hpp"

using namespace m42;

TEST_CASE("powerset", "[powerset]") {
    std::set<int> empty;
    std::set<std::set<int>> expected;
    expected.insert(empty);
    REQUIRE(powerset(empty) == expected);

    std::set<int> set1 = {1};
    expected.insert(set1);
    REQUIRE(powerset(set1) == expected);

    std::set<int> set2 = {1, 2};
    std::set<std::set<int>> expected2 = {
        empty,
        {1},
        {2},
        {1, 2}
    };
    REQUIRE(powerset(set2) == expected2);

    std::set<int> set3 = {1, 2, 3};
    std::set<std::set<int>> expected3 = {
        empty,
        {1},
        {2},
        {3},
        {1, 2},
        {1, 3},
        {2, 3},
        {1, 2, 3}
    };
    REQUIRE(powerset(set3) == expected3);
}
