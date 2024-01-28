#include "../mtf.h"
#include <stdio.h>
#include <assert.h>

#define TITLE() printf("liblzd/%s %d: ", __FILE__, __LINE__)

int
main (void)
{
    if (startMtf())
    {
        TITLE();
        puts("Failed to initialize move-to-front transform");
        return 1;
    }

    assert(encodeMtf(10) == 10);
    assert(encodeMtf( 1) ==  2);
    assert(encodeMtf(32) == 32);
    assert(encodeMtf( 2) ==  4);
    assert(encodeMtf( 1) ==  2);
    assert(encodeMtf( 8) == 10);
    assert(encodeMtf( 8) ==  0);
    assert(encodeMtf( 8) ==  0);
    assert(encodeMtf( 1) ==  1);

    stopMtf();

    TITLE();
    puts("\tConsistent");
}
