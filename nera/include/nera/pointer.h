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
        pointer_t(data_t& data);

        pointer_t(const pointer_t<data_t>& other);

        pointer_t(pointer_t<data_t>&& other) noexcept;
        pointer_t(pointer_t<void>&& other) noexcept;

        pointer_t<data_t>& operator=(const pointer_t<data_t>& other);

        pointer_t<data_t>& operator=(pointer_t<data_t>&& other) noexcept;

        ~pointer_t();

        size_t count();

        operator pointer_t<void>& ();

        template <typename data_t1, typename data_t2>
        friend bool operator ==(const pointer_t<data_t1>& pointer_a,
                                const pointer_t<data_t2>& pointer_b);
        template <typename data_t1, typename data_t2>
        friend bool operator !=(const pointer_t<data_t1>& pointer_a,
                                const pointer_t<data_t2>& pointer_b);
    };

    template <>
    class pointer_t<void> {
    public:
        void* data = nullptr;
        size_t bytes = 0;

        pointer_t();
        pointer_t(void* data, size_t bytes);
        template <typename data_t>
        pointer_t(data_t& data);

        template <typename data_t>
        pointer_t(pointer_t<data_t>& other);
        pointer_t(const pointer_t<void>& other);

        template <typename data_t>
        pointer_t(pointer_t<data_t>&& other) noexcept;
        pointer_t(pointer_t<void>&& other) noexcept;

        pointer_t<void>& operator=(const pointer_t<void>& other);

        template <typename data_t>
        pointer_t<void>& operator=(pointer_t<data_t>&& other) noexcept;
        pointer_t<void>& operator=(pointer_t<void>&& other) noexcept;

        ~pointer_t();

        template <typename data_t>
        operator pointer_t<data_t>& ();

        template <typename data_t1, typename data_t2>
        friend bool operator ==(const pointer_t<data_t1>& pointer_a,
                                const pointer_t<data_t2>& pointer_b);
        template <typename data_t1, typename data_t2>
        friend bool operator !=(const pointer_t<data_t1>& pointer_a,
                                const pointer_t<data_t2>& pointer_b);
    };

}

#include "nera/pointer.inl"
