#ifndef READY_SET_BOOL_READY_SET_BOOL_HPP
#define READY_SET_BOOL_READY_SET_BOOL_HPP

#include <cstdint>
#include <cstddef>
#include <string>
#include <stack>
#include <iostream>
#include <cctype>
#include <queue>
#include <map>
#include <utility>
#include <sstream>

#include "Proposition.hpp"

namespace m42 {

    /* Common util functions */
    uint32_t extend_bit(bool bit, size_t n = 32);

    template<typename T>
    void pop_two(std::stack<T> &stack, T &a, T &b) {
        b = stack.top();
        stack.pop();
        a = stack.top();
        stack.pop();
    }

    /* Adder */
    void half_adder(bool a, bool b, bool &sum, bool &carry);
    void full_adder(bool a, bool b, bool c, bool &sum, bool &carry);
    uint32_t adder(uint32_t a, uint32_t b);

    /* Multiplier */
    uint32_t multiplier(uint32_t a, uint32_t b);

    /* Gray code */
    uint32_t gray_code(uint32_t n);

    /* Eval formula */
    bool eval_formula(const std::string &str);

    /* Print truth table */
    void print_truth_table(const std::string &formula);

    /* Negation normal form */
    std::string negation_normal_form(const std::string &formula);

}

#endif //READY_SET_BOOL_READY_SET_BOOL_HPP
