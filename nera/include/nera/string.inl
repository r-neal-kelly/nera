/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "nera/string.h"

namespace nera {

    inline ascii_t::ascii_t(const uint8_t* string) :
        charcoder(ascii_charcoder_t::singleton())
    {
        vector = std::move(charcoder.encode(string, count));
    }

    inline ascii_t::ascii_t(const char* string) :
        charcoder(ascii_charcoder_t::singleton())
    {
        vector = std::move(charcoder.encode(reinterpret_cast<const uint8_t*>(string), count));
    }

    uint8_t& ascii_t::operator [](size_t index)
    {
        NERA_ASSERT(index < count);
        return charcoder.at(vector, index);
    }

    inline ascii_t::operator const uint8_t* ()
    {
        return vector.point(0);
    }

    inline ascii_t::operator const char* ()
    {
        return reinterpret_cast<const char*>(vector.point(0));
    }

}
