/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "stdio.h"

#include "main.h"

namespace nera { namespace tests {

    void start_tests(const char* name)
    {
        printf("%s {\n\n", name);
    }

    void run_test(const char* name, void (*lambda)())
    {
        printf("    %s\n", name);
        lambda();
    }

    void stop_tests()
    {
        printf("\n}\n\n");
    }

    void utils()
    {
        NERA_ASSERT(is_power_of_two(0x0) == false);
        NERA_ASSERT(is_power_of_two(0x1) == true);
        NERA_ASSERT(is_power_of_two(0x10) == true);
        NERA_ASSERT(is_power_of_two(0x11) == false);
        NERA_ASSERT(is_power_of_two(0x100) == true);
        NERA_ASSERT(is_power_of_two(0x101) == false);
    }

    void pointer()
    {
        start_tests("template <typename data_t>\n"
                    "class pointer_t<data_t>");

        run_test(
            "pointer_t()",
            []() -> void
            {
                pointer_t<int> pointer;
                NERA_ASSERT(pointer.data == nullptr);
                NERA_ASSERT(pointer.bytes == 0);
            }
        );

        run_test(
            "pointer_t(data_t*, size_t)",
            []() -> void
            {
                int ints[5];
                pointer_t<int> pointer(ints, sizeof(int) * 5);
                NERA_ASSERT(pointer.data == ints);
                NERA_ASSERT(pointer.bytes == sizeof(int) * 5);
            }
        );

        run_test(
            "pointer_t(data_t*)",
            []() -> void
            {
                char letter = 'a';
                pointer_t<char> pointer(&letter);
                NERA_ASSERT(pointer.data == &letter);
                NERA_ASSERT(pointer.bytes == sizeof(char));
            }
        );

        run_test(
            "pointer_t(const pointer_t<data_t>&)",
            []() -> void
            {
                uint16_t num_16 = 256;
                pointer_t<uint16_t> pointer_a(&num_16);
                pointer_t<uint16_t> pointer_b(pointer_a);
                NERA_ASSERT(pointer_a.data == &num_16);
                NERA_ASSERT(pointer_b.data == &num_16);
                NERA_ASSERT(pointer_a.bytes == sizeof(uint16_t));
                NERA_ASSERT(pointer_b.bytes == sizeof(uint16_t));
            }
        );

        run_test(
            "pointer_t(pointer_t<data_t>&&)",
            []() -> void
            {
                struct test_t { int a = 16; int b = 32; int c = 64; } test;
                pointer_t<test_t> pointer_a(&test);
                pointer_t<test_t> pointer_b(pointer_a);
                pointer_t<test_t> pointer_c(std::move(pointer_a));
                NERA_ASSERT(pointer_a.data == nullptr);
                NERA_ASSERT(pointer_b.data == &test);
                NERA_ASSERT(pointer_c.data == &test);
                NERA_ASSERT(pointer_a.bytes == 0);
                NERA_ASSERT(pointer_b.bytes == sizeof(test_t));
                NERA_ASSERT(pointer_c.bytes == sizeof(test_t));
            }
        );

        run_test(
            "pointer_t<data_t>& operator=(const pointer_t<data_t>&)",
            []() -> void
            {
                uint16_t num_16 = 256;
                pointer_t<uint16_t> pointer_a(&num_16);
                pointer_t<uint16_t> pointer_b = pointer_a;
                NERA_ASSERT(pointer_a.data == &num_16);
                NERA_ASSERT(pointer_b.data == &num_16);
                NERA_ASSERT(pointer_a.bytes == sizeof(uint16_t));
                NERA_ASSERT(pointer_b.bytes == sizeof(uint16_t));
            }
        );

        run_test(
            "pointer_t<data_t>& operator=(pointer_t<data_t>&&)",
            []() -> void
            {
                struct test_t { int a = 16; int b = 32; int c = 64; } test;
                pointer_t<test_t> pointer_a(&test);
                pointer_t<test_t> pointer_b = pointer_a;
                pointer_t<test_t> pointer_c = std::move(pointer_a);
                NERA_ASSERT(pointer_a.data == nullptr);
                NERA_ASSERT(pointer_b.data == &test);
                NERA_ASSERT(pointer_c.data == &test);
                NERA_ASSERT(pointer_a.bytes == 0);
                NERA_ASSERT(pointer_b.bytes == sizeof(test_t));
                NERA_ASSERT(pointer_c.bytes == sizeof(test_t));
            }
        );

        run_test(
            "~pointer_t()",
            []() -> void
            {
                int ints[5];
                pointer_t<int> pointer(ints, sizeof(ints));
                NERA_ASSERT(pointer.data == ints);
                NERA_ASSERT(pointer.bytes == sizeof(int) * 5);

                pointer.~pointer_t();
                NERA_ASSERT(pointer.data == nullptr);
                NERA_ASSERT(pointer.bytes == 0);
            }
        );

        run_test(
            "size_t count()",
            []() -> void
            {
                bool bools[24];
                pointer_t<bool> pointer_a(bools, sizeof(bools));
                NERA_ASSERT(pointer_a.data == bools);
                NERA_ASSERT(pointer_a.bytes == 24);
                NERA_ASSERT(pointer_a.count() == 24);

                word_t words[12];
                pointer_t<word_t> pointer_b(words, sizeof(words));
                NERA_ASSERT(pointer_b.data == words);
                NERA_ASSERT(pointer_b.bytes == sizeof(word_t) * 12);
                NERA_ASSERT(pointer_b.count() == 12);
            }
        );

        run_test(
            "operator pointer_t<void>* ()",
            []() -> void
            {
                double dbl = 100.1;
                pointer_t<double> pointer(&dbl, sizeof(double));
                pointer_t<void>* void_pointer = pointer;
                NERA_ASSERT(void_pointer->data == &dbl);
                NERA_ASSERT(void_pointer->bytes == sizeof(double));
            }
        );

        run_test(
            "operator data_t* ()",
            []() -> void
            {
                float flt = 17823.0234f;
                pointer_t<float> pointer(&flt);
                float* flt_pointer = pointer;
                NERA_ASSERT(flt_pointer == &flt);
                NERA_ASSERT(flt_pointer == pointer.data);
            }
        );

        stop_tests();
    }

    void allocator()
    {
    }

    void memory()
    {
        const allocator_t& mallocator = allocator_t::mallocator();
        manual_memory_t<int> manual_memory(mallocator, 20);
        manual_memory.free(mallocator);

        auto_memory_t<int> test;
    }

    void vector()
    {
        vector_t<int> ints(allocator_t::callocator(), 16);

        for (size_t index = 0, count = ints.memory.count(); index < count; index += 1) {
            printf("%i", ints.memory[index]);
        } printf("\n");

        ints.push(1);
        ints.push(2);
        ints.push(3);

        for (size_t index = 0, count = ints.memory.count(); index < count; index += 1) {
            printf("%i", ints.memory[index]);
        } printf("\n");

        for (size_t index = 0, count = ints.count; index < count; index += 1) {
            printf("%i", ints[index]);
        } printf("\n");
    }

    void hasher()
    {
        char letter = 'a';
        pointer_t<char> pointer(&letter, sizeof(char));

        const hasher_t& hasher = hasher_t::fnv_1a();
        size_t hash = hasher.hash(pointer);
        NERA_ASSERT(hash != 0);

        NERA_ASSERT(hasher.modulus_reduce(hash, 0) == MAX_SIZE_T);
        
        hasher.bitwise_reduce(hash, 8);
        hasher.bitwise_reduce(hash, 4);
        NERA_ASSERT(hasher.bitwise_reduce(hash, 0) == MAX_SIZE_T);

        hasher.modulus_reduce(hash, 9);
        hasher.modulus_reduce(hash, 7);
        NERA_ASSERT(hasher.modulus_reduce(hash, 0) == MAX_SIZE_T);
    }

    void hashmap()
    {
        hashmap_t<char, int> hashmap;
        hashmap['a'] = 0;
        hashmap['b'] = 1;
        hashmap['c'] = 2;

        printf("%i %i %i\n", hashmap['a'], hashmap['b'], hashmap['c']);

        hashmap_t<int, char> hashmap2;
        hashmap2[34] = 'a';
        hashmap2[263] = 'r';
        hashmap2[86] = 'e';
        hashmap2[3] = 'n';

        printf("%c%c%c%c\n", hashmap2[3], hashmap2[86], hashmap2[263], hashmap2[34]);

        vector_t<tuple_t<int, char>> entries = hashmap2.entries();
        for (size_t idx = 0, count = entries.count; idx < count; idx += 1) {
            printf("%i:%c, ", entries[idx].first, entries[idx].second);
        } printf("\n");
    }

}}

int main()
{
    using namespace nera;

    printf("\n(nera's test suite will assert on any failure)\n\n");

    tests::utils();
    tests::pointer();
    tests::allocator();
    tests::memory();
    tests::vector();
    tests::hasher();
    tests::hashmap();

    printf("\nsuccess!\n");
    getc(stdin);

    return 0;
}
