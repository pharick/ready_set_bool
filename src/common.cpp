#include "ready_set_bool.hpp"

namespace m42 {

    uint32_t extend_bit(bool bit, size_t n) {
        uint32_t result = 0;
        for (size_t i = 0; i < n; ++i) {
            result |= bit << i;
        }
        return result;
    }

}
