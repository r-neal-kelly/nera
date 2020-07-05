/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "nera/pointer.h"
#include "nera/utils.h"

namespace nera {

    template <typename data_t>
    pointer_t<data_t>::pointer_t() :
        data(nullptr), bytes(0)
    {
    }

    template <typename data_t>
    pointer_t<data_t>::pointer_t(data_t* data, size_t bytes) :
        data(data), bytes(bytes)
    {
    }

    template <typename data_t>
    pointer_t<data_t>::~pointer_t()
    {
        data = nullptr;
        bytes = 0;
    }

    template <typename data_t>
    pointer_t<data_t>::operator pointer_t<void>* ()
    {
        return reinterpret_cast<pointer_t<void>*>(this);
    }

    template <typename data_t>
    pointer_t<data_t>::operator data_t* ()
    {
        return data;
    }

    template <typename data_t>
    pointer_t<data_t>::operator void* ()
    {
        return static_cast<void*>(data);
    }

}
