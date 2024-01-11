#ifndef __LZ_DUAL_CODING_H__
#define __LZ_DUAL_CODING_H__
#include <stddef.h>

struct cindex
{
    unsigned char bits;  // amount of used bits in the last byte
    int           index; // current index
};

static void
pushBit (struct cindex *idx, unsigned char *buff, unsigned char byte, unsigned char bits)
{
    // add upper
    // add lower
}

static void
encodeByte (struct cindex *idx, unsigned char *buff, unsigned char byte)
{
    // partition
    if (!(byte & 0b11111100))
    {
        // 0 000000--
        pushBit(idx, buff, 0,    1);
        pushBit(idx, buff, byte, 2);
    }
    else if (!(byte & 0b11110000))
    {
        // 10 0000----
        pushBit(idx, buff, 0b10, 2);
        pushBit(idx, buff, byte, 4);
    }
    else if (!(byte & 0b11000000))
    {
        // 110 00------
        pushBit(idx, buff, 0b110, 3);
        pushBit(idx, buff, byte,  6);
    }
    else
    {
        // 111 --------
        pushBit(idx, buff, 0b111, 3);
        pushBit(idx, buff, byte,  8);
    }

    // push bits
}

#endif
