/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "nera/allocator.h"
#include "nera/pointer.h"

namespace nera {

    template <typename data_t>
    class memory_t {
    public:
        pointer_t<data_t> pointer;
        const allocator_t& allocator;
        size_t count = 0;

        memory_t();
        memory_t(size_t count);
        memory_t(const allocator_t& allocator);
        memory_t(const allocator_t& allocator, size_t count);
        ~memory_t();

        bool hold(size_t count);
        bool free();

        data_t& operator [](size_t index);
    };

}

#include "nera/memory.inl"
