#include "ready_set_bool.hpp"

namespace m42 {

    uint32_t interleave(uint16_t x, uint16_t y) {
        uint32_t result = 0;
        for (size_t i = 0; i < 16; ++i) {
            uint32_t bit_x = x & (1 << i);
            uint32_t bit_y = y & (1 << i);
            bit_x <<= i;
            bit_y <<= i + 1;
            result |= bit_x | bit_y;
        }
        return result;
    }

    double map(uint16_t x, uint16_t y) {
        uint32_t interleaved = interleave(x, y);
        return static_cast<double>(interleaved) / UINT32_MAX;
    }

    std::pair<uint16_t, uint16_t> deinterleave(uint32_t interleaved) {
        uint16_t x = 0;
        uint16_t y = 0;
        for (size_t i = 0; i < 16; ++i) {
            uint32_t bit_x = interleaved & (1 << (2 * i));
            uint32_t bit_y = interleaved & (1 << (2 * i + 1));
            bit_x >>= i;
            bit_y >>= i + 1;
            x |= bit_x;
            y |= bit_y;
        }
        return std::make_pair(x, y);
    }

    std::pair<uint16_t, uint16_t> reverse_map(double n) {
        auto interleaved = static_cast<uint32_t>(n * UINT32_MAX);
        return deinterleave(interleaved);
    }

}
