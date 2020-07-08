/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

namespace nera {

    template <typename data_t>
    class pointer_t {
    public:
        data_t* data = nullptr;
        size_t bytes = 0;

        pointer_t();
        pointer_t(data_t* data, size_t bytes);
        pointer_t(data_t* data);

        pointer_t(const pointer_t<data_t>& to_copy);
        pointer_t(pointer_t<data_t>&& to_move) noexcept;
        pointer_t<data_t>& operator=(const pointer_t<data_t>& to_copy);
        pointer_t<data_t>& operator=(pointer_t<data_t>&& to_move) noexcept;
        ~pointer_t();

        size_t count();

        operator pointer_t<void>* ();
        operator data_t* ();
    };

    template <>
    class pointer_t<void> {
    public:
        void* data = nullptr;
        size_t bytes = 0;

        pointer_t();
        pointer_t(void* data, size_t bytes);
        pointer_t(pointer_t<void>&& to_move);
        ~pointer_t();

        operator pointer_t<void>* ();
    };

}

#include "nera/pointer.inl"
