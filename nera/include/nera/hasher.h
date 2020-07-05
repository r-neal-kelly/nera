/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "nera/pointer.h"

namespace nera {

    typedef size_t (*hasher_f)(pointer_t<void>* pointer);

    class hasher_t {
    public:
        static const hasher_t& fnv_1a();

    public:
        const hasher_f hash = nullptr;

        hasher_t(hasher_f hash);
    };

}
