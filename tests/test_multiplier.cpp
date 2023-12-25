#include <random>

#include <catch2/catch_test_macros.hpp>

#include "ready_set_bool.hpp"

TEST_CASE("multiply first 100 numbers", "[multiplier]") {
    for (uint32_t a = 0; a < 100; ++a) {
        for (uint32_t b = 0; b < 100; ++b) {
            REQUIRE(multiplier(a, b) == a * b);
        }
    }
}

TEST_CASE("random multiplier test", "[adder]") {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32_t> rand(0, UINT32_MAX);
    for (size_t i = 0; i < 100; ++i) {
        uint32_t a = rand(gen);
        uint32_t b = rand(gen);
        REQUIRE(multiplier(a, b) == a * b);
    }
}
