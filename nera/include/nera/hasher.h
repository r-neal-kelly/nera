/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "nera/pointer.h"

namespace nera {

    typedef size_t (*hash_f)(pointer_t<void>& pointer);

    class hasher_t {
    public:
        static const hasher_t& fnv_1a();

    public:
        const hash_f hash = nullptr;

        hasher_t(hash_f hash);

        size_t reduce(size_t hash, size_t limit) const;
        size_t bitwise_reduce(size_t hash, size_t power_of_two_limit) const;
        size_t modulus_reduce(size_t hash, size_t above_zero_limit) const;
        size_t hash_and_reduce(pointer_t<void>& pointer, size_t limit) const;
    };

}

#include "nera/hasher.inl"
