/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "stdio.h"

#include "main.h"

namespace nera { namespace tests {

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
    }

    void vector()
    {
        vector_t<int> ints(allocator_t::callocator(), 16);

        for (size_t index = 0, count = ints.memory.count; index < count; index += 1) {
            printf("%i", ints.memory[index]);
        } printf("\n");

        ints.push(1);
        ints.push(2);
        ints.push(3);

        for (size_t index = 0, count = ints.memory.count; index < count; index += 1) {
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
        hasher_t hasher = hasher_t::fnv_1a();
        printf("hashed letter: %zu", hasher.hash(pointer));
    }

    void hashmap()
    {
        hashmap_t<char, int> hashmap;
    }

}}

int main()
{
    using namespace nera;

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
