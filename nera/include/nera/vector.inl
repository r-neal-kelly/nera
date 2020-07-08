/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include <utility>

#include "nera/utils.h"
#include "nera/vector.h"

namespace nera {

    template <typename data_t>
    vector_t<data_t>::vector_t() :
        memory(allocator_t::mallocator())
    {
    }

    template <typename data_t>
    vector_t<data_t>::vector_t(size_t reserve_count) :
        memory(allocator_t::mallocator(), reserve_count)
    {
    }

    template <typename data_t>
    vector_t<data_t>::vector_t(const allocator_t& allocator) :
        memory(allocator)
    {
    }

    template <typename data_t>
    vector_t<data_t>::vector_t(const allocator_t& allocator, size_t reserve_count) :
        memory(allocator, reserve_count)
    {
    }

    /*template <typename data_t>
    vector_t<data_t>::vector_t(const vector_t<data_t>& from)
    {
    }*/

    template <typename data_t>
    vector_t<data_t>::vector_t(vector_t<data_t>&& to_move) :
        memory(std::move(to_move.memory)),
        count(std::exchange(to_move.count, 0)),
        grow_rate(std::exchange(to_move.grow_rate, DEFAULT_GROW_RATE))
    {
    }

    template <typename data_t>
    vector_t<data_t>::~vector_t()
    {
        memory.free();
        grow_rate = 1.7f;
        count = 0;
    }

    template <typename data_t>
    bool vector_t<data_t>::reserve(size_t reserve_count)
    {
        if (reserve_count > memory.count()) {
            return memory.hold(reserve_count);
        } else {
            return false;
        }
    }

    template <typename data_t>
    bool vector_t<data_t>::energize(float grow_rate)
    {
        if (grow_rate >= 1.0f) {
            this->grow_rate = grow_rate;
            return true;
        } else {
            return false;
        }
    }

    template <typename data_t>
    bool vector_t<data_t>::grow()
    {
        size_t memory_count = memory.count();
        size_t new_reserve_count =
            static_cast<size_t>(memory_count * static_cast<double>(grow_rate));
        if (new_reserve_count <= memory_count) {
            new_reserve_count = memory_count + 1;
        }
        return memory.hold(new_reserve_count);
    }

    template <typename data_t>
    data_t& vector_t<data_t>::at(size_t index)
    {
        NERA_ASSERT(index < count);
        return memory[index];
    }

    template <typename data_t>
    data_t* vector_t<data_t>::point(size_t index)
    {
        NERA_ASSERT(index < count);
        return &memory[index];
    }

    template <typename data_t>
    bool vector_t<data_t>::push(data_t& in_element)
    {
        if (count < memory.count() || grow()) {
            memory[count] = in_element;
            count += 1;
            return true;
        } else {
            return false;
        }
    }

    template <typename data_t>
    bool vector_t<data_t>::push(data_t&& in_element)
    {
        return push(in_element);
    }

    template <typename data_t>
    bool vector_t<data_t>::pull(data_t& out_element)
    {
        if (count > 0) {
            count -= 1;
            out_element = memory[count];
            return true;
        } else {
            return false;
        }
    }

    template <typename data_t>
    bool vector_t<data_t>::pop()
    {
        if (count > 0) {
            count -= 1;
            return true;
        } else {
            return false;
        }
    }

    template <typename data_t>
    size_t vector_t<data_t>::find(data_t& element)
    {
        for (size_t index = 0; index < count; index += 1) {
            if (memory[index] == element) {
                return index;
            }
        }
        return MAX_SIZE_T;
    }

    template <typename data_t>
    data_t& vector_t<data_t>::operator [](size_t index)
    {
        NERA_ASSERT(index < count);
        return memory[index];
    }

}
