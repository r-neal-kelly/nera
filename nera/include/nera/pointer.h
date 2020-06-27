#pragma once

namespace nera {

    template <typename data_t>
    class pointer_t {
    public:
        data_t* data = nullptr;
        size_t bytes = 0;

        pointer_t();
        pointer_t(data_t* data, size_t bytes);
        ~pointer_t();

        operator pointer_t<void>&();
    };
}

#include "nera/pointer.inl"