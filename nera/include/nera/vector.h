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
        vector_t(size_t reserve_count, const allocator_t& allocator);
        ~vector_t();

        bool reserve(size_t count);
        bool energize(float grow_rate);
        bool prepare();
        data_t& at(size_t index);
        data_t* point(size_t index);
        bool push(data_t element);
        bool pop();
        bool pop(data_t& out_element);
        size_t find(data_t& element);

        data_t& operator [](size_t index);
    };

}

#include "nera/vector.inl"
