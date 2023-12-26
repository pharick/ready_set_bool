#include "ready_set_bool.hpp"

namespace m42 {

    static void print_truth_table_header(const Proposition &prop) {
        for (auto c : prop.vars()) {
            std::cout << "| " << c.first << " ";
        }
        std::cout << "| = |" << std::endl;
        for (size_t i = 0; i < prop.vars().size(); ++i) {
            std::cout << "|---";
        }
        std::cout << "|---|" << std::endl;
    }

    static void print_truth_table_row(Proposition &prop, uint32_t values) {
        std::map<char, bool> v;
        size_t i = 0;
        for (auto c : prop.vars()) {
            v[c.first] = (values >> (prop.vars().size() - 1 - i++)) & 1;
            std::cout << "| " << v[c.first] << " ";
        }
        Proposition p(prop);
        p.substitute_values(v);
        std::cout << "| " << p.evaluate() << " |" << std::endl;
    }

    void print_truth_table(const std::string &formula) {
        Proposition prop(formula);
        uint32_t max_values = extend_bit(true, prop.vars().size());
        print_truth_table_header(prop);
        for (uint32_t values = 0; values <= max_values; ++values) {
            print_truth_table_row(prop, values);
        }
    }

}
