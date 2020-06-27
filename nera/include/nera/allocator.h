#pragma once

#include "nera/pointer.h"

namespace nera {

    typedef bool (*allocate_t)(pointer_t<void>& data, size_t bytes);
    typedef bool (*reallocate_t)(pointer_t<void>& data, size_t bytes);
    typedef bool (*deallocate_t)(pointer_t<void>& data);

    class allocator_t {
    public:
        static bool malloc(pointer_t<void>& pointer, size_t bytes);
        static bool remalloc(pointer_t<void>& pointer, size_t bytes);
        static bool demalloc(pointer_t<void>& pointer);

        static bool calloc(pointer_t<void>& pointer, size_t bytes);
        static bool recalloc(pointer_t<void>& pointer, size_t bytes);
        static bool decalloc(pointer_t<void>& pointer);

        static bool zero(pointer_t<void>& pointer);

        static const allocator_t& mallocator();
        static const allocator_t& callocator();

    public:
        allocate_t allocate = nullptr;
        reallocate_t reallocate = nullptr;
        deallocate_t deallocate = nullptr;

        allocator_t(allocate_t allocate, reallocate_t reallocate, deallocate_t deallocate);
        ~allocator_t();
    };

}
