#include <stdfil.h>

int main(int argc, char** argv)
{
    int* huge = zalloc(int, 0x400000000000000lu);
    zprintf("huge = %p\n", huge);
    *huge = 42;
    zprintf("*huge = %d\n", *huge);
    return 0;
}

