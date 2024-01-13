#include <random>

#include <catch2/catch_test_macros.hpp>

#include "ready_set_bool.hpp"

using namespace m42;

TEST_CASE("interleave", "[curve]") {
    REQUIRE(interleave(0b1100, 0b1011) == 0b11011010);
    REQUIRE(interleave(0b1011, 0b1100) == 0b11100101);
    REQUIRE(interleave(0b0000, 0b1111) == 0b10101010);
    REQUIRE(interleave(0b1111, 0b0000) == 0b01010101);
    REQUIRE(interleave(0b0101, 0b1010) == 0b10011001);
}

TEST_CASE("map", "[curve]") {
    double m;
    uint32_t x, y;

    m = map(42, 21);
    REQUIRE(reverse_map(m) == std::make_pair<uint16_t, uint16_t>(42, 21));
    REQUIRE(m >= 0.0);
    REQUIRE(m <= 1.0);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32_t> rand(0, UINT32_MAX);
    for (size_t i = 0; i < 100; ++i) {
        x = rand(gen);
        y = rand(gen);
        m = map(x, y);
        REQUIRE(reverse_map(m) == std::make_pair<uint16_t, uint16_t>(x, y));
        REQUIRE(m >= 0.0);
        REQUIRE(m <= 1.0);
    }

}
