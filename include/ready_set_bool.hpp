#ifndef READY_SET_BOOL_READY_SET_BOOL_HPP
#define READY_SET_BOOL_READY_SET_BOOL_HPP

#include <cstdint>
#include <cstddef>
#include <string>
#include <stack>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <set>
#include <regex>
#include <sstream>

uint32_t extend_bit(bool bit, size_t n = 32);
void pop_two(std::stack<bool> &stack, bool &a, bool &b);

void half_adder(bool a, bool b, bool& sum, bool& carry);
void full_adder(bool a, bool b, bool c, bool& sum, bool& carry);
uint32_t adder(uint32_t a, uint32_t b);

uint32_t multiplier(uint32_t a, uint32_t b);

uint32_t gray_code(uint32_t n);

bool eval_formula(const std::string &str);

void print_truth_table(const std::string &formula);

#endif //READY_SET_BOOL_READY_SET_BOOL_HPP
