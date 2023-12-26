#include "ready_set_bool.hpp"

namespace m42 {

    void half_adder(bool a, bool b, bool &sum, bool &carry) {
        sum = a ^ b;
        carry = a & b;
    }

    void full_adder(bool a, bool b, bool c, bool &sum, bool &carry) {
        bool xor1, and2;
        half_adder(a, b, xor1, and2);
        bool and1;
        half_adder(xor1, c, sum, and1);
        carry = and1 | and2;
    }

    uint32_t adder(uint32_t a, uint32_t b) {
        bool sum_bit, carry_bit;
        uint32_t sum = 0;
        uint32_t carry = 0;
        for (size_t i = 0; i < 32; ++i) {
            bool a_bit = (a >> i) & 1;
            bool b_bit = (b >> i) & 1;
            full_adder(a_bit, b_bit, carry, sum_bit, carry_bit);
            sum |= (sum_bit << i);
            carry = carry_bit;
        }
        return sum;
    }

}
