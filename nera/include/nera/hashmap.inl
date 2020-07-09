/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "nera/utils.h"
#include "nera/pointer.h"
#include "nera/hashmap.h"

namespace nera {

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

        size_t old_bucket_count = buckets.count();
        if (bucket_count > old_bucket_count) {
            NERA_ASSERT(buckets.hold(allocator, bucket_count) && indices.hold(allocator, bucket_count));
            if (!allocator.initializes_to_zero) {
                pointer_t<uint8_t> pointer(indices.pointer.data + old_bucket_count, bucket_count - old_bucket_count);
                NERA_ASSERT(allocator_t::zero(pointer));
            }
            return true;
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
            grow();
            return true;
        } else {
            return false;
        }
    }

    template <typename key_t, typename value_t>
    inline void hashmap_t<key_t, value_t>::grow()
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
                size_t new_bucket_index = index_of(old_bucket.first);
                NERA_ASSERT(new_bucket_index < MAX_SIZE_T);
                tuple_t<key_t, value_t>& new_bucket = buckets[new_bucket_index];
                new_bucket.first = old_bucket.first;
                new_bucket.second = old_bucket.second;
                indices[new_bucket_index] = ~static_cast<uint8_t>(0);
            }
        }

        NERA_ASSERT(old_buckets.free(allocator) && old_indices.free(allocator));
    }

    template <typename key_t, typename value_t>
    inline void hashmap_t<key_t, value_t>::empty()
    {
        NERA_ASSERT(allocator_t::zero(indices.pointer));
        count = 0;
    }

    template <typename key_t, typename value_t>
    inline bool hashmap_t<key_t, value_t>::is_empty()
    {
        return count == 0;
    }

    template <typename key_t, typename value_t>
    inline size_t hashmap_t<key_t, value_t>::index_of(key_t& key)
    {
        NERA_ASSERT(try_grow() == false); // should be called before this scope
        size_t index = hasher.hash_and_reduce(pointer_t<key_t>(&key, sizeof(key)), buckets.count());
        NERA_ASSERT(index != MAX_SIZE_T);
        size_t indices_count = indices.count();
        size_t indices_iterated = 0;

        // may want to consume by word to speed things up
        for (; index < indices_count; index += 1, indices_iterated += 1) {
            if (indices[index] == 0) {
                buckets[index].first = key;
                indices[index] = ~static_cast<uint8_t>(0);
                count += 1;
                return index;
            } else if (buckets[index].first == key) {
                return index;
            }
        }
        index = 0;
        for (; indices_iterated < indices_count; index += 1, indices_iterated += 1) {
            if (indices[index] == 0) {
                buckets[index].first = key;
                indices[index] = ~static_cast<uint8_t>(0);
                count += 1;
                return index;
            } else if (buckets[index].first == key) {
                return index;
            }
        }

        return MAX_SIZE_T;
    }

    template <typename key_t, typename value_t>
    inline size_t hashmap_t<key_t, value_t>::index_of_used(key_t& key)
    {
        size_t index = hasher.hash_and_reduce(pointer_t<key_t>(&key), buckets.count());
        NERA_ASSERT(index != MAX_SIZE_T);
        size_t indices_count = indices.count();
        size_t indices_iterated = 0;

        // may want to consume by word to speed things up
        for (; index < indices_count; index += 1, indices_iterated += 1) {
            if (indices[index] == 0) {
                return MAX_SIZE_T;
            } else if (buckets[index].first == key) {
                return index;
            }
        }
        index = 0;
        for (; indices_iterated < indices_count; index += 1, indices_iterated += 1) {
            if (indices[index] == 0) {
                return MAX_SIZE_T;
            } else if (buckets[index].first == key) {
                return index;
            }
        }

        return MAX_SIZE_T;
    }

    template <typename key_t, typename value_t>
    inline value_t& hashmap_t<key_t, value_t>::at(key_t& key)
    {
        try_grow();
        size_t bucket_index = index_of(key);
        NERA_ASSERT(bucket_index < MAX_SIZE_T);
        return buckets[bucket_index].second;
    }

    template <typename key_t, typename value_t>
    inline value_t& hashmap_t<key_t, value_t>::at(key_t&& key)
    {
        return at(key);
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

    template <typename key_t, typename value_t>
    inline bool hashmap_t<key_t, value_t>::erase(key_t& key)
    {
        size_t index = index_of_used(key);
        if (index < MAX_SIZE_T) {
            indices[index] = 0;
            return true;
        } else {
            return false;
        }
    }

    template <typename key_t, typename value_t>
    inline bool hashmap_t<key_t, value_t>::erase(key_t&& key)
    {
        return erase(key);
    }

    template <typename key_t, typename value_t>
    inline bool hashmap_t<key_t, value_t>::has_key(key_t& key)
    {
        return index_of_used(key) != MAX_SIZE_T;
    }

    template <typename key_t, typename value_t>
    inline bool hashmap_t<key_t, value_t>::has_key(key_t&& key)
    {
        return has_key(key);
    }

    template <typename key_t, typename value_t>
    inline vector_t<key_t> hashmap_t<key_t, value_t>::keys(const allocator_t& allocator)
    {
        vector_t<key_t> keys_copy(allocator, count);

        for (size_t idx = 0, count = buckets.count(); idx < count; idx += 1) {
            if (indices[idx] != 0) {
                keys_copy.push(buckets[idx].first);
            }
        }

        return keys_copy;
    }

    template <typename key_t, typename value_t>
    inline vector_t<value_t> hashmap_t<key_t, value_t>::values(const allocator_t& allocator)
    {
        vector_t<key_t> values_copy(allocator, count);

        for (size_t idx = 0, count = buckets.count(); idx < count; idx += 1) {
            if (indices[idx] != 0) {
                values_copy.push(buckets[idx].second);
            }
        }

        return values_copy;
    }

    template <typename key_t, typename value_t>
    inline vector_t<tuple_t<key_t, value_t>> hashmap_t<key_t, value_t>::entries(const allocator_t& allocator)
    {
        vector_t<tuple_t<key_t, value_t>> entries_copy(allocator, count);

        for (size_t idx = 0, count = buckets.count(); idx < count; idx += 1) {
            if (indices[idx] != 0) {
                entries_copy.push(buckets[idx]);
            }
        }

        return entries_copy;
    }

    template <typename key_t, typename value_t>
    inline vector_t<key_t> hashmap_t<key_t, value_t>::keys()
    {
        return keys(allocator);
    }

    template <typename key_t, typename value_t>
    inline vector_t<value_t> hashmap_t<key_t, value_t>::values()
    {
        return values(allocator);
    }

    template <typename key_t, typename value_t>
    inline vector_t<tuple_t<key_t, value_t>> hashmap_t<key_t, value_t>::entries()
    {
        return entries(allocator);
    }

}
