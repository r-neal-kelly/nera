/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "nera/memory.h"
#include "nera/utils.h"

namespace nera {

    // manual_memory

    template <typename data_t>
    manual_memory_t<data_t>::manual_memory_t()
    {
    }

    template <typename data_t>
    manual_memory_t<data_t>::manual_memory_t(const allocator_t& allocator, size_t count)
    {
        hold(allocator, count);
        NERA_ASSERT(pointer.data != nullptr && pointer.bytes != 0);
    }

    template <typename data_t>
    manual_memory_t<data_t>::~manual_memory_t()
    {
        NERA_ASSERT(pointer.data == nullptr && pointer.bytes == 0);
    }

    template <typename data_t>
    bool manual_memory_t<data_t>::hold(const allocator_t& allocator, size_t count)
    {
        if (count > 0) {
            if (pointer.data != nullptr && pointer.bytes != 0) {
                return allocator.reallocate(pointer, count * sizeof(data_t));
            } else {
                return allocator.allocate(pointer, count * sizeof(data_t));
            }
        } else {
            return free(allocator);
        }
    }

    template <typename data_t>
    bool manual_memory_t<data_t>::free(const allocator_t& allocator)
    {
        return allocator.deallocate(pointer);
    }

    template <typename data_t>
    size_t manual_memory_t<data_t>::count()
    {
        return pointer.count();
    }

    template <typename data_t>
    data_t& manual_memory_t<data_t>::operator [](size_t index)
    {
        NERA_ASSERT(index < pointer.count());
        return pointer.data[index];
    }

    // auto_memory

    template <typename data_t>
    auto_memory_t<data_t>::auto_memory_t() :
        allocator(allocator_t::mallocator())
    {
    }

    template <typename data_t>
    auto_memory_t<data_t>::auto_memory_t(const allocator_t& allocator) :
        allocator(allocator)
    {
    }

    template <typename data_t>
    auto_memory_t<data_t>::auto_memory_t(const allocator_t& allocator, size_t count) :
        allocator(allocator)
    {
        hold(count);
        NERA_ASSERT(pointer.data != nullptr && pointer.bytes != 0);
    }
    
    template <typename data_t>
    auto_memory_t<data_t>::~auto_memory_t()
    {
        free();
    }

    template <typename data_t>
    bool auto_memory_t<data_t>::hold(size_t count)
    {
        if (count > 0) {
            if (pointer.data != nullptr && pointer.bytes != 0) {
                return allocator.reallocate(pointer, count * sizeof(data_t));
            } else {
                return allocator.allocate(pointer, count * sizeof(data_t));
            }
        } else {
            return free();
        }
    }

    template <typename data_t>
    bool auto_memory_t<data_t>::free()
    {
        return allocator.deallocate(pointer);
    }

    template <typename data_t>
    size_t auto_memory_t<data_t>::count()
    {
        return pointer.count();
    }

    template <typename data_t>
    data_t& auto_memory_t<data_t>::operator [](size_t index)
    {
        NERA_ASSERT(index < pointer.count());
        return pointer.data[index];
    }

}
