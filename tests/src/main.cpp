/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "stdio.h"
#include <thread>
#include <chrono>

#include "main.h"

namespace nera { namespace tests {

    void start_tests(const char* name)
    {
        printf("%s {\n", name);
    }

    void start_tests(const char* line_1,
                     const char* line_2)
    {
        printf("%s\n", line_1);
        printf("%s {\n", line_2);
    }

    void new_line()
    {
        printf("\n");
    }

    void run_test(const char* name,
                  void (*lambda)())
    {
        printf("    %s\n", name);
        lambda();
    }

    void run_test(const char* line_1,
                  const char* line_2,
                  void (*lambda)())
    {
        printf("    %s\n", line_1);
        printf("    %s\n", line_2);
        lambda();
    }

    void run_test(const char* line_1,
                  const char* line_2,
                  const char* line_3,
                  void (*lambda)())
    {
        printf("    %s\n", line_1);
        printf("    %s\n", line_2);
        printf("    %s\n", line_3);
        lambda();
    }

    void run_test(const char* line_1,
                  const char* line_2,
                  const char* line_3,
                  const char* line_4,
                  void (*lambda)())
    {
        printf("    %s\n", line_1);
        printf("    %s\n", line_2);
        printf("    %s\n", line_3);
        printf("    %s\n", line_4);
        lambda();
    }

    void stop_tests()
    {
        printf("};\n\n");
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

    void utils_bits()
    {
        start_tests("namespace nera");

        run_test(
            "template <typename bits_t, typename idx_t>",
            "bits_t bit_on(const bits_t& bits, const idx_t idx);",
            []() -> void
            {
                byte_t byte = 0;

                byte = bit_on(byte, 0);
                NERA_ASSERT(byte == 1);
                byte = bit_on(byte, 1);
                NERA_ASSERT(byte == 3);
                byte = bit_on(byte, 2);
                NERA_ASSERT(byte == 7);
                byte = bit_on(byte, 3);
                NERA_ASSERT(byte == 15);
                byte = bit_on(byte, 4);
                NERA_ASSERT(byte == 31);
                byte = bit_on(byte, 5);
                NERA_ASSERT(byte == 63);
                byte = bit_on(byte, 6);
                NERA_ASSERT(byte == 127);
                byte = bit_on(byte, 7);
                NERA_ASSERT(byte == 255);
            }
        );

        new_line();
        run_test(
            "template <typename bits_t, typename idx_t>",
            "bits_t bit_off(const bits_t& bits, const idx_t idx);",
            []() -> void
            {
                byte_t byte = 255;

                byte = bit_off(byte, 0);
                NERA_ASSERT(byte == 254);
                byte = bit_off(byte, 1);
                NERA_ASSERT(byte == 252);
                byte = bit_off(byte, 2);
                NERA_ASSERT(byte == 248);
                byte = bit_off(byte, 3);
                NERA_ASSERT(byte == 240);
                byte = bit_off(byte, 4);
                NERA_ASSERT(byte == 224);
                byte = bit_off(byte, 5);
                NERA_ASSERT(byte == 192);
                byte = bit_off(byte, 6);
                NERA_ASSERT(byte == 128);
                byte = bit_off(byte, 7);
                NERA_ASSERT(byte == 0);
            }
        );

        new_line();
        run_test(
            "template <typename bits_t, typename idx_t>",
            "bool is_bit_on(const bits_t& bits, const idx_t idx);",
            []() -> void
            {
                NERA_ASSERT(is_bit_on(0, 0) == false);
                NERA_ASSERT(is_bit_on(0, 1) == false);
                NERA_ASSERT(is_bit_on(0, 2) == false);

                NERA_ASSERT(is_bit_on(1, 0) == true);
                NERA_ASSERT(is_bit_on(1, 1) == false);
                NERA_ASSERT(is_bit_on(1, 2) == false);

                NERA_ASSERT(is_bit_on(2, 0) == false);
                NERA_ASSERT(is_bit_on(2, 1) == true);
                NERA_ASSERT(is_bit_on(2, 2) == false);

                NERA_ASSERT(is_bit_on(3, 0) == true);
                NERA_ASSERT(is_bit_on(3, 1) == true);
                NERA_ASSERT(is_bit_on(3, 2) == false);

                NERA_ASSERT(is_bit_on(4, 0) == false);
                NERA_ASSERT(is_bit_on(4, 1) == false);
                NERA_ASSERT(is_bit_on(4, 2) == true);

                NERA_ASSERT(is_bit_on(5, 0) == true);
                NERA_ASSERT(is_bit_on(5, 1) == false);
                NERA_ASSERT(is_bit_on(5, 2) == true);

                NERA_ASSERT(is_bit_on(6, 0) == false);
                NERA_ASSERT(is_bit_on(6, 1) == true);
                NERA_ASSERT(is_bit_on(6, 2) == true);

                NERA_ASSERT(is_bit_on(7, 0) == true);
                NERA_ASSERT(is_bit_on(7, 1) == true);
                NERA_ASSERT(is_bit_on(7, 2) == true);
            }
        );

        new_line();
        run_test(
            "template <typename bits_t, typename idx_t>",
            "bool is_bit_off(const bits_t& bits, const idx_t idx);",
            []() -> void
            {
                NERA_ASSERT(is_bit_off(0, 0) == true);
                NERA_ASSERT(is_bit_off(0, 1) == true);
                NERA_ASSERT(is_bit_off(0, 2) == true);

                NERA_ASSERT(is_bit_off(1, 0) == false);
                NERA_ASSERT(is_bit_off(1, 1) == true);
                NERA_ASSERT(is_bit_off(1, 2) == true);

                NERA_ASSERT(is_bit_off(2, 0) == true);
                NERA_ASSERT(is_bit_off(2, 1) == false);
                NERA_ASSERT(is_bit_off(2, 2) == true);

                NERA_ASSERT(is_bit_off(3, 0) == false);
                NERA_ASSERT(is_bit_off(3, 1) == false);
                NERA_ASSERT(is_bit_off(3, 2) == true);

                NERA_ASSERT(is_bit_off(4, 0) == true);
                NERA_ASSERT(is_bit_off(4, 1) == true);
                NERA_ASSERT(is_bit_off(4, 2) == false);

                NERA_ASSERT(is_bit_off(5, 0) == false);
                NERA_ASSERT(is_bit_off(5, 1) == true);
                NERA_ASSERT(is_bit_off(5, 2) == false);

                NERA_ASSERT(is_bit_off(6, 0) == true);
                NERA_ASSERT(is_bit_off(6, 1) == false);
                NERA_ASSERT(is_bit_off(6, 2) == false);

                NERA_ASSERT(is_bit_off(7, 0) == false);
                NERA_ASSERT(is_bit_off(7, 1) == false);
                NERA_ASSERT(is_bit_off(7, 2) == false);
            }
        );

        new_line();
        run_test(
            "template <typename bits_t, typename idx_t>",
            "bits_t toggle_bit(const bits_t& bits, const idx_t idx);",
            []() -> void
            {
                byte_t byte = 0;

                byte = toggle_bit(byte, 0);
                NERA_ASSERT(byte == 1);
                byte = toggle_bit(byte, 0);
                NERA_ASSERT(byte == 0);

                byte = toggle_bit(byte, 1);
                NERA_ASSERT(byte == 2);
                byte = toggle_bit(byte, 1);
                NERA_ASSERT(byte == 0);

                byte = toggle_bit(byte, 2);
                NERA_ASSERT(byte == 4);
                byte = toggle_bit(byte, 2);
                NERA_ASSERT(byte == 0);

                byte = toggle_bit(byte, 3);
                NERA_ASSERT(byte == 8);
                byte = toggle_bit(byte, 3);
                NERA_ASSERT(byte == 0);

                byte = toggle_bit(byte, 4);
                NERA_ASSERT(byte == 16);
                byte = toggle_bit(byte, 4);
                NERA_ASSERT(byte == 0);

                byte = toggle_bit(byte, 5);
                NERA_ASSERT(byte == 32);
                byte = toggle_bit(byte, 5);
                NERA_ASSERT(byte == 0);

                byte = toggle_bit(byte, 6);
                NERA_ASSERT(byte == 64);
                byte = toggle_bit(byte, 6);
                NERA_ASSERT(byte == 0);

                byte = toggle_bit(byte, 7);
                NERA_ASSERT(byte == 128);
                byte = toggle_bit(byte, 7);
                NERA_ASSERT(byte == 0);
            }
        );

        new_line();
        run_test(
            "template <typename bits_t>",
            "bits_t clear_bits(const bits_t& bits);",
            []() -> void
            {
                byte_t byte = 255;
                byte = clear_bits(byte);
                NERA_ASSERT(byte == 0);
                byte = clear_bits(byte);
                NERA_ASSERT(byte == 0);
                byte = bit_on(byte, 7);
                NERA_ASSERT(byte == 128);
                byte = clear_bits(byte);
                NERA_ASSERT(byte == 0);
            }
        );

        stop_tests();
    }

    void pointer_data_t()
    {
        start_tests("template <typename data_t>",
                    "class pointer_t<data_t>");

        run_test(
            "pointer_t();",
            []() -> void
            {
                pointer_t<int> pointer;
                NERA_ASSERT(pointer.data == nullptr);
                NERA_ASSERT(pointer.bytes == 0);
            }
        );
        run_test(
            "pointer_t(data_t* data, size_t bytes);",
            []() -> void
            {
                int num = 5;
                pointer_t<int> pointer_a(&num, sizeof(num));
                NERA_ASSERT(pointer_a.data == &num);
                NERA_ASSERT(pointer_a.bytes == sizeof(int));

                // array decays into pointer, no & operator
                int nums[5];
                pointer_t<int> pointer_b(nums, sizeof(nums));
                NERA_ASSERT(pointer_b.data == nums);
                NERA_ASSERT(pointer_b.bytes == sizeof(int) * 5);

                struct test_t { int a = 16; int b = 32; int c = 64; } test;
                pointer_t<test_t> pointer_c(&test, sizeof(test));
                NERA_ASSERT(pointer_c.data == &test);
                NERA_ASSERT(pointer_c.bytes == sizeof(test_t));
            }
        );
        run_test(
            "pointer_t(data_t& data);",
            []() -> void
            {
                char letter = 'c';
                pointer_t<char> pointer_a(letter);
                NERA_ASSERT(pointer_a.data == &letter);
                NERA_ASSERT(pointer_a.bytes == sizeof(letter));
                NERA_ASSERT(pointer_a.bytes == sizeof(char));

                // arrays decay into pointer, can't reference, so needs sizeof
                char letters[3];
                pointer_t<char> pointer_b(letters, sizeof(letters));
                NERA_ASSERT(pointer_b.data == letters);
                NERA_ASSERT(pointer_b.bytes == sizeof(letters));
                NERA_ASSERT(pointer_b.bytes == sizeof(char) * 3);

                struct test_t { char a = 'a'; char b = 'b'; char c = 'c'; } test;
                pointer_t<test_t> pointer_c(test);
                NERA_ASSERT(pointer_c.data == &test);
                NERA_ASSERT(pointer_c.bytes == sizeof(test));
                NERA_ASSERT(pointer_c.bytes == sizeof(test_t));
            }
        );

        new_line();
        run_test(
            "pointer_t(const pointer_t<data_t>& other);",
            []() -> void
            {
                struct test_t { int a = 16; int b = 32; int c = 64; } test;

                pointer_t<test_t> pointer_a(test);
                NERA_ASSERT(pointer_a.data == &test);
                NERA_ASSERT(pointer_a.bytes == sizeof(test));

                pointer_t<test_t> pointer_b(pointer_a);
                NERA_ASSERT(pointer_a.data == &test);
                NERA_ASSERT(pointer_a.bytes == sizeof(test));
                NERA_ASSERT(pointer_b.data == &test);
                NERA_ASSERT(pointer_b.bytes == sizeof(test));

                pointer_t<void> pointer_c(test);
                NERA_ASSERT(pointer_c.data == &test);
                NERA_ASSERT(pointer_c.bytes == sizeof(test));

                // void will use the regular copy constructor just fine.
                pointer_t<test_t> pointer_d(pointer_c);
                NERA_ASSERT(pointer_c.data == &test);
                NERA_ASSERT(pointer_c.bytes == sizeof(test));
                NERA_ASSERT(pointer_d.data == &test);
                NERA_ASSERT(pointer_d.bytes == sizeof(test));

                // will not compile. test_t2 shall not construct with test_t!
                // this *would* compile if we had an explicit void copy constructor,
                // because pointer_t<data_t> implicitly casts to pointer_t<void>
                /*struct test_t2 { double a = 7.0; } test2;
                pointer_t<test_t2> pointer_e(pointer_d);*/
            }
        );

        new_line();
        run_test(
            "pointer_t(pointer_t<data_t>&& other);",
            []() -> void
            {
                struct test_t { int a = 16; int b = 32; int c = 64; } test;

                pointer_t<test_t> pointer_a(test);
                NERA_ASSERT(pointer_a.data == &test);
                NERA_ASSERT(pointer_a.bytes == sizeof(test));

                pointer_t<test_t> pointer_b(std::move(pointer_a));
                NERA_ASSERT(pointer_a.data == nullptr);
                NERA_ASSERT(pointer_a.bytes == 0);
                NERA_ASSERT(pointer_b.data == &test);
                NERA_ASSERT(pointer_b.bytes == sizeof(test));

                // will not compile. test_t2 shall not construct with test_t!
                /*struct test_t2 { double a = 7.0; } test2;
                pointer_t<test_t2> pointer_e(std::move(pointer_b));*/
            }
        );
        run_test(
            "pointer_t(pointer_t<void>&& other);",
            []() -> void
            {
                struct test_t { int a = 16; int b = 32; int c = 64; } test;

                pointer_t<void> pointer_c(test);
                NERA_ASSERT(pointer_c.data == &test);
                NERA_ASSERT(pointer_c.bytes == sizeof(test));

                // needs an explicit void move constructor to work on pointer_c.
                // Maybe a hidden cast becomes a new rvalue, ignoring pointer_c?
                pointer_t<test_t> pointer_d(std::move(pointer_c));
                NERA_ASSERT(pointer_c.data == nullptr);
                NERA_ASSERT(pointer_c.bytes == 0);
                NERA_ASSERT(pointer_d.data == &test);
                NERA_ASSERT(pointer_d.bytes == sizeof(test));
            }
        );

        new_line();
        run_test(
            "pointer_t<data_t>& operator=(const pointer_t<data_t>& other);",
            []() -> void
            {
                struct test_t { int a = 16; int b = 32; int c = 64; } test;

                pointer_t<test_t> pointer_a(test);
                NERA_ASSERT(pointer_a.data == &test);
                NERA_ASSERT(pointer_a.bytes == sizeof(test));

                pointer_t<test_t> pointer_b;
                NERA_ASSERT(pointer_b.data == nullptr);
                NERA_ASSERT(pointer_b.bytes == 0);

                pointer_b = pointer_a;
                NERA_ASSERT(pointer_a.data == &test);
                NERA_ASSERT(pointer_a.bytes == sizeof(test));
                NERA_ASSERT(pointer_b.data == &test);
                NERA_ASSERT(pointer_b.bytes == sizeof(test));

                pointer_t<void> pointer_c(test);
                NERA_ASSERT(pointer_c.data == &test);
                NERA_ASSERT(pointer_c.bytes == sizeof(test));

                pointer_t<test_t> pointer_d;
                NERA_ASSERT(pointer_d.data == nullptr);
                NERA_ASSERT(pointer_d.bytes == 0);

                pointer_d = pointer_c;
                NERA_ASSERT(pointer_c.data == &test);
                NERA_ASSERT(pointer_c.bytes == sizeof(test));
                NERA_ASSERT(pointer_d.data == &test);
                NERA_ASSERT(pointer_d.bytes == sizeof(test));

                // will not compile. test_t2 shall not assign with test_t!
                // this *might* compile if we had an explicit void copy assigner,
                // because pointer_t<data_t> implicitly casts to pointer_t<void>
                /*struct test_t2 { double a = 7.0; } test2;
                pointer_t<test_t2> pointer_e = pointer_d;*/
            }
        );

        new_line();
        run_test(
            "pointer_t<data_t>& operator=(pointer_t<data_t>&& other);",
            []() -> void
            {
                struct test_t { int a = 16; int b = 32; int c = 64; } test;

                pointer_t<test_t> pointer_a(test);
                NERA_ASSERT(pointer_a.data == &test);
                NERA_ASSERT(pointer_a.bytes == sizeof(test));

                pointer_t<test_t> pointer_b;
                NERA_ASSERT(pointer_b.data == nullptr);
                NERA_ASSERT(pointer_b.bytes == 0);

                pointer_b = std::move(pointer_a);
                NERA_ASSERT(pointer_a.data == nullptr);
                NERA_ASSERT(pointer_a.bytes == 0);
                NERA_ASSERT(pointer_b.data == &test);
                NERA_ASSERT(pointer_b.bytes == sizeof(test));

                pointer_t<void> pointer_c(test);
                NERA_ASSERT(pointer_c.data == &test);
                NERA_ASSERT(pointer_c.bytes == sizeof(test));

                pointer_t<test_t> pointer_d;
                NERA_ASSERT(pointer_d.data == nullptr);
                NERA_ASSERT(pointer_d.bytes == 0);

                // doesn't need an explicit void move assigner to work on pointer_c?
                // see note above about the explicit void constructor.
                pointer_d = std::move(pointer_c);
                NERA_ASSERT(pointer_c.data == nullptr);
                NERA_ASSERT(pointer_c.bytes == 0);
                NERA_ASSERT(pointer_d.data == &test);
                NERA_ASSERT(pointer_d.bytes == sizeof(test));

                // will not compile. test_t2 shall not assign with test_t!
                /*struct test_t2 { double a = 7.0; } test2;
                pointer_t<test_t2> pointer_e = std::move(pointer_d);*/
            }
        );

        new_line();
        run_test(
            "~pointer_t();",
            []() -> void
            {
                int num = 5;
                pointer_t<int> pointer_a(num);
                NERA_ASSERT(pointer_a.data == &num);
                NERA_ASSERT(pointer_a.bytes == sizeof(num));
                pointer_a.~pointer_t();
                NERA_ASSERT(pointer_a.data == nullptr);
                NERA_ASSERT(pointer_a.bytes == 0);

                // array decays into pointer, no & operator
                int nums[5];
                pointer_t<int> pointer_b(nums, sizeof(nums));
                NERA_ASSERT(pointer_b.data == nums);
                NERA_ASSERT(pointer_b.bytes == sizeof(int) * 5);
                pointer_b.~pointer_t();
                NERA_ASSERT(pointer_b.data == nullptr);
                NERA_ASSERT(pointer_b.bytes == 0);

                struct test_t { int a = 16; int b = 32; int c = 64; } test;
                pointer_t<test_t> pointer_c(test);
                NERA_ASSERT(pointer_c.data == &test);
                NERA_ASSERT(pointer_c.bytes == sizeof(test));
                pointer_c.~pointer_t();
                NERA_ASSERT(pointer_c.data == nullptr);
                NERA_ASSERT(pointer_c.bytes == 0);
            }
        );

        new_line();
        run_test(
            "size_t count();",
            []() -> void
            {
                bool bools[24];
                pointer_t<bool> pointer_a(bools, sizeof(bools));
                NERA_ASSERT(pointer_a.data == bools);
                NERA_ASSERT(pointer_a.bytes == sizeof(bool) * 24);
                NERA_ASSERT(pointer_a.count() == 24);

                word_t words[12];
                pointer_t<word_t> pointer_b(words, sizeof(words));
                NERA_ASSERT(pointer_b.data == words);
                NERA_ASSERT(pointer_b.bytes == sizeof(word_t) * 12);
                NERA_ASSERT(pointer_b.count() == 12);
            }
        );

        new_line();
        run_test(
            "operator pointer_t<void>& ();",
            []() -> void
            {
                char letter = 'c';
                pointer_t<char> pointer_a(letter);
                NERA_ASSERT(pointer_a.data == &letter);
                NERA_ASSERT(pointer_a.bytes == sizeof(letter));

                pointer_t<void> pointer_b(pointer_a);
                NERA_ASSERT(pointer_b == pointer_a);
                NERA_ASSERT(pointer_b.data == pointer_a.data);
                NERA_ASSERT(pointer_b.bytes == pointer_a.bytes);

                pointer_t<void> pointer_c = pointer_a;
                NERA_ASSERT(pointer_c == pointer_a);
                NERA_ASSERT(pointer_c.data == pointer_a.data);
                NERA_ASSERT(pointer_c.bytes == pointer_a.bytes);

                pointer_t<void>& pointer_d = pointer_a;
                NERA_ASSERT(pointer_d == pointer_a);
                NERA_ASSERT(pointer_d.data == pointer_a.data);
                NERA_ASSERT(pointer_d.bytes == pointer_a.bytes);

                // pointing to pointer_a should not equal pointer_a.
                pointer_t<void> pointer_e(&pointer_a, sizeof(pointer_a));
                NERA_ASSERT(pointer_e != pointer_a);
                NERA_ASSERT(pointer_e.data != pointer_a.data);
                NERA_ASSERT(pointer_e.bytes != pointer_a.bytes);
                NERA_ASSERT(pointer_e.data == &pointer_a);
                NERA_ASSERT(pointer_e.bytes == sizeof(pointer_a));

                pointer_t<void>* pointer_f = &pointer_d;
                NERA_ASSERT(*pointer_f == pointer_a);
                NERA_ASSERT(pointer_f->data == pointer_a.data);
                NERA_ASSERT(pointer_f->bytes == pointer_a.bytes);
            }
        );

        stop_tests();
    }

    void pointer_void_t()
    {
        start_tests("template <>",
                    "class pointer_t<void>");

        run_test(
            "pointer_t();",
            []() -> void
            {
                pointer_t<void> pointer;
                NERA_ASSERT(pointer.data == nullptr);
                NERA_ASSERT(pointer.bytes == 0);
            }
        );
        run_test(
            "pointer_t(void* data, size_t bytes);",
            []() -> void
            {
                int num = 5;
                pointer_t<void> pointer_a(&num, sizeof(num));
                NERA_ASSERT(pointer_a.data == &num);
                NERA_ASSERT(pointer_a.bytes == sizeof(int));

                // array decays into pointer, no & operator
                int nums[5];
                pointer_t<void> pointer_b(nums, sizeof(nums));
                NERA_ASSERT(pointer_b.data == nums);
                NERA_ASSERT(pointer_b.bytes == sizeof(int) * 5);

                struct test_t { int a = 16; int b = 32; int c = 64; } test;
                pointer_t<void> pointer_c(&test, sizeof(test));
                NERA_ASSERT(pointer_c.data == &test);
                NERA_ASSERT(pointer_c.bytes == sizeof(test_t));
            }
        );
        run_test(
            "template <typename data_t>",
            "pointer_t(data_t& data);",
            []() -> void
            {
                char letter = 'c';
                pointer_t<void> pointer_a(letter);
                NERA_ASSERT(pointer_a.data == &letter);
                NERA_ASSERT(pointer_a.bytes == sizeof(letter));
                NERA_ASSERT(pointer_a.bytes == sizeof(char));

                // arrays decay into pointer, can't reference, so needs sizeof
                char letters[3];
                pointer_t<void> pointer_b(letters, sizeof(letters));
                NERA_ASSERT(pointer_b.data == letters);
                NERA_ASSERT(pointer_b.bytes == sizeof(letters));
                NERA_ASSERT(pointer_b.bytes == sizeof(char) * 3);

                struct test_t { char a = 'a'; char b = 'b'; char c = 'c'; } test;
                pointer_t<void> pointer_c(test);
                NERA_ASSERT(pointer_c.data == &test);
                NERA_ASSERT(pointer_c.bytes == sizeof(test));
                NERA_ASSERT(pointer_c.bytes == sizeof(test_t));
            }
        );

        new_line();
        run_test(
            "template <typename data_t>",
            "pointer_t(pointer_t<data_t>& other);",
            []() -> void
            {
                struct test_t { int a = 16; int b = 32; int c = 64; } test;

                pointer_t<test_t> pointer_a(test);
                NERA_ASSERT(pointer_a.data == &test);
                NERA_ASSERT(pointer_a.bytes == sizeof(test));

                pointer_t<void> pointer_b(pointer_a);
                NERA_ASSERT(pointer_a.data == &test);
                NERA_ASSERT(pointer_a.bytes == sizeof(test));
                NERA_ASSERT(pointer_b.data == &test);
                NERA_ASSERT(pointer_b.bytes == sizeof(test));
            }
        );
        run_test(
            "pointer_t(const pointer_t<void>& other);",
            []() -> void
            {
                struct test_t { int a = 16; int b = 32; int c = 64; } test;

                pointer_t<void> pointer_a(test);
                NERA_ASSERT(pointer_a.data == &test);
                NERA_ASSERT(pointer_a.bytes == sizeof(test));

                pointer_t<void> pointer_b(pointer_a);
                NERA_ASSERT(pointer_a.data == &test);
                NERA_ASSERT(pointer_a.bytes == sizeof(test));
                NERA_ASSERT(pointer_b.data == &test);
                NERA_ASSERT(pointer_b.bytes == sizeof(test));
            }
        );

        new_line();
        run_test(
            "template <typename data_t>",
            "pointer_t(pointer_t<data_t>&& other);",
            []() -> void
            {
                struct test_t { int a = 16; int b = 32; int c = 64; } test;

                // this too needs it's own constructor to work properly
                pointer_t<test_t> pointer_c(test);
                NERA_ASSERT(pointer_c.data == &test);
                NERA_ASSERT(pointer_c.bytes == sizeof(test));

                pointer_t<void> pointer_d(std::move(pointer_c));
                NERA_ASSERT(pointer_c.data == nullptr);
                NERA_ASSERT(pointer_c.bytes == 0);
                NERA_ASSERT(pointer_d.data == &test);
                NERA_ASSERT(pointer_d.bytes == sizeof(test));
            }
        );
        run_test(
            "pointer_t(pointer_t<void>&& other);",
            []() -> void
            {
                struct test_t { int a = 16; int b = 32; int c = 64; } test;

                pointer_t<void> pointer_a(test);
                NERA_ASSERT(pointer_a.data == &test);
                NERA_ASSERT(pointer_a.bytes == sizeof(test));

                pointer_t<void> pointer_b(std::move(pointer_a));
                NERA_ASSERT(pointer_a.data == nullptr);
                NERA_ASSERT(pointer_a.bytes == 0);
                NERA_ASSERT(pointer_b.data == &test);
                NERA_ASSERT(pointer_b.bytes == sizeof(test));
            }
        );

        new_line();
        run_test(
            "pointer_t<void>& operator=(const pointer_t<void>& other);",
            []() -> void
            {
                struct test_t { int a = 16; int b = 32; int c = 64; } test;

                pointer_t<void> pointer_a(test);
                NERA_ASSERT(pointer_a.data == &test);
                NERA_ASSERT(pointer_a.bytes == sizeof(test));

                pointer_t<void> pointer_b;
                NERA_ASSERT(pointer_b.data == nullptr);
                NERA_ASSERT(pointer_b.bytes == 0);

                pointer_b = pointer_a;
                NERA_ASSERT(pointer_a.data == &test);
                NERA_ASSERT(pointer_a.bytes == sizeof(test));
                NERA_ASSERT(pointer_b.data == &test);
                NERA_ASSERT(pointer_b.bytes == sizeof(test));

                pointer_t<test_t> pointer_c(test);
                NERA_ASSERT(pointer_c.data == &test);
                NERA_ASSERT(pointer_c.bytes == sizeof(test));

                pointer_t<void> pointer_d;
                NERA_ASSERT(pointer_d.data == nullptr);
                NERA_ASSERT(pointer_d.bytes == 0);

                // works without the need for a separate constructor
                pointer_d = pointer_c;
                NERA_ASSERT(pointer_c.data == &test);
                NERA_ASSERT(pointer_c.bytes == sizeof(test));
                NERA_ASSERT(pointer_d.data == &test);
                NERA_ASSERT(pointer_d.bytes == sizeof(test));
            }
        );

        new_line();
        run_test(
            "template <typename data_t>",
            "pointer_t<void>& operator=(pointer_t<data_t>&& other);",
            []() -> void
            {
                struct test_t { int a = 16; int b = 32; int c = 64; } test;

                pointer_t<test_t> pointer_c(test);
                NERA_ASSERT(pointer_c.data == &test);
                NERA_ASSERT(pointer_c.bytes == sizeof(test));

                pointer_t<void> pointer_d;
                NERA_ASSERT(pointer_d.data == nullptr);
                NERA_ASSERT(pointer_d.bytes == 0);

                // this too needs its own move assigner, unlike <data_t>
                pointer_d = std::move(pointer_c);
                NERA_ASSERT(pointer_c.data == nullptr);
                NERA_ASSERT(pointer_c.bytes == 0);
                NERA_ASSERT(pointer_d.data == &test);
                NERA_ASSERT(pointer_d.bytes == sizeof(test));
            }
        );
        run_test(
            "pointer_t<void>& operator=(pointer_t<void>&& other);",
            []() -> void
            {
                struct test_t { int a = 16; int b = 32; int c = 64; } test;

                pointer_t<void> pointer_a(test);
                NERA_ASSERT(pointer_a.data == &test);
                NERA_ASSERT(pointer_a.bytes == sizeof(test));

                pointer_t<void> pointer_b;
                NERA_ASSERT(pointer_b.data == nullptr);
                NERA_ASSERT(pointer_b.bytes == 0);

                pointer_b = std::move(pointer_a);
                NERA_ASSERT(pointer_a.data == nullptr);
                NERA_ASSERT(pointer_a.bytes == 0);
                NERA_ASSERT(pointer_b.data == &test);
                NERA_ASSERT(pointer_b.bytes == sizeof(test));
            }
        );

        new_line();
        run_test(
            "~pointer_t();",
            []() -> void
            {
                int num = 5;
                pointer_t<void> pointer_a(num);
                NERA_ASSERT(pointer_a.data == &num);
                NERA_ASSERT(pointer_a.bytes == sizeof(num));
                pointer_a.~pointer_t();
                NERA_ASSERT(pointer_a.data == nullptr);
                NERA_ASSERT(pointer_a.bytes == 0);

                // array decays into pointer, no & operator
                int nums[5];
                pointer_t<void> pointer_b(nums, sizeof(nums));
                NERA_ASSERT(pointer_b.data == nums);
                NERA_ASSERT(pointer_b.bytes == sizeof(int) * 5);
                pointer_b.~pointer_t();
                NERA_ASSERT(pointer_b.data == nullptr);
                NERA_ASSERT(pointer_b.bytes == 0);

                struct test_t { int a = 16; int b = 32; int c = 64; } test;
                pointer_t<void> pointer_c(test);
                NERA_ASSERT(pointer_c.data == &test);
                NERA_ASSERT(pointer_c.bytes == sizeof(test));
                pointer_c.~pointer_t();
                NERA_ASSERT(pointer_c.data == nullptr);
                NERA_ASSERT(pointer_c.bytes == 0);
            }
        );

        new_line();
        run_test(
            "template <typename data_t>",
            "operator pointer_t<data_t>& ();",
            []() -> void
            {
                char letter = 'c';
                pointer_t<void> pointer_a(letter);
                NERA_ASSERT(pointer_a.data == &letter);
                NERA_ASSERT(pointer_a.bytes == sizeof(letter));

                pointer_t<char> pointer_b(pointer_a);
                NERA_ASSERT(pointer_b == pointer_a);
                NERA_ASSERT(pointer_b.data == pointer_a.data);
                NERA_ASSERT(pointer_b.bytes == pointer_a.bytes);

                pointer_t<char> pointer_c = pointer_a;
                NERA_ASSERT(pointer_c == pointer_a);
                NERA_ASSERT(pointer_c.data == pointer_a.data);
                NERA_ASSERT(pointer_c.bytes == pointer_a.bytes);

                pointer_t<char>& pointer_d = pointer_a;
                NERA_ASSERT(pointer_d == pointer_a);
                NERA_ASSERT(pointer_d.data == pointer_a.data);
                NERA_ASSERT(pointer_d.bytes == pointer_a.bytes);

                pointer_t<char>* pointer_e = &pointer_d;
                NERA_ASSERT(*pointer_e == pointer_a);
                NERA_ASSERT(pointer_e->data == pointer_a.data);
                NERA_ASSERT(pointer_e->bytes == pointer_a.bytes);
            }
        );

        stop_tests();
    }

    void pointer_friend()
    {
        start_tests("pointer_t<data_t> friend,",
                    "pointer_t<void> friend");

        run_test(
            "template <typename data_t1, typename data_t2>",
            "friend bool operator ==(const pointer_t<data_t1>& pointer_a,",
            "                        const pointer_t<data_t2> & pointer_b);",
            []() -> void
            {
                int num = 5;
                pointer_t<int> pointer_a(num);
                NERA_ASSERT(pointer_a.data == &num);
                NERA_ASSERT(pointer_a.bytes == sizeof(num));

                pointer_t<int> pointer_b(num);
                NERA_ASSERT(pointer_b.data == &num);
                NERA_ASSERT(pointer_b.bytes == sizeof(num));
                NERA_ASSERT(pointer_b == pointer_a);
                NERA_ASSERT(&pointer_b != &pointer_a);

                pointer_t<int>* pointer_c = &pointer_a;
                NERA_ASSERT(pointer_c == &pointer_a);
                NERA_ASSERT(*pointer_c == pointer_a);

                pointer_t<int>& pointer_d = pointer_a;
                NERA_ASSERT(pointer_d == pointer_a);
                NERA_ASSERT(&pointer_d == &pointer_a);

                pointer_t<void> pointer_e(num);
                NERA_ASSERT(pointer_e.data == &num);
                NERA_ASSERT(pointer_e.bytes == sizeof(num));
                NERA_ASSERT(pointer_e == pointer_a);

                pointer_t<void>* pointer_f = &pointer_e;
                NERA_ASSERT(pointer_f->data == &num);
                NERA_ASSERT(pointer_f->bytes == sizeof(num));
                NERA_ASSERT(*pointer_f == pointer_a);

                pointer_t<void>* pointer_g = reinterpret_cast<pointer_t<void>*>(&pointer_a);
                NERA_ASSERT(pointer_g->data == &num);
                NERA_ASSERT(pointer_g->bytes == sizeof(num));
                NERA_ASSERT(*pointer_g == pointer_a);

                // this does not do what would be expected. it constructs a new
                // pointer_t<void> and doesn't copy anything like it's supposed to.
                // this may be undefined behavior, so stick to reinterpret_cast
                pointer_t<void>* pointer_h = &static_cast<pointer_t<void>>(pointer_a);
                NERA_ASSERT(*pointer_h != pointer_a);
                NERA_ASSERT(pointer_h->data == nullptr);
                NERA_ASSERT(pointer_h->bytes == 0);
            }
        );

        run_test(
            "template <typename data_t1, typename data_t2>",
            "friend bool operator !=(const pointer_t<data_t1>& pointer_a,",
            "                        const pointer_t<data_t2> & pointer_b);",
            []() -> void
            {
                int num_a = 5;
                pointer_t<int> pointer_a(num_a);
                NERA_ASSERT(pointer_a.data == &num_a);
                NERA_ASSERT(pointer_a.bytes == sizeof(num_a));

                int num_b = 6;
                pointer_t<int> pointer_b(num_b);
                NERA_ASSERT(pointer_b.data == &num_b);
                NERA_ASSERT(pointer_b.bytes == sizeof(num_b));
                NERA_ASSERT(pointer_b != pointer_a);

                pointer_t<int> pointer_c(pointer_a);
                NERA_ASSERT(pointer_c == pointer_a);
                NERA_ASSERT(pointer_c != pointer_b);
                NERA_ASSERT(&pointer_c != &pointer_a);
                NERA_ASSERT(&pointer_c != &pointer_b);

                pointer_t<int>* pointer_d = &pointer_a;
                NERA_ASSERT(pointer_d == &pointer_a);
                NERA_ASSERT(*pointer_d == pointer_a);
                NERA_ASSERT(pointer_d != &pointer_b);
                NERA_ASSERT(*pointer_d != pointer_b);

                pointer_t<int>& pointer_e = pointer_b;
                NERA_ASSERT(pointer_e != pointer_a);
                NERA_ASSERT(pointer_e == pointer_b);
                NERA_ASSERT(&pointer_e == &pointer_b);
                NERA_ASSERT(&pointer_e != &pointer_a);

                pointer_t<void> pointer_f(num_a);
                NERA_ASSERT(pointer_f.data == &num_a);
                NERA_ASSERT(pointer_f.bytes == sizeof(num_a));
                NERA_ASSERT(pointer_f == pointer_a);
                NERA_ASSERT(pointer_f != pointer_b);
                NERA_ASSERT(pointer_f == pointer_c);
                NERA_ASSERT(pointer_f == *pointer_d);
                NERA_ASSERT(pointer_f != pointer_e);
            }
        );

        stop_tests();
    }

    void allocator()
    {
        start_tests("class allocator_t");

        run_test(
            "static const allocator_t& mallocator();",
            []() -> void
            {
                // need to test each individual method too
            }
        );

        run_test(
            "static const allocator_t& callocator();",
            []() -> void
            {
                // need to test each individual method too
            }
        );

        new_line();
        run_test(
            "static bool copy(pointer_t<void>& from, pointer_t<void>& to);",
            []() -> void
            {

            }
        );

        run_test(
            "static bool zero(pointer_t<void>& pointer);",
            []() -> void
            {

            }
        );

        new_line();
        run_test(
            "allocator_t(allocate_f allocate,",
            "            reallocate_f reallocate,",
            "            deallocate_f deallocate,",
            "            bool initializes_to_zero);",
            []() -> void
            {
                static byte_t heap[64];
                static size_t cursor = 0;

                auto allocate = [](pointer_t<void>& pointer, size_t bytes) -> bool
                {
                    if (cursor + bytes <= sizeof(heap)) {
                        pointer.data = &heap[cursor];
                        pointer.bytes = bytes;
                        cursor += bytes;
                        return true;
                    } else {
                        return false; // out of memory.
                    }
                };

                auto reallocate = [](pointer_t<void>& pointer, size_t bytes) -> bool
                {
                    return false; // this allocator_t doesn't reallocate.
                };

                auto deallocate = [](pointer_t<void>& pointer) -> bool
                {
                    return false; // this allocator_t doesn't deallocate.
                };

                const allocator_t my_heap = allocator_t(allocate, reallocate, deallocate, false);
                NERA_ASSERT(my_heap.allocate == allocate);
                NERA_ASSERT(my_heap.reallocate == reallocate);
                NERA_ASSERT(my_heap.deallocate == deallocate);

                pointer_t<uint8_t> u8s;
                NERA_ASSERT(my_heap.allocate(u8s, sizeof(uint8_t) * 2));
                NERA_ASSERT(u8s.data == reinterpret_cast<uint8_t*>(&heap[0]));
                NERA_ASSERT(u8s.bytes == sizeof(uint8_t) * 2);

                pointer_t<uint16_t> u16s;
                NERA_ASSERT(my_heap.allocate(u16s, sizeof(uint16_t) * 3));
                NERA_ASSERT(u16s.data == reinterpret_cast<uint16_t*>(&heap[u8s.bytes]));
                NERA_ASSERT(u16s.bytes == sizeof(uint16_t) * 3);

                pointer_t<uint32_t> u32s;
                NERA_ASSERT(my_heap.allocate(u32s, sizeof(uint32_t) * 4));
                NERA_ASSERT(u32s.data == reinterpret_cast<uint32_t*>(&heap[u8s.bytes + u16s.bytes]));
                NERA_ASSERT(u32s.bytes == sizeof(uint32_t) * 4);

                pointer_t<uint64_t> u64s;
                NERA_ASSERT(my_heap.allocate(u64s, sizeof(uint64_t) * 5));
                NERA_ASSERT(u64s.data == reinterpret_cast<uint64_t*>(&heap[u8s.bytes + u16s.bytes + u32s.bytes]));
                NERA_ASSERT(u64s.bytes == sizeof(uint64_t) * 5);

                pointer_t<byte_t> fail;
                NERA_ASSERT(my_heap.allocate(fail, sizeof(byte_t)) ==  false);
                NERA_ASSERT(fail.data == nullptr);
                NERA_ASSERT(fail.bytes == 0);

                u8s.data[0] = 1;
                u8s.data[1] = 2;

                u16s.data[0] = 3;
                u16s.data[1] = 4;
                u16s.data[2] = 5;

                u32s.data[0] = 6;
                u32s.data[1] = 7;
                u32s.data[2] = 8;
                u32s.data[3] = 9;

                u64s.data[0] = 10;
                u64s.data[1] = 11;
                u64s.data[2] = 12;
                u64s.data[3] = 13;
                u64s.data[4] = 14;

                // we don't want allocated sectors overwriting each other
                NERA_ASSERT(u8s.data[0] == 1);
                NERA_ASSERT(u8s.data[1] == 2);

                NERA_ASSERT(u16s.data[0] == 3);
                NERA_ASSERT(u16s.data[1] == 4);
                NERA_ASSERT(u16s.data[2] == 5);

                NERA_ASSERT(u32s.data[0] == 6);
                NERA_ASSERT(u32s.data[1] == 7);
                NERA_ASSERT(u32s.data[2] == 8);
                NERA_ASSERT(u32s.data[3] == 9);

                NERA_ASSERT(u64s.data[0] == 10);
                NERA_ASSERT(u64s.data[1] == 11);
                NERA_ASSERT(u64s.data[2] == 12);
                NERA_ASSERT(u64s.data[3] == 13);
                NERA_ASSERT(u64s.data[4] == 14);

                /*for (uint8_t* ptr = u8s.data, *end = ptr + u8s.count(); ptr < end; ptr += 1) {
                    printf("%u ", *ptr);
                }
                for (uint16_t* ptr = u16s.data, *end = ptr + u16s.count(); ptr < end; ptr += 1) {
                    printf("%u ", *ptr);
                }
                for (uint32_t* ptr = u32s.data, *end = ptr + u32s.count(); ptr < end; ptr += 1) {
                    printf("%u ", *ptr);
                }
                for (uint64_t* ptr = u64s.data, *end = ptr + u64s.count(); ptr < end; ptr += 1) {
                    printf("%llu ", *ptr);
                }
                printf("\n");*/
            }
        );

        stop_tests();
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

        if (true) {
            uint32_t num = 0;
            pointer_t<uint32_t> pointer(num);
            constexpr uint32_t max = static_cast<uint16_t>(~0) + 1;
            for (; num < max; num += 1) {
                vector_t<char> binary = to_binary(pointer);
                vector_t<char> hexadecimal = to_hexadecimal(pointer);
                printf("%s %s\n",
                       binary.memory.pointer.data,
                       hexadecimal.memory.pointer.data);
            }
        }
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

    inline void divider()
    {
        for (size_t idx = 0; idx < 64; idx += 1) {
            putc('.', stdout);
            std::this_thread::sleep_for(std::chrono::milliseconds(12));
        } printf("\n\n");
    }

    inline char get_one_char()
    {
        char result = getc(stdin);
        if (result != '\n') {
            while (getc(stdin) != '\n');
        }

        return result;
    }

    void manual_mode()
    {
        //divider(); tests::utils(); get_one_char();
        divider(); tests::utils_bits(); get_one_char();
        divider(); tests::pointer_data_t(); get_one_char();
        divider(); tests::pointer_void_t(); get_one_char();
        divider(); tests::pointer_friend(); get_one_char();
        divider(); tests::allocator(); get_one_char();
        //divider(); tests::memory(); get_one_char();
        //divider(); tests::vector(); get_one_char();
        //divider(); tests::hasher(); get_one_char();
        //divider(); tests::hashmap(); get_one_char();

        divider(); printf("success!\n"); get_one_char();
    }

    void automatic_mode()
    {
        //tests::utils();
        tests::utils_bits();
        tests::pointer_data_t();
        tests::pointer_void_t();
        tests::pointer_friend();
        tests::allocator();
        //tests::memory();
        //tests::vector();
        //tests::hasher();
        //tests::hashmap();

        printf("\nsuccess!\n");
    }

}}

int main(int arg_count, char* args[])
{
    using namespace nera;

    tests::divider();
    printf("This test suite will rigorously test Nera, a library\n"
           "containing general types that will combine into a new\n"
           "regular expression engine. The types will be made with\n"
           "reuse in mind.\n"
           "The suite will assert on any detected failures.\n\n");
    tests::divider();

    printf("[m]anual mode, or [a]utomatic?\n\n");

    if (tests::get_one_char() == 'm') {
        tests::manual_mode();
    } else {
        tests::automatic_mode();
    }
    
    return EXIT_SUCCESS;
}
