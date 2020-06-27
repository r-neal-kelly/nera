#pragma once

#include "nera/memory.h"

namespace nera {

    template <typename data_t>
    class vector_t {
    public:
        memory_t<data_t> memory;
        size_t count;
        float grow_rate;

        vector_t();
        ~vector_t();

        bool reserve(size_t count);
        void push(data_t element);
        void push_at(data_t element, size_t index);
        data_t pop();
        data_t pop_at(size_t index);
        data_t& at(size_t index);
        data_t* point(size_t index);
        size_t find_left(data_t& element);
        size_t find_right(data_t& element);
    };

}

#include "nera/vector.inl"
