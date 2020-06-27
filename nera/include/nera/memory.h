#pragma once

#include "nera/allocator.h"
#include "nera/pointer.h"

namespace nera {

    template <typename data_t>
    class memory_t {
    public:
        pointer_t<data_t> pointer;
        const allocator_t& allocator;

        memory_t();
        memory_t(size_t count);
        memory_t(const allocator_t& allocator);
        memory_t(size_t count, const allocator_t& allocator);
        ~memory_t();

        bool hold(size_t count);
        bool free();
        bool zero();
    };

}

#include "nera/memory.inl"
