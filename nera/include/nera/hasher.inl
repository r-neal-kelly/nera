/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "nera/utils.h"
#include "nera/hasher.h"

namespace nera {

    inline hasher_t::hasher_t(hash_f hash) :
        hash(hash)
    {
    }

    inline size_t hasher_t::reduce(size_t hash, size_t limit) const
    {
        if (is_power_of_two(limit)) {
            return bitwise_reduce(hash, limit);
        } else {
            return modulus_reduce(hash, limit);
        }
    }

    inline size_t hasher_t::bitwise_reduce(size_t hash, size_t power_of_two_limit) const
    {
        if (power_of_two_limit > 0) {
            return hash & (power_of_two_limit - 1);
        } else {
            return MAX_SIZE_T;
        }
    }

    inline size_t hasher_t::modulus_reduce(size_t hash, size_t above_zero_limit) const
    {
        if (above_zero_limit > 0) {
            return hash % above_zero_limit;
        } else {
            return MAX_SIZE_T;
        }
    }

    inline size_t hasher_t::hash_and_reduce(pointer_t<void>& pointer, size_t limit) const
    {
        return reduce(hash(pointer), limit);
    }

}
