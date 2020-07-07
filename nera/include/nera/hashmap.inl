/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "nera/utils.h"
#include "nera/pointer.h"
#include "nera/hashmap.h"

namespace nera {

    // might want to assert on all reserves?

    template <typename key_t, typename value_t>
    inline hashmap_t<key_t, value_t>::hashmap_t() :
        hasher(hasher_t::fnv_1a()), allocator(allocator_t::mallocator())
    {
        reserve(DEFAULT_BUCKETS);
    }

    template <typename key_t, typename value_t>
    inline hashmap_t<key_t, value_t>::hashmap_t(const hasher_t& hasher) :
        hasher(hasher), allocator(allocator_t::mallocator())
    {
        reserve(DEFAULT_BUCKETS);
    }

    template <typename key_t, typename value_t>
    inline hashmap_t<key_t, value_t>::hashmap_t(const allocator_t& allocator) :
        hasher(hasher_t::fnv_1a()), allocator(allocator)
    {
        reserve(DEFAULT_BUCKETS);
    }

    template <typename key_t, typename value_t>
    inline hashmap_t<key_t, value_t>::hashmap_t(size_t bucket_count) :
        hasher(hasher_t::fnv_1a()), allocator(allocator_t::mallocator())
    {
        reserve(bucket_count);
    }

    template <typename key_t, typename value_t>
    inline hashmap_t<key_t, value_t>::hashmap_t(const hasher_t& hasher, const allocator_t& allocator) :
        hasher(hasher), allocator(allocator)
    {
        reserve(DEFAULT_BUCKETS);
    }
    
    template <typename key_t, typename value_t>
    inline hashmap_t<key_t, value_t>::hashmap_t(const hasher_t& hasher, size_t bucket_count) :
        hasher(hasher), allocator(allocator_t::mallocator())
    {
        reserve(bucket_count);
    }

    template <typename key_t, typename value_t>
    inline hashmap_t<key_t, value_t>::hashmap_t(const allocator_t& allocator, size_t bucket_count) :
        hasher(hasher_t::fnv_1a()), allocator(allocator)
    {
        reserve(bucket_count);
    }
    
    template <typename key_t, typename value_t>
    inline hashmap_t<key_t, value_t>::hashmap_t(const hasher_t& hasher, const allocator_t& allocator, size_t bucket_count) :
        hasher(hasher), allocator(allocator)
    {
        reserve(bucket_count);
    }

    template <typename key_t, typename value_t>
    inline hashmap_t<key_t, value_t>::hashmap_t::~hashmap_t()
    {
        buckets.free(allocator);
        indices.free(allocator);
        count = 0;
        grow_rate = DEFAULT_GROW_RATE;
        threshold = DEFAULT_THRESHOLD;
    }

    template <typename key_t, typename value_t>
    inline bool hashmap_t<key_t, value_t>::reserve(size_t bucket_count)
    {
        if (bucket_count < MIN_BUCKETS) {
            bucket_count = MIN_BUCKETS;
        }

        size_t old_indices_count = indices.count();
        if (bucket_count > old_indices_count) {
            if (buckets.hold(allocator, bucket_count) && indices.hold(allocator, bucket_count)) {
                if (allocator.initializes_to_zero) {
                    return true;
                } else {
                    pointer_t<uint8_t> pointer(indices.pointer.data + old_indices_count, bucket_count - old_indices_count);
                    return allocator_t::zero(pointer);
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    template <typename key_t, typename value_t>
    inline bool hashmap_t<key_t, value_t>::energize(float grow_rate, float threshold)
    {
        if (grow_rate >= MIN_GROW_RATE && threshold >= MIN_THRESHOLD && threshold <= MAX_THRESHOLD) {
            this->grow_rate = grow_rate;
            this->threshold = threshold;
            return true;
        } else {
            return false;
        }
    }

    template <typename key_t, typename value_t>
    inline bool hashmap_t<key_t, value_t>::try_grow()
    {
        if (count / indices.count() >= threshold) {
            NERA_ASSERT(grow());
            return true;
        } else {
            return false;
        }
    }

    template <typename key_t, typename value_t>
    inline bool hashmap_t<key_t, value_t>::grow()
    {
        manual_memory_t<tuple_t<key_t, value_t>> old_buckets = buckets;
        manual_memory_t<uint8_t> old_indices = indices;

        size_t old_indices_count = indices.count();
        size_t new_reserve_count =
            static_cast<size_t>(old_indices_count * static_cast<double>(grow_rate));
        if (new_reserve_count <= old_indices_count) {
            new_reserve_count = old_indices_count + 1;
        }

        buckets = manual_memory_t<tuple_t<key_t, value_t>>();
        indices = manual_memory_t<uint8_t>();
        reserve(new_reserve_count);
        count = 0;

        // may want to consume by word instead, especially if threshold is low.
        for (size_t idx = 0; idx < old_indices_count; idx += 1) {
            if (old_indices[idx] != 0) {
                tuple_t<key_t, value_t>& old_bucket = old_buckets[idx];
                size_t new_bucket = bucket(old_bucket.first);
                NERA_ASSERT(new_bucket < MAX_SIZE_T);
                buckets[new_bucket].second = old_bucket.second;
            }
        }

        return old_buckets.free(allocator) && old_indices.free(allocator);
    }

    template <typename key_t, typename value_t>
    inline bool hashmap_t<key_t, value_t>::empty()
    {
        count = 0;
        return allocator_t::zero(indices.pointer);
    }

    template <typename key_t, typename value_t>
    inline size_t hashmap_t<key_t, value_t>::bucket(key_t& key)
    {
        NERA_ASSERT(try_grow() == false); // remove for release
        pointer_t<key_t> key_pointer(&key, sizeof(key_t));
        size_t bucket = hasher.hash_and_reduce(key_pointer, indices.count());
        NERA_ASSERT(bucket != MAX_SIZE_T);

        if (indices[bucket] == 0) {
            buckets[bucket].first = key;
            indices[bucket] = ~static_cast<uint8_t>(0);
            count += 1;
            return bucket;
        } else if (buckets[bucket].first == key) {
            return bucket;
        } else {
            size_t indices_count = indices.count();
            size_t indices_iterated = 1;
            bucket += 1;

            // may want to consume by word to speed things up
            for (; bucket < indices_count; bucket += 1, indices_iterated += 1) {
                if (indices[bucket] == 0) {
                    return bucket;
                }
            }
            bucket = 0;
            for (; indices_iterated < indices_count; bucket += 1, indices_iterated += 1) {
                if (indices[bucket] == 0) {
                    return bucket;
                }
            }

            return MAX_SIZE_T;
        }
    }

    template <typename key_t, typename value_t>
    inline value_t& hashmap_t<key_t, value_t>::at(key_t& key)
    {
        try_grow();
        size_t bucket_index = bucket(key);
        NERA_ASSERT(bucket_index < indices.count());
        return buckets[bucket_index].second;
    }

    template <typename key_t, typename value_t>
    inline value_t& hashmap_t<key_t, value_t>::at(key_t&& key)
    {
        try_grow();
        size_t bucket_index = bucket(key);
        NERA_ASSERT(bucket_index < indices.count());
        return buckets[bucket_index].second;
    }

    template <typename key_t, typename value_t>
    inline value_t& hashmap_t<key_t, value_t>::operator [](key_t& key)
    {
        return at(key);
    }

    template <typename key_t, typename value_t>
    inline value_t& hashmap_t<key_t, value_t>::operator [](key_t&& key)
    {
        return at(key);
    }

}
