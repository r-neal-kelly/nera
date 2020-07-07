/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "stdint.h"

#include "nera/hasher.h"

namespace nera {

    static size_t fnv_1a(pointer_t<void>* pointer)
    {
        uint64_t hash = 0xcbf29ce484222325;
        uint64_t prime = 0x00000100000001b3;
        uint8_t* ptr = static_cast<uint8_t*>(pointer->data);
        for (uint64_t idx = 0; idx < pointer->bytes; idx += 1, ptr += 1) {
            hash ^= *ptr;
            hash *= prime;
        }
        return hash;
    }

    const hasher_t& hasher_t::fnv_1a()
    {
        static const hasher_t hasher(nera::fnv_1a);
        return hasher;
    }

}
