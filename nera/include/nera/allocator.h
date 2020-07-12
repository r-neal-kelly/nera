/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "nera/pointer.h"

namespace nera {

    class allocator_t {
    public:
        typedef bool (*allocate_f)(pointer_t<void>& pointer, size_t bytes);
        typedef bool (*reallocate_f)(pointer_t<void>& pointer, size_t bytes);
        typedef bool (*deallocate_f)(pointer_t<void>& pointer);

        static const allocator_t& mallocator();
        static const allocator_t& callocator();

        static bool copy(pointer_t<void>& from, pointer_t<void>& to);
        static bool zero(pointer_t<void>& pointer);

    public:
        const allocate_f allocate = nullptr;
        const reallocate_f reallocate = nullptr;
        const deallocate_f deallocate = nullptr;
        const bool initializes_to_zero = false;

        allocator_t(allocate_f allocate,
                    reallocate_f reallocate,
                    deallocate_f deallocate,
                    bool initializes_to_zero);
    };

}
