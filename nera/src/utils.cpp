#include "stdio.h"
#include "stdlib.h"

#include "nera/utils.h"

namespace nera {

    void assert(const char* assertion,
                const char* function,
                const char* file,
                int line)
    {
        printf("NERA_ASSERT: ( %s ) is not true!\n", assertion);
        printf("    in func: %s\n", function);
        printf("    in file: %s\n", file);
        printf("    on line: %i\n", line);
        getc(stdin);
        exit(EXIT_FAILURE);
    }

}
