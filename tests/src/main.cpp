/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "stdio.h"

#include "main.h"

namespace nera { namespace tests {

    void start_tests(const char* name)
    {
        printf("%s {\n", name);
    }

    void start_tests(const char* line_1, const char* line_2)
    {
        printf("%s\n", line_1);
        printf("%s {\n", line_2);
    }

    void new_line()
    {
        printf("\n");
    }

    void run_test(const char* name, void (*lambda)())
    {
        printf("    %s\n", name);
        lambda();
    }

    void run_test(const char* line_1, const char* line_2, void (*lambda)())
    {
        printf("    %s\n", line_1);
        printf("    %s\n", line_2);
        lambda();
    }

    void run_test(const char* line_1, const char* line_2, const char* line_3, void (*lambda)())
    {
        printf("    %s\n", line_1);
        printf("    %s\n", line_2);
        printf("    %s\n", line_3);
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

    tests::new_line();
    printf("This test suite will rigorously test Nera, a library\n"
           "containing general types that will combine into a new\n"
           "regular expression engine. The types will be made with\n"
           "reuse in mind.\n"
           "(The suite will assert on any detected failures.)\n");
    tests::new_line();

    tests::utils();
    tests::pointer_data_t();
    tests::pointer_void_t();
    tests::pointer_friend();
    tests::allocator();
    tests::memory();
    tests::vector();
    tests::hasher();
    tests::hashmap();

    printf("\nsuccess!\n");
    //getc(stdin);

    return 0;
}
