/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

//#include "stdio.h" // temp for printf
#include <utility>

#include "nera/pointer.h"
#include "nera/utils.h"

namespace nera {

    // data_t

    template <typename data_t>
    inline pointer_t<data_t>::pointer_t() :
        data(nullptr), bytes(0)
    {
    }

    template <typename data_t>
    inline pointer_t<data_t>::pointer_t(data_t* data, size_t bytes) :
        data(data), bytes(bytes)
    {
    }

    template <typename data_t>
    inline pointer_t<data_t>::pointer_t(data_t& data) :
        data(&data), bytes(sizeof(data))
    {
    }

    template <typename data_t>
    inline pointer_t<data_t>::pointer_t(const pointer_t<data_t>& other) :
        data(other.data), bytes(other.bytes)
    {
    }

    template <typename data_t>
    inline pointer_t<data_t>::pointer_t(pointer_t<data_t>&& other) noexcept :
        data(std::exchange(other.data, nullptr)), bytes(std::exchange(other.bytes, 0))
    {
    }

    template <typename data_t>
    inline pointer_t<data_t>::pointer_t(pointer_t<void>&& other) noexcept :
        data(static_cast<data_t*>(std::exchange(other.data, nullptr))), bytes(std::exchange(other.bytes, 0))
    {
    }

    template <typename data_t>
    inline pointer_t<data_t>& pointer_t<data_t>::operator=(const pointer_t<data_t>& other)
    {
        if (&other != this) {
            data = other.data;
            bytes = other.bytes;
        }
        return *this;
    }

    template <typename data_t>
    inline pointer_t<data_t>& pointer_t<data_t>::operator=(pointer_t<data_t>&& other) noexcept
    {
        if (&other != this) {
            data = std::exchange(other.data, nullptr);
            bytes = std::exchange(other.bytes, 0);
        }
        return *this;
    }

    template <typename data_t>
    inline pointer_t<data_t>::~pointer_t()
    {
        data = nullptr;
        bytes = 0;
    }

    template <typename data_t>
    inline pointer_t<data_t>::operator pointer_t<void>& ()
    {
        return reinterpret_cast<pointer_t<void>&>(*this);
    }

    template <typename data_t1, typename data_t2>
    bool operator ==(const pointer_t<data_t1>& pointer_a, const pointer_t<data_t2>& pointer_b)
    {
        return pointer_a.data == pointer_b.data && pointer_a.bytes == pointer_b.bytes;
    }

    template <typename data_t1, typename data_t2>
    bool operator !=(const pointer_t<data_t1>& pointer_a, const pointer_t<data_t2>& pointer_b)
    {
        return !(pointer_a == pointer_b);
    }

    template <typename data_t>
    inline size_t pointer_t<data_t>::count()
    {
        return bytes / sizeof(data_t);
    }

    // void

    inline pointer_t<void>::pointer_t() :
        data(nullptr), bytes(0)
    {
    }

    inline pointer_t<void>::pointer_t(void* data, size_t bytes) :
        data(data), bytes(bytes)
    {
    }

    template <typename data_t>
    inline pointer_t<void>::pointer_t(data_t& data) :
        data(&data), bytes(sizeof(data))
    {
    }

    template <typename data_t>
    inline pointer_t<void>::pointer_t(pointer_t<data_t>& other) :
        data(other.data), bytes(other.bytes)
    {
    }

    inline pointer_t<void>::pointer_t(const pointer_t<void>& other) :
        data(other.data), bytes(other.bytes)
    {
    }

    template <typename data_t>
    inline pointer_t<void>::pointer_t(pointer_t<data_t>&& other) noexcept :
        data(std::exchange(other.data, nullptr)), bytes(std::exchange(other.bytes, 0))
    {
    }

    inline pointer_t<void>::pointer_t(pointer_t<void>&& other) noexcept :
        data(std::exchange(other.data, nullptr)), bytes(std::exchange(other.bytes, 0))
    {
    }

    inline pointer_t<void>& pointer_t<void>::operator =(const pointer_t<void>& other)
    {
        if (&other != this) {
            data = other.data;
            bytes = other.bytes;
        }
        return *this;
    }

    template <typename data_t>
    inline pointer_t<void>& pointer_t<void>::operator =(pointer_t<data_t>&& other) noexcept
    {
        if (reinterpret_cast<pointer_t<void>*>(&other) != this) {
            data = std::exchange(other.data, nullptr);
            bytes = std::exchange(other.bytes, 0);
        }
        return *this;
    }

    inline pointer_t<void>& pointer_t<void>::operator =(pointer_t<void>&& other) noexcept
    {
        if (&other != this) {
            data = std::exchange(other.data, nullptr);
            bytes = std::exchange(other.bytes, 0);
        }
        return *this;
    }

    inline pointer_t<void>::~pointer_t()
    {
        data = nullptr;
        bytes = 0;
    }

    template <typename data_t>
    inline pointer_t<void>::operator pointer_t<data_t>& ()
    {
        return reinterpret_cast<pointer_t<data_t>&>(*this);
    }

}
