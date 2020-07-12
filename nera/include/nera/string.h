/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "stdint.h"

#include "nera/types.h"
#include "nera/vector.h"

namespace nera {

    class charcoder_t {
    public:
        static const charcoder_t& ascii();
        static const charcoder_t& utf8();
        static const charcoder_t& utf16();
        static const charcoder_t& utf32();

        typedef void (*encode_f)(const void* const data, vector_t<void>& out_vector);

    public:
        const encode_f encode;
        size_t count(pointer_t<void>& data) const;
        size_t begin(pointer_t<void>& data, void** out_cursor) const;
        size_t end(pointer_t<void>& data, void** out_cursor) const;
        size_t next(void** cursor) const; // shall incrememt cursor
        size_t prev(void** cursor) const; // shall decrement cursor
    };

    class ascii_t {
    public:
        const charcoder_t& charcoder;
        vector_t<uint8_t> vector;
        size_t count = 0;

        ascii_t(const uint8_t* const data) :
            charcoder(charcoder_t::ascii()),
            //vector(std::move(charcoder.encode(data, vector))), // vector needs more work before this can be done
            count(0)
        {
        }
    };

    class utf8_t {
    public:
        const charcoder_t& charcoder;
        const vector_t<uint8_t> data;
        size_t count = 0;
    };

    class utf16_t {
    public:
        const charcoder_t& charcoder;
        const vector_t<uint16_t> data;
        size_t count = 0;
    };

    class utf32_t {
    public:
        const charcoder_t& charcoder;
        const vector_t<uint32_t> data;
        size_t count = 0;
    };

}

#include "nera/string.inl"
