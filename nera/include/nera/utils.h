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

    void assert(const char* assertion,
                const char* function,
                const char* file,
                int line);

}
