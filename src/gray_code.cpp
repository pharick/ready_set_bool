#include "ready_set_bool.hpp"

namespace m42 {

    uint32_t gray_code(uint32_t n) {
        return n ^ (n >> 1);
    }

}
