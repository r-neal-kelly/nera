/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "stdint.h"

#include "nera/types.h"
#include "nera/vector.h"

namespace nera {

    // I think processing speed is extremely important.
    // templating might seem to be the faster option, 
    // but the code could get dense, and lots of strings
    // means lots to cache in processor. virtual calls can
    // be slow because they may cause more cache misses
    // than necessary. composition may be the best bet,
    // but it falls short when use of all types are required.

    template <typename data_t>
    class charcoder_t {
    public:
        static const charcoder_t<uint8_t>& ascii();
        static const charcoder_t<uint8_t>& utf8();
        static const charcoder_t<uint16_t>& utf16();
        static const charcoder_t<uint32_t>& utf32();

    public:
        // this can essentially just be a fancy iterator
        // over the raw string data. ascii and utf32 are
        // trivial of course, but utf8 and especially utf16
        // are more troublesome. if we make it like the
        // allocator_t, then we would be making it more
        // extensible for more encodings in the future,
        // where you just supply the necessary funcs.

        // it is to be understood that these will retrieve
        // actual code points, and not simply raw data.
        // ~0 should probably be the default null on either
        // end, but 0 itself is also a contender.
        // I think it should return size, because it's kinda
        // throw away, and it ought to be the word of the processor.
        size_t next(data_t** cursor); // shall incrememt cursor
        size_t prev(data_t** cursor); // shall decrement cursor
        // if these are given an invalid cursor, it is probably best
        // to just jump to the next valid spot, either next or prev.

        // this might be useful, because the charcoder in some
        // cases will need to skip parts of the beginning or end
        // of string.
        size_t begin(pointer_t<data_t>& pointer, data_t** out_cursor);
        size_t end(pointer_t<data_t>& pointer, data_t** out_cursor);
        // we may not need to pass the whole pointer, because it
        // represents memory allocation, not the actual string itself.
        // it could perhaps be useful somehow, but I'm not sure.
        // 'end' may not be a great idea, as it could end up just
        // being like count. how often do we have to traverse a string
        // backwards anyway?

        // expects \0 null termination of string.
        // it should not need to be called, because
        // the initialize can give a count, or a cstring,
        // or a vector, or something that tells us the count.
        // we can slap a 0 on it for the sake of the charcoder.
        size_t count(pointer_t<data_t>& pointer);

        // note that the charcodes is not capable of determing
        // if the string is valid, when composed into the string
        // type itself. we would need a meta type to determine
        // which of the four, or others, would be prudent to use
        // with the raw data. this can also be supplied by the user.
    };

    class ascii_t {
    public:
        const charcoder_t<uint8_t>& charcoder;
        const vector_t<uint8_t> data;
        size_t count = 0;
    };
    static_assert(sizeof(ascii_t) == 0x38, "");
    // 7 words. std::string is 5 words. charcoder and grow_rate make up the difference

    class utf8_t {
    public:
        const charcoder_t<uint8_t>& charcoder;
        const vector_t<uint8_t> data;
        size_t count = 0;
    };

    class utf16_t {
    public:
        const charcoder_t<uint16_t>& charcoder;
        const vector_t<uint16_t> data;
        size_t count = 0;
    };

    class utf32_t {
    public:
        const charcoder_t<uint32_t>& charcoder;
        const vector_t<uint32_t> data;
        size_t count = 0;
    };

    // one possible problem with this pattern is that
    // our regex engine should be able to use all of
    // the above charcodings. that means we either need
    // a virtual interface instead of four types or
    // we need to selectively and carefully employ 
    // templates in the engine itself. rationally,
    // not everyone will be using all four types, so it
    // makes sense to not have all the code accessible
    // in each program. careful templating will allow this.
    // we would have to make sure that each regex instance
    // does not generate a ton of code at the call site.
    // it should be kept as much as possible in the cpp file.
    // we probably shouldn't always read the entire string,
    // except for when gathering multiple matches. the single
    // match mode should not have to read an entire string,
    // unless it's necessary to exhaust all code points, so
    // it won't be so simple as a single template getting all
    // the codes upfront in constructor or something, although
    // that can be done by user selection.

}

#include "nera/string.inl"
