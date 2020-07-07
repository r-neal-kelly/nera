/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "nera/allocator.h"
#include "nera/pointer.h"

namespace nera {

    template <typename data_t>
    class manual_memory_t {
    public:
        pointer_t<data_t> pointer;

        manual_memory_t();
        manual_memory_t(const allocator_t& allocator, size_t count);

        manual_memory_t(const manual_memory_t<data_t>& to_copy) = default;
        manual_memory_t(manual_memory_t<data_t>&& to_move);
        manual_memory_t<data_t>& operator=(const manual_memory_t<data_t>& to_copy) = default;
        manual_memory_t<data_t>& operator=(manual_memory_t<data_t>&& to_move);
        ~manual_memory_t();

        bool hold(const allocator_t& allocator, size_t count);
        bool free(const allocator_t& allocator);
        size_t count();

        data_t& operator [](size_t index);
    };

    template <typename data_t>
    class auto_memory_t {
    public:
        pointer_t<data_t> pointer;
        const allocator_t& allocator;

        auto_memory_t();
        auto_memory_t(const allocator_t& allocator);
        auto_memory_t(const allocator_t& allocator, size_t count);

        auto_memory_t(const auto_memory_t<data_t>& to_copy);
        auto_memory_t(auto_memory_t<data_t>&& to_move);
        auto_memory_t<data_t>& operator=(const auto_memory_t<data_t>& to_copy);
        auto_memory_t<data_t>& operator=(auto_memory_t<data_t> && to_move);
        ~auto_memory_t();

        bool hold(size_t count);
        bool free();
        size_t count();

        data_t& operator [](size_t index);
    };

}

#include "nera/memory.inl"
