/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "nera/types.h"
#include "nera/memory.h"

namespace nera {

    template <typename data_t>
    class vector_t {
    public:
        static constexpr float DEFAULT_GROW_RATE = 1.7f;

    public:
        auto_memory_t<data_t> memory;
        size_t count = 0;
        float grow_rate = DEFAULT_GROW_RATE;

        vector_t();
        vector_t(size_t reserve_count);
        vector_t(const allocator_t& allocator);
        vector_t(const allocator_t& allocator, size_t reserve_count);

        vector_t(const vector_t<data_t>& other);
        vector_t(vector_t<data_t>&& other) noexcept;
        vector_t<data_t>& operator=(const vector_t<data_t>& other);
        vector_t<data_t>& operator=(vector_t<data_t>&& other) noexcept;

        ~vector_t();

        bool reserve(size_t count);
        bool energize(float grow_rate = DEFAULT_GROW_RATE);
        bool grow();
        data_t& at(size_t index);
        data_t* point(size_t index);
        bool push(data_t& in_element);
        bool push(data_t&& in_element);
        bool pull(data_t& out_element);
        bool pop();
        bool pop_all();
        size_t find(data_t& element);
        bool clone(vector_t<data_t>& out_vector);

        data_t& operator [](size_t index);
    };

    // I think I would like to use ascii_t with this eventually
    // probably be best if this assumes endianess is already converted?
    inline vector_t<char> to_binary(pointer_t<void>& input)
    {
        static const char* half_bytes[16] = {
            "0000", "0001", "0010", "0011",
            "0100", "0101", "0110", "0111",
            "1000", "1001", "1010", "1011",
            "1100", "1101", "1110", "1111"
        };

        size_t bits = input.bytes * 8;
        size_t spaces = input.bytes * 1 - 1;
        size_t null = 1;
        vector_t<char> chars(allocator_t::callocator(), bits + spaces + null);

        byte_t* data = static_cast<byte_t*>(input.data) + input.bytes;
        while (data != input.data) {
            data -= 1;
            byte_t byte = *data;
            char* left = const_cast<char*>(half_bytes[(byte & 0xF0) >> 4]);
            char* right = const_cast<char*>(half_bytes[byte & 0x0F]);
            for (size_t idx = 0; idx < 4; idx += 1) {
                chars.push(left[idx]);
            }
            for (size_t idx = 0; idx < 4; idx += 1) {
                chars.push(right[idx]);
            }
            chars.push(' ');
        }
        chars.at(chars.count - 1) = '\0';

        return chars;
    }

    inline vector_t<char> to_hexadecimal(pointer_t<void>& input)
    {
        static char half_bytes[16] = {
            '0', '1', '2', '3',
            '4', '5', '6', '7',
            '8', '9', 'A', 'B',
            'C', 'D', 'E', 'F'
        };

        size_t digits = input.bytes * 2;
        size_t null = 1;
        vector_t<char> chars(allocator_t::callocator(), digits + null);

        byte_t* data = static_cast<byte_t*>(input.data) + input.bytes;
        while (data != input.data) {
            data -= 1;
            byte_t byte = *data;
            char left = half_bytes[(byte & 0xF0) >> 4];
            char right = half_bytes[byte & 0x0F];
            chars.push(left);
            chars.push(right);
        }
        chars.push('\0');

        return chars;
    }

}

#include "nera/vector.inl"
