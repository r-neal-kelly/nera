#pragma once

#include "nera/memory.h"
#include "nera/utils.h"

namespace nera {

    template <typename data_t>
    memory_t<data_t>::memory_t() :
        allocator(allocator_t::mallocator())
    {
    }

    template <typename data_t>
    memory_t<data_t>::memory_t(size_t count) :
        allocator(allocator_t::mallocator())
    {
        hold(count);
    }

    template <typename data_t>
    memory_t<data_t>::memory_t(const allocator_t& allocator) :
        allocator(allocator)
    {
    }

    template <typename data_t>
    memory_t<data_t>::memory_t(size_t count, const allocator_t& allocator) :
        allocator(allocator)
    {
        hold(count);
    }

    template <typename data_t>
    memory_t<data_t>::~memory_t()
    {
        free();
    }

    template <typename data_t>
    bool memory_t<data_t>::hold(size_t count)
    {
        if (count > 0) {
            if (pointer.data != nullptr && pointer.bytes != 0) {
                if (allocator.reallocate(pointer, count * sizeof(data_t))) {
                    this->count = count;
                    return true;
                } else {
                    return false;
                }
            } else {
                if (allocator.allocate(pointer, count * sizeof(data_t))) {
                    this->count = count;
                    return true;
                } else {
                    return false;
                }
            }
        } else {
            // maybe shouldn't free like this?
            return free();
        }
    }

    template <typename data_t>
    bool memory_t<data_t>::free()
    {
        if (allocator.deallocate(pointer)) {
            this->count = 0;
            return true;
        } else {
            return false;
        }
    }

    template <typename data_t>
    data_t& memory_t<data_t>::operator [](size_t index)
    {
        NERA_ASSERT(index < count);
        return pointer.data[index];
    }

}
