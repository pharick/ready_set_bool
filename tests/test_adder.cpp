#include <random>

#include <catch2/catch_test_macros.hpp>

#include "ready_set_bool.hpp"

using namespace m42;

TEST_CASE("half_adder", "[adder]") {
    bool sum, carry;

    // 0 + 0 = 00
    half_adder(false, false, sum, carry);
    REQUIRE(sum == false);
    REQUIRE(carry == false);

    // 0 + 1 = 01
    half_adder(false, true, sum, carry);
    REQUIRE(sum == true);
    REQUIRE(carry == false);

    // 1 + 0 = 01
    half_adder(true, false, sum, carry);
    REQUIRE(sum == true);
    REQUIRE(carry == false);

    // 1 + 1 = 10
    half_adder(true, true, sum, carry);
    REQUIRE(sum == false);
    REQUIRE(carry == true);
}

TEST_CASE("full_adder", "[adder]") {
    bool sum, carry;

    // 0 + 0 + 0 = 00
    full_adder(false, false, false, sum, carry);
    REQUIRE(sum == false);
    REQUIRE(carry == false);

    // 0 + 0 + 1 = 01
    full_adder(false, false, true, sum, carry);
    REQUIRE(sum == true);
    REQUIRE(carry == false);

    // 0 + 1 + 0 = 01
    full_adder(false, true, false, sum, carry);
    REQUIRE(sum == true);
    REQUIRE(carry == false);

    // 0 + 1 + 1 = 10
    full_adder(false, true, true, sum, carry);
    REQUIRE(sum == false);
    REQUIRE(carry == true);

    // 1 + 0 + 0 = 01
    full_adder(true, false, false, sum, carry);
    REQUIRE(sum == true);
    REQUIRE(carry == false);

    // 1 + 0 + 1 = 10
    full_adder(true, false, true, sum, carry);
    REQUIRE(sum == false);
    REQUIRE(carry == true);

    // 1 + 1 + 0 = 10
    full_adder(true, true, false, sum, carry);
    REQUIRE(sum == false);
    REQUIRE(carry == true);

    // 1 + 1 + 1 = 11
    full_adder(true, true, true, sum, carry);
    REQUIRE(sum == true);
    REQUIRE(carry == true);
}

TEST_CASE("add first 100 numbers", "[adder]") {
    for (uint32_t a = 0; a < 100; ++a) {
        for (uint32_t b = 0; b < 100; ++b) {
            REQUIRE(adder(a, b) == a + b);
        }
    }
}

TEST_CASE("random adder test", "[adder]") {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32_t> rand(0, UINT32_MAX);
    for (size_t i = 0; i < 100; ++i) {
        uint32_t a = rand(gen);
        uint32_t b = rand(gen);
        REQUIRE(adder(a, b) == a + b);
    }
}
