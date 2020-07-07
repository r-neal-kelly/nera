/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

namespace nera {

    template <typename first_t, typename second_t>
    class tuple_t {
    public:
        first_t first;
        second_t second;
    };

}

#include "nera/tuple.inl"
