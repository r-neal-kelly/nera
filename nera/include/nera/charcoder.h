/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "nera/types.h"
#include "nera/vector.h"

namespace nera {

    template <typename unit_t = uint8_t>
    class charcoder_t {
    public:
        virtual vector_t<unit_t> encode(const unit_t* string, size_t& out_count) const = 0;
        virtual unit_t& at(vector_t<unit_t>& vector, size_t index) const = 0;
        virtual unit_t* point(vector_t<unit_t>& vector, size_t index) const = 0;

        /*size_t count(pointer_t<unit_t>& data) const;
        size_t begin(pointer_t<unit_t>& data, unit_t** out_cursor) const;
        size_t end(pointer_t<unit_t>& data, unit_t** out_cursor) const;
        size_t next(unit_t** cursor) const; // shall incrememt cursor
        size_t prev(unit_t** cursor) const; // shall decrement cursor*/
    };

    class ascii_charcoder_t : public charcoder_t<uint8_t> {
    public:
        static const ascii_charcoder_t& singleton();

    public:
        virtual vector_t<uint8_t> encode(const uint8_t* string, size_t& out_count) const override;
        virtual uint8_t& at(vector_t<uint8_t>& vector, size_t index) const override;
        virtual uint8_t* point(vector_t<uint8_t>& vector, size_t index) const override;
    };

}
