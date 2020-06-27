#include "stdio.h"

#include "main.h"

namespace nera { namespace tests {

    void pointer()
    {
        NERA_TEST("pointer_t default constructor:",
                  {
                         pointer_t<void> pointer;
                         NERA_ASSERT(pointer.data == nullptr);
                         NERA_ASSERT(pointer.bytes == 0);
                  }
        );

        NERA_TEST("pointer_t user constructor:",
                  {
                         pointer_t<void> pointer(nullptr, 0);
                         NERA_ASSERT(pointer.data == nullptr);
                         NERA_ASSERT(pointer.bytes == 0);
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
    }

}}

int main()
{
    using namespace nera;

    tests::pointer();
    tests::allocator();
    tests::memory();
    tests::vector();

    printf("\nsuccess!\n");
    getc(stdin);

    return 0;
}
