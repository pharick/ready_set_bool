#include "ready_set_bool.hpp"

namespace m42 {

    std::string negation_normal_form(const std::string &formula) {
        Proposition prop(formula);
        prop.to_negation_normal_form();
        return prop.postfix_notation();
    }

}
