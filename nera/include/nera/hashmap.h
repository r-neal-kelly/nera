/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "nera/hasher.h"
#include "nera/vector.h"

namespace nera {

    template <typename key_t, typename value_t>
    class hashmap_t {
    public:
        hasher_t hasher;
        vector_t<key_t> keys;
        vector_t<value_t> values;

        hashmap_t();
        hashmap_t(hasher_t hasher);
        hashmap_t(size_t reserve_count);
        hashmap_t(const allocator_t& allocator);
        hashmap_t(size_t reserve_count, hasher_t hasher);
        hashmap_t(const allocator_t& allocator, hasher_t hasher);
        hashmap_t(const allocator_t& allocator, size_t reserve_count);
        hashmap_t(const allocator_t& allocator, size_t reserve_count, hasher_t hasher);
        ~hashmap_t();

        value_t& operator [](key_t key);
    };

}

#include "nera/hashmap.inl"
