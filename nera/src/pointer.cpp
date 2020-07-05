/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "nera/pointer.h"

namespace nera {

    pointer_t<void>::pointer_t() :
        data(nullptr), bytes(0)
    {
    }

    pointer_t<void>::pointer_t(void* data, size_t bytes) :
        data(data), bytes(bytes)
    {
    }

    pointer_t<void>::~pointer_t()
    {
        data = nullptr;
        bytes = 0;
    }

    pointer_t<void>::operator pointer_t<void>* ()
    {
        return this;
    }

    pointer_t<void>::operator void* ()
    {
        return data;
    }

}
