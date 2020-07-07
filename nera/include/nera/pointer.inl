/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

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
    inline pointer_t<data_t>::pointer_t(data_t* data) :
        data(data), bytes(sizeof(data_t))
    {
    }

    template <typename data_t>
    inline pointer_t<data_t>::~pointer_t()
    {
        data = nullptr;
        bytes = 0;
    }

    template <typename data_t>
    inline size_t pointer_t<data_t>::count()
    {
        return bytes / sizeof(data_t);
    }

    template <typename data_t>
    inline pointer_t<data_t>::operator pointer_t<void>* ()
    {
        return reinterpret_cast<pointer_t<void>*>(this);
    }

    template <typename data_t>
    inline pointer_t<data_t>::operator data_t* ()
    {
        return data;
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

    inline pointer_t<void>::~pointer_t()
    {
        data = nullptr;
        bytes = 0;
    }

    inline pointer_t<void>::operator pointer_t<void>* ()
    {
        return this;
    }

}
