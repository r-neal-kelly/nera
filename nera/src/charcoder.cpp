/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "nera/charcoder.h"
#include "nera/charcoder.inl"

namespace nera {

    const ascii_charcoder_t& ascii_charcoder_t::singleton()
    {
        static const ascii_charcoder_t ascii_charcoder;
        return ascii_charcoder;
    }

    vector_t<uint8_t> ascii_charcoder_t::encode(const uint8_t* string, size_t& out_count) const
    {
        vector_t<uint8_t> vector;
        size_t count = 0;

        if (string) {
            for (; *string != 0; string += 1) {
                vector.push(*const_cast<uint8_t*>(string));
                count += 1;
            }
            vector.push(0);
            count += 1;
        }
        out_count = count;

        return std::move(vector);
    }

    uint8_t& ascii_charcoder_t::at(vector_t<uint8_t>& vector, size_t index) const
    {
        NERA_ASSERT(index < vector.count);
        return vector.at(index);
    }

    uint8_t* ascii_charcoder_t::point(vector_t<uint8_t>& vector, size_t index) const
    {
        NERA_ASSERT(index < vector.count);
        return vector.point(index);
    }

}
