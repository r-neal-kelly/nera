#pragma once

#include "nera/utils.h"
#include "nera/vector.h"

namespace nera {

    template <typename data_t>
    vector_t<data_t>::vector_t()
    {
    }

    template <typename data_t>
    vector_t<data_t>::vector_t(size_t reserve_count) :
        memory(reserve_count)
    {
    }

    template <typename data_t>
    vector_t<data_t>::vector_t(const allocator_t& allocator) :
        memory(allocator)
    {
    }

    template <typename data_t>
    vector_t<data_t>::vector_t(size_t reserve_count, const allocator_t& allocator) :
        memory(reserve_count, allocator)
    {
    }

    template <typename data_t>
    vector_t<data_t>::~vector_t()
    {
        memory.free();
        count = 0;
        grow_rate = 0.0f;
    }

    template <typename data_t>
    bool vector_t<data_t>::reserve(size_t reserve_count)
    {
        return memory.hold(reserve_count);
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
    bool vector_t<data_t>::prepare()
    {
        if (count + 1 > memory.count) {
            size_t new_reserve_count = static_cast<size_t>(memory.count * grow_rate);
            if (new_reserve_count <= memory.count) {
                new_reserve_count = memory.count + 1;
            }
            return memory.hold(new_reserve_count);
        } else {
            return true;
        }
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
    bool vector_t<data_t>::push(data_t element)
    {
        if (prepare()) {
            memory[count] = element;
            count += 1;
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
    bool vector_t<data_t>::pop(data_t& out_element)
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
    size_t vector_t<data_t>::find(data_t& element)
    {
        for (size_t index = 0; index < count; index += 1) {
            if (memory[index] == element) {
                return index;
            }
        }
        return ~static_cast<size_t>(0);
    }

    template <typename data_t>
    data_t& vector_t<data_t>::operator [](size_t index)
    {
        NERA_ASSERT(index < count);
        return memory[index];
    }

}
