#include "ready_set_bool.hpp"

/**
 * @brief Evaluates a propositional formula in reverse Polish notation.
 * @param str Formula in reverse Polish notation.
 * @return Result of the evaluation.
 */
bool eval_formula(const std::string &str) {
    std::stack<bool> stack;
    bool a, b;
    for (char c : str) {
        switch (c) {
            case '0':
                stack.push(false);
                break;
            case '1':
                stack.push(true);
                break;
            case '!':
                if (stack.empty())
                    throw std::runtime_error("Invalid formula");
                stack.top() = !stack.top();
                break;
            case '&':
                pop_two(stack, a, b);
                stack.push(a && b);
                break;
            case '|':
                pop_two(stack, a, b);
                stack.push(a || b);
                break;
            case '^':
                pop_two(stack, a, b);
                stack.push(a != b);
                break;
            case '>':
                pop_two(stack, a, b);
                stack.push(!a || b);
                break;
            case '=':
                pop_two(stack, a, b);
                stack.push(a == b);
                break;
            default:
                throw std::runtime_error("Invalid formula");
        }
    }
    if (stack.size() != 1)
        throw std::runtime_error("Invalid formula");
    return stack.top();
}
