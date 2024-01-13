#include "ready_set_bool.hpp"

namespace m42 {

    std::set<int> eval_set(const std::string &str, std::map<char, std::set<int>> &set_map) {
        return Proposition(str).evaluate_sets(set_map);
    }

}
