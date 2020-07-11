/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

namespace nera {

    #define NERA_M \
        do {

    #define NERA_W } \
        while(false)

    #define NERA_ASSERT(THIS_IS_TRUE_)      \
    (                                       \
        (THIS_IS_TRUE_) ? (                 \
            true                            \
        ) : (                               \
            nera::assert(#THIS_IS_TRUE_,    \
                         __func__,          \
                         __FILE__,          \
                         __LINE__),         \
            false                           \
        )                                   \
    )

    constexpr size_t MAX_SIZE_T = static_cast<size_t>(~0);

    void assert(const char* assertion,
                const char* function,
                const char* file,
                int line);

    inline bool is_power_of_two(size_t word)
    {
        return word != 0 && !(word & (word - 1));
    }

    // bits

    template <typename bits_t, typename idx_t>
    inline bits_t bit_on(const bits_t& bits, const idx_t idx)
    {
        return bits | (1llu << idx);
    }

    template <typename bits_t, typename idx_t>
    inline bits_t bit_off(const bits_t& bits, const idx_t idx)
    {
        return bits & ~(1llu << idx);
    }

    template <typename bits_t, typename idx_t>
    inline bool is_bit_on(const bits_t& bits, const idx_t idx)
    {
        return 1llu & (bits >> idx);
    }

    template <typename bits_t, typename idx_t>
    inline bool is_bit_off(const bits_t& bits, const idx_t idx)
    {
        return !(1llu & (bits >> idx));
    }

    template <typename bits_t, typename idx_t>
    inline bits_t toggle_bit(const bits_t& bits, const idx_t idx)
    {
        return bits ^ (1llu << idx);
    }

    template <typename bits_t>
    inline bits_t clear_bits(const bits_t& bits)
    {
        return 0;
    }

}
