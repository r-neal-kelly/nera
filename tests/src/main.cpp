/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "stdio.h"

#include "main.h"

namespace nera { namespace tests {

    void utils()
    {
        NERA_ASSERT(Is_Power_Of_Two(0x0) == false);
        NERA_ASSERT(Is_Power_Of_Two(0x1) == true);
        NERA_ASSERT(Is_Power_Of_Two(0x10) == true);
        NERA_ASSERT(Is_Power_Of_Two(0x11) == false);
        NERA_ASSERT(Is_Power_Of_Two(0x100) == true);
        NERA_ASSERT(Is_Power_Of_Two(0x101) == false);
    }

    void pointer()
    {
        NERA_TEST(
            "pointer_t default constructor:",
            {
                pointer_t<void> pointer;
                NERA_ASSERT(pointer.data == nullptr);
                NERA_ASSERT(pointer.bytes == 0);
            }
        );

        NERA_TEST(
            "pointer_t user constructor:",
            {
                pointer_t<void> pointer(nullptr, 0);
                NERA_ASSERT(pointer.data == nullptr);
                NERA_ASSERT(pointer.bytes == 0);
            }
        );

        NERA_TEST(
            "pointer_t deconstructor:",
            {
                int num = 16;
                pointer_t<int> pointer(&num, sizeof(int));
                NERA_ASSERT(pointer.data == &num);
                NERA_ASSERT(pointer.bytes == sizeof(int));
                pointer.~pointer_t();
                NERA_ASSERT(pointer.data == nullptr);
                NERA_ASSERT(pointer.bytes == 0);
            }
        );
        NERA_TEST(
            "pointer_t<data_t> to pointer_t<void>*:",
            {
                double dbl = 100.1;
                pointer_t<double> pointer(&dbl, sizeof(double));
                pointer_t<void>* void_pointer = pointer;
                NERA_ASSERT(void_pointer->data == &dbl);
                NERA_ASSERT(void_pointer->bytes == sizeof(double));
            }
        );
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
