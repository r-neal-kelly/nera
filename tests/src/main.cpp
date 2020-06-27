#include "stdio.h"

#include "main.h"

namespace nera { namespace tests {

    vector_t<int> Quick_Vector_Test()
    {
        return vector_t<int>();
    }

}}

int main()
{
    using namespace nera;

    vector_t<int> vector = tests::Quick_Vector_Test();

    printf("success!");

    return 0;
}
