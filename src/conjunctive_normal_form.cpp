#include "ready_set_bool.hpp"

namespace m42 {

    std::string conjunctive_normal_form(const std::string &formula) {
        Proposition prop(formula);
        prop.to_conjunctive_normal_form();
        return prop.postfix_notation();
    }

}
