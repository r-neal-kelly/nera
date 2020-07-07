/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "stdint.h"

#include "nera/tuple.h"
#include "nera/hasher.h"
#include "nera/vector.h"

namespace nera {

    // we use linear search instead of linked lists.
    // we use uint8_t for indices in consideration of speed/space tradeoff.
    // the indices are searchable a word at a time, making larger maps more optimal.

    template <typename key_t, typename value_t>
    class hashmap_t {
    public:
        static constexpr size_t MIN_BUCKETS = 16;
        static constexpr float MIN_GROW_RATE = 1.0f;
        static constexpr float MIN_THRESHOLD = 0.5f;

        static constexpr float MAX_THRESHOLD = 1.0f;

        static constexpr size_t DEFAULT_BUCKETS = MIN_BUCKETS;
        static constexpr float DEFAULT_GROW_RATE = 2.0f;
        static constexpr float DEFAULT_THRESHOLD = 0.8f;

    public:
        const hasher_t& hasher;
        const allocator_t& allocator;
        manual_memory_t<tuple_t<key_t, value_t>> buckets;
        manual_memory_t<uint8_t> indices;
        size_t count = 0;
        float grow_rate = DEFAULT_GROW_RATE;
        float threshold = DEFAULT_THRESHOLD;

        hashmap_t();
        hashmap_t(const hasher_t& hasher);
        hashmap_t(const allocator_t& allocator);
        hashmap_t(size_t bucket_count);
        hashmap_t(const hasher_t& hasher, const allocator_t& allocator);
        hashmap_t(const hasher_t& hasher, size_t bucket_count);
        hashmap_t(const allocator_t& allocator, size_t bucket_count);
        hashmap_t(const hasher_t& hasher, const allocator_t& allocator, size_t bucket_count);
        ~hashmap_t();

        bool reserve(size_t bucket_count = DEFAULT_BUCKETS);
        bool energize(float grow_rate = DEFAULT_GROW_RATE, float threshold = DEFAULT_THRESHOLD);
        bool try_grow();
        bool grow();
        bool empty();

        size_t bucket(key_t& key);
        
        value_t& at(key_t& key);
        value_t& at(key_t&& key);
        value_t& operator [](key_t& key);
        value_t& operator [](key_t&& key);

        bool erase(key_t key);

        vector_t<key_t> keys();
        vector_t<value_t> values();
        vector_t<tuple_t<key_t, value_t>> entries();
        
        bool contains(key_t& key);
    };

}

#include "nera/hashmap.inl"
