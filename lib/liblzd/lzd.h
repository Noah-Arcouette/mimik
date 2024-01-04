#ifndef __LIB_LZ_DUAL_H__
#define __LIB_LZ_DUAL_H__
#include <stddef.h>

struct LZD_Options
{
    unsigned char off;
    unsigned char len;
    unsigned char dct;
    unsigned char hst;
};
int LZD_dumpOptions (struct LZD_Options,         unsigned char *buff, size_t size);
int LZD_readOptions (struct LZD_Options *, const unsigned char *buff, size_t size);

unsigned char *LZD_compress   (struct LZD_Options, const unsigned char *buff, size_t size, int *outsize);
unsigned char *LZD_decompress (struct LZD_Options, const unsigned char *buff, size_t size, int *outsize);

#endif
