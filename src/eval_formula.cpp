#include "ready_set_bool.hpp"

namespace m42 {

    bool eval_formula(const std::string &str) {
        return Proposition(str).evaluate();
    }

}
