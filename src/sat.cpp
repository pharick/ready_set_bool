#include "ready_set_bool.hpp"

namespace m42 {

    bool sat(const std::string &formula) {
        return Proposition(formula).is_satisfiable();
    }

}
