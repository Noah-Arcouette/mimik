#ifndef __LIB_LZ_DUAL_H__
#define __LIB_LZ_DUAL_H__
#include <stddef.h>

#define LZD_MATCH_TYPE_DICTION 0
#define LZD_MATCH_TYPE_WINDOW  1
struct LZD_Match
{
    size_t        size;
    unsigned char type;
    size_t        index;
};
struct __attribute__((__packed__)) LZD_Stream_Header
{
    char magic[4];          // "LZD\0"
    unsigned char revision; // 0
    char dictionary[256];   // the name of the dictionary, may be NULL for the preset
    unsigned char diction;  // length of a dictionary code word, in bits
    unsigned char offset;   // length of an offset, in bits
    unsigned char length;   // length of a length, in bits
    unsigned char history;  // length of a history offset, in bits
};
unsigned char *LZD_compress   (struct LZD_Stream_Header, const unsigned char *buff, size_t size, size_t *outsize);
unsigned char *LZD_decompress (struct LZD_Stream_Header, const unsigned char *buff, size_t size, size_t *outsize);

int  startDictionary (struct LZD_Stream_Header);
void stopDictionary  (void);
void findDictionary  (unsigned char *find);
int  matchDictionary (struct LZD_Match *);

int  startWindow (struct LZD_Stream_Header);
void stopWindow  (void);
void findWindow  (unsigned char *find);
int  matchWindow (struct LZD_Match *);
int  pushWindow  (unsigned char *buff, size_t size);


#endif
