#pragma once

#include "stdint.h"
#include "stdlib.h"
#include "string.h"

namespace nera { namespace vector {

    #ifdef NERA_64_BIT
    typedef uint64_t word_t;
    #else
    typedef uint32_t word_t;
    #endif

    typedef void* (*allocate_t)(size_t bytes);
    typedef void* (*reallocate_t)(void* data, size_t bytes);
    typedef void (*deallocate_t)(void* data);
    // should we make calloc explicit? OS call can be way faster sometimes...

    class allocator_t {
    public:
        allocate_t m_allocate = nullptr;
        reallocate_t m_reallocate = nullptr;
        deallocate_t m_deallocate = nullptr;
        void* m_data = nullptr;
        size_t m_bytes = 0;

        allocator_t()
        {
            m_allocate = (allocate_t)malloc;
            m_reallocate = (reallocate_t)realloc;
            m_deallocate = (deallocate_t)free;
        }

        allocator_t(allocate_t allocate, reallocate_t reallocate, deallocate_t deallocate)
        {
            m_allocate = allocate;
            m_reallocate = reallocate;
            m_deallocate = deallocate;
        }

        ~allocator_t()
        {
            letgo();
            m_allocate = nullptr;
            m_reallocate = nullptr;
            m_deallocate = nullptr;
        }

        bool grab(size_t bytes)
        {
            if (bytes == 0) {
                // undefined behavior avoidance, may want to assert
                return false;
            } else {
                if (m_data) {
                    void* data = m_reallocate(m_data, bytes);
                    if (data) {
                        m_data = data;
                        m_bytes = bytes;
                        return true;
                    } else {
                        return false;
                    }
                } else {
                    m_data = m_allocate(bytes);
                    if (m_data) {
                        m_bytes = bytes;
                        return true;
                    } else {
                        return false;
                    }
                }
            }
        }

        void letgo()
        {
            if (m_data) {
                m_deallocate(m_data);
                m_data = nullptr;
                m_bytes = 0;
            }
        }

        void zero()
        {
            if (m_data) {
                // we'll use word_t to set 0, and do the remainder in 8bit.
                // not sure if memset will actually do this or not.
                // it looks like size_t actually is the same as word_t, cool!
            }
        }

        void* data()
        {
            return m_data;
        }

        size_t bytes()
        {
            return m_bytes;
        }
    };

    typedef int data_t;

    //template <typename data_t>
    class vector_t {
    public:
        //allocator_t<data_t> allocator;
        allocator_t m_allocator;
        size_t m_count;
        float m_grow_rate;

        vector_t()
        {
            m_count = 0;
            m_grow_rate = 1.7f;
        }

        vector_t(size_t size)
        {
        }

        ~vector_t()
        {
        }

        bool reserve(size_t elements)
        {

        }

        void push(data_t element)
        {

        }

        void push_at(data_t element, size_t index)
        {

        }

        data_t pop()
        {

        }

        data_t pop_at(size_t index)
        {

        }

        data_t& at(size_t index)
        {

        }

        data_t* point(size_t index)
        {

        }

        size_t count()
        {
            return m_count;
        }

        size_t find(data_t& element)
        {

        }
    };

}}
