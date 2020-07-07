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

    #define NERA_TEST(MESSAGE_, BODY_)  \
    NERA_M                              \
        printf("%s ...", MESSAGE_);     \
        BODY_;                          \
        printf("Ok!\n");                \
    NERA_W

    constexpr size_t MAX_SIZE_T = ~static_cast<size_t>(0);

    void assert(const char* assertion,
                const char* function,
                const char* file,
                int line);

    inline bool Is_Power_Of_Two(size_t word)
    {
        return word != 0 && !(word & (word - 1));
    }

}
