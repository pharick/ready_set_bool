#include "ready_set_bool.hpp"

static std::set<char> get_vars(const std::string &formula) {
    std::set<char> vars;
    for (char c : formula) {
        char c_upper = static_cast<char>(std::toupper(c));
        if (std::isalpha(c_upper)) {
            vars.insert(c_upper);
        }
    }
    return vars;
}

static void print_truth_table_header(const std::set<char> &vars) {
    for (char c : vars) {
        std::cout << "| " << c << " ";
    }
    std::cout << "| = |" << std::endl;
    for (size_t i = 0; i < vars.size(); ++i) {
        std::cout << "|---";
    }
    std::cout << "|---|" << std::endl;
}

static std::string substitute_values(const std::string &formula, const std::set<char> &vars, uint32_t values) {
    std::string substituted = formula;
    size_t i = 0;
    for (char c : vars) {
        substituted = std::regex_replace(
                substituted,
                std::regex("[" + std::string(1, c) + std::string(1, static_cast<char>(std::tolower(c))) + "]"),
                std::to_string((values >> (vars.size() - 1 - i++)) & 1)
        );
    }
    return substituted;
}

static void print_truth_table_row(const std::string &formula, const std::set<char> &vars, uint32_t values) {
    for (size_t i = 0; i < vars.size(); ++i) {
        std::cout << "| " << ((values >> (vars.size() - i - 1)) & 1) << " ";
    }
    std::cout << "| " << eval_formula(substitute_values(formula, vars, values)) << " |" << std::endl;
}

void print_truth_table(const std::string &formula) {
    std::set<char> vars = get_vars(formula);
    uint32_t max_values = extend_bit(true, vars.size());
    print_truth_table_header(vars);
    for (uint32_t values = 0; values <= max_values; ++values) {
        print_truth_table_row(formula, vars, values);
    }
}
