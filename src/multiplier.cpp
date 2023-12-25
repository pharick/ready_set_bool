#include "ready_set_bool.hpp"

uint32_t multiplier(uint32_t a, uint32_t b) {
    uint32_t product = 0;
    for (size_t i = 0; i < 32; ++i) {
        bool b_bit = (b >> i) & 1;
        uint32_t partial_product = a & extend_bit(b_bit);
        product = adder(product, partial_product << i);
    }
    return product;
}
