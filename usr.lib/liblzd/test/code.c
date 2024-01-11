#include <lzd.h>
#include <stdio.h>
#include "../coding.h"

int
main (void)
{
    struct cindex idx = { 0, -1 };
    unsigned char buff[256];

    pushBit(&idx, buff, 1, 1);
    pushBit(&idx, buff, 0, 1);
    pushBit(&idx, buff, 1, 1);
    pushBit(&idx, buff, 1, 1);
    pushBit(&idx, buff, 0, 1);
    pushBit(&idx, buff, 1, 1);
    pushBit(&idx, buff, 1, 1);
    pushBit(&idx, buff, 0, 1);
    encodeByte(&idx, buff, 0xef); // 111 11101111
    encodeByte(&idx, buff, 0x2f); // 110   101111
    encodeByte(&idx, buff, 0x0f); // 10      1111
    encodeByte(&idx, buff, 0x03); // 0         11

    for (int i = 0; i<=idx.index; i++)
    {
        for (unsigned int j = 0; j<8; j++)
        {
            printf("%d", (buff[i]>>(7-j))&1);
        }
        printf("\n");
    }

    return 0;
}
