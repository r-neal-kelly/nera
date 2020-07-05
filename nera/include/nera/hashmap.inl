/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "nera/hashmap.h"

namespace nera {

    template <typename key_t, typename value_t>
    inline hashmap_t<key_t, value_t>::hashmap_t() :
        hasher(hasher_t::fnv_1a())
    {
    }

    template <typename key_t, typename value_t>
    inline hashmap_t<key_t, value_t>::hashmap_t(hasher_t hasher) :
        hasher(hasher)
    {
    }

    template <typename key_t, typename value_t>
    inline hashmap_t<key_t, value_t>::hashmap_t(size_t reserve_count) :
        keys(vector_t<key_t>(reserve_count)),
        values(vector_t<value_t>(reserve_count))
    {
    }

    template <typename key_t, typename value_t>
    inline hashmap_t<key_t, value_t>::hashmap_t(const allocator_t& allocator) :
        keys(vector_t<key_t>(allocator)),
        values(vector_t<value_t>(allocator))
    {
    }

    template <typename key_t, typename value_t>
    inline hashmap_t<key_t, value_t>::hashmap_t(size_t reserve_count, hasher_t hasher) :
        hasher(hasher),
        keys(vector_t<key_t>(reserve_count)),
        values(vector_t<value_t>(reserve_count))
    {
    }

    template <typename key_t, typename value_t>
    inline hashmap_t<key_t, value_t>::hashmap_t(const allocator_t& allocator, hasher_t hasher) :
        hasher(hasher),
        keys(vector_t<key_t>(allocator)),
        values(vector_t<value_t>(allocator))
    {
    }

    template <typename key_t, typename value_t>
    inline hashmap_t<key_t, value_t>::hashmap_t(const allocator_t& allocator, size_t reserve_count) :
        keys(vector_t<key_t>(allocator), reserve_count),
        values(vector_t<value_t>(allocator), reserve_count)
    {
    }

    template <typename key_t, typename value_t>
    inline hashmap_t<key_t, value_t>::hashmap_t(const allocator_t& allocator, size_t reserve_count, hasher_t hasher) :
        hasher(hasher),
        keys(vector_t<key_t>(allocator), reserve_count),
        values(vector_t<value_t>(allocator), reserve_count)
    {
    }

    template <typename key_t, typename value_t>
    inline hashmap_t<key_t, value_t>::hashmap_t::~hashmap_t()
    {
    }

}
