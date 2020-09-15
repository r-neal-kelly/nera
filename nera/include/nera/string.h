/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "stdint.h"

#include "nera/types.h"
#include "nera/vector.h"
#include "nera/charcoder.h"

namespace nera {

    class ascii_t {
    public:
        const charcoder_t<uint8_t>& charcoder;
        vector_t<uint8_t> vector;
        size_t count = 0;

        ascii_t(const uint8_t* string);
        ascii_t(const char* string);

        uint8_t& operator [](size_t index);

        operator const uint8_t* ();
        operator const char* ();
    };

    class utf8_t {
    public:
        const charcoder_t<uint8_t>& charcoder;
        const vector_t<uint8_t> vector;
        size_t count = 0;
    };

    class utf16_t {
    public:
        const charcoder_t<uint16_t>& charcoder;
        const vector_t<uint16_t> vector;
        size_t count = 0;
    };

    class utf32_t {
    public:
        const charcoder_t<uint32_t>& charcoder;
        const vector_t<uint32_t> vector;
        size_t count = 0;
    };

}
