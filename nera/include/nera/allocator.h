/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "nera/pointer.h"

namespace nera {

    typedef bool (*allocate_f)(pointer_t<void>* pointer, size_t bytes);
    typedef bool (*reallocate_f)(pointer_t<void>* pointer, size_t bytes);
    typedef bool (*deallocate_f)(pointer_t<void>* pointer);

    class allocator_t {
    public:
        static bool malloc(pointer_t<void>* pointer, size_t bytes);
        static bool remalloc(pointer_t<void>* pointer, size_t bytes);
        static bool demalloc(pointer_t<void>* pointer);

        static bool calloc(pointer_t<void>* pointer, size_t bytes);
        static bool recalloc(pointer_t<void>* pointer, size_t bytes);
        static bool decalloc(pointer_t<void>* pointer);

        static bool zero(pointer_t<void>* pointer);

        static const allocator_t& mallocator();
        static const allocator_t& callocator();

    public:
        const allocate_f allocate = nullptr;
        const reallocate_f reallocate = nullptr;
        const deallocate_f deallocate = nullptr;
        const bool initializes_to_zero = false;

        allocator_t(allocate_f allocate, reallocate_f reallocate, deallocate_f deallocate, bool initializes_to_zero);
    };

}
