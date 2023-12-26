#include <catch2/catch_test_macros.hpp>

#include "ready_set_bool.hpp"

using namespace m42;

TEST_CASE("first 16 gray codes", "[gray_code]") {
    REQUIRE(gray_code(0b0000) == 0b0000); // 0 -> 0
    REQUIRE(gray_code(0b0001) == 0b0001); // 1 -> 1
    REQUIRE(gray_code(0b0010) == 0b0011); // 2 -> 3
    REQUIRE(gray_code(0b0011) == 0b0010); // 3 -> 2
    REQUIRE(gray_code(0b0100) == 0b0110); // 4 -> 6
    REQUIRE(gray_code(0b0101) == 0b0111); // 5 -> 7
    REQUIRE(gray_code(0b0110) == 0b0101); // 6 -> 5
    REQUIRE(gray_code(0b0111) == 0b0100); // 7 -> 4
    REQUIRE(gray_code(0b1000) == 0b1100); // 8 -> 12
    REQUIRE(gray_code(0b1001) == 0b1101); // 9 -> 13
    REQUIRE(gray_code(0b1010) == 0b1111); // 10 -> 15
}

