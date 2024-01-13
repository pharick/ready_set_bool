#include "ready_set_bool.hpp"

namespace m42 {

    std::set<std::set<int>> powerset(const std::set<int> &set) {
        std::set<std::set<int>> result;
        std::set<int> empty;
        result.insert(empty);
        for (auto &element : set) {
            std::set<std::set<int>> new_result;
            for (auto &subset : result) {
                std::set<int> new_subset(subset);
                new_subset.insert(element);
                new_result.insert(new_subset);
            }
            result.insert(new_result.begin(), new_result.end());
        }
        return result;
    }

}
