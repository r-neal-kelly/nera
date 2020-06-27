#pragma once

#include "nera/vector.h"

namespace nera {

    template <typename data_t>
    vector_t<data_t>::vector_t() :
        count(0), grow_rate(1.7f)
    {
    }

    template <typename data_t>
    vector_t<data_t>::~vector_t()
    {
    }

}
