#include "ready_set_bool.hpp"

uint32_t extend_bit(bool bit, size_t n) {
    uint32_t result = 0;
    for (size_t i = 0; i < n; ++i) {
        result |= bit << i;
    }
    return result;
}

void pop_two(std::stack<bool> &stack, bool &a, bool &b) {
    if (stack.size() < 2)
        throw std::runtime_error("Invalid formula");
    b = stack.top();
    stack.pop();
    a = stack.top();
    stack.pop();
}
