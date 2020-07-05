/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "nera/memory.h"

namespace nera {

    template <typename data_t>
    class vector_t {
    public:
        memory_t<data_t> memory;
        float grow_rate = 1.7f;
        size_t count = 0;

        vector_t();
        vector_t(size_t reserve_count);
        vector_t(const allocator_t& allocator);
        vector_t(const allocator_t& allocator, size_t reserve_count);
        ~vector_t();

        bool reserve(size_t count);
        bool energize(float grow_rate);
        bool prepare();
        data_t& at(size_t index);
        data_t* point(size_t index);
        bool push(data_t in_element);
        bool push(data_t& in_element);
        bool pull(data_t& out_element);
        bool pop();
        size_t find(data_t& element);

        data_t& operator [](size_t index);
    };

}

#include "nera/vector.inl"
