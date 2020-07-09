/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "stdlib.h"

#include "nera/allocator.h"
#include "nera/types.h"

namespace nera {

    bool allocator_t::malloc(pointer_t<void>& pointer, size_t bytes)
    {
        if (pointer.data != nullptr || bytes == 0) {
            return false;
        } else {
            void* data = ::malloc(bytes);
            if (data) {
                pointer.data = data;
                pointer.bytes = bytes;
                return true;
            } else {
                return false;
            }
        }
    }

    bool allocator_t::remalloc(pointer_t<void>& pointer, size_t bytes)
    {
        if (pointer.data == nullptr || bytes == 0) {
            return false;
        } else {
            void* data = ::realloc(pointer.data, bytes);
            if (data) {
                pointer.data = data;
                pointer.bytes = bytes;
                return true;
            } else {
                return false;
            }
        }
    }

    bool allocator_t::demalloc(pointer_t<void>& pointer)
    {
        if (pointer.data == nullptr) {
            return false;
        } else {
            ::free(pointer.data);
            pointer.data = nullptr;
            pointer.bytes = 0;
            return true;
        }
    }

    bool allocator_t::calloc(pointer_t<void>& pointer, size_t bytes)
    {
        if (pointer.data != nullptr || bytes == 0) {
            return false;
        } else {
            void* data = ::calloc(bytes, sizeof(byte_t));
            if (data) {
                pointer.data = data;
                pointer.bytes = bytes;
                return true;
            } else {
                return false;
            }
        }
    }

    bool allocator_t::recalloc(pointer_t<void>& pointer, size_t bytes)
    {
        if (pointer.data == nullptr || bytes == 0) {
            return false;
        } else {
            void* data = ::realloc(pointer.data, bytes);
            if (data) {
                if (bytes > pointer.bytes) {
                    pointer_t<void> slice;
                    slice.data = reinterpret_cast<byte_t*>(data) + pointer.bytes;
                    slice.bytes = bytes - pointer.bytes;
                    zero(slice);
                }
                pointer.data = data;
                pointer.bytes = bytes;
                return true;
            } else {
                return false;
            }
        }
    }

    bool allocator_t::decalloc(pointer_t<void>& pointer)
    {
        return demalloc(pointer);
    }

    bool copy(pointer_t<void>& from, pointer_t<void>& to)
    {
        if (from.data == nullptr || from.bytes == 0 || to.data == nullptr || to.bytes == 0) {
            return false;
        } else {
            word_t* from_words = reinterpret_cast<word_t*>(from.data);
            word_t* to_words = reinterpret_cast<word_t*>(to.data);
            size_t bytes;
            if (from.bytes > to.bytes) {
                bytes = to.bytes;
            } else {
                bytes = from.bytes;
            }
            while (bytes >= sizeof(word_t)) {
                *to_words = *from_words;
                from_words += 1;
                to_words += 1;
                bytes -= sizeof(word_t);
            }
            byte_t* from_data = reinterpret_cast<byte_t*>(from_words);
            byte_t* to_data = reinterpret_cast<byte_t*> (to_words);
            while (bytes >= sizeof(byte_t)) {
                *to_data = *from_data;
                from_data += 1;
                to_data += 1;
                bytes -= sizeof(byte_t);
            }
            return true;
        }
    }

    bool allocator_t::zero(pointer_t<void>& pointer)
    {
        if (pointer.data == nullptr || pointer.bytes == 0) {
            return false;
        } else {
            word_t* words = reinterpret_cast<word_t*>(pointer.data);
            size_t bytes = pointer.bytes;
            while (bytes >= sizeof(word_t)) {
                *words = 0;
                words += 1;
                bytes -= sizeof(word_t);
            }
            byte_t* data = reinterpret_cast<byte_t*>(words);
            while (bytes >= sizeof(byte_t)) {
                *data = 0;
                data += 1;
                bytes -= sizeof(byte_t);
            }
            return true;
        }
    }

    const allocator_t& allocator_t::mallocator()
    {
        static const allocator_t allocator(malloc, remalloc, demalloc, false);
        return allocator;
    }

    const allocator_t& allocator_t::callocator()
    {
        static const allocator_t allocator(calloc, recalloc, decalloc, true);
        return allocator;
    }

    allocator_t::allocator_t(allocate_f allocate, reallocate_f reallocate, deallocate_f deallocate, bool initializes_to_zero) :
        allocate(allocate), reallocate(reallocate), deallocate(deallocate), initializes_to_zero(initializes_to_zero)
    {
    }

}
