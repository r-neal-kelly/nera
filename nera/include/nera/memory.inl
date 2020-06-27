#pragma once

#include "nera/memory.h"

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
                return allocator.reallocate(pointer, count * sizeof(data_t));
            } else {
                return allocator.allocate(pointer, count * sizeof(data_t));
            }
        } else {
            return false;
        }
    }

    template <typename data_t>
    bool memory_t<data_t>::free()
    {
        return allocator.deallocate(pointer);
    }

    template <typename data_t>
    bool memory_t<data_t>::zero()
    {
        return allocator_t::zero(pointer);
    }

}
