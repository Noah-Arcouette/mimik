# LZD ( Lempel-Ziv Dual )

## Abstract

The goal of LZD is to combine a LZ78 dictionary with a LZ77 window. It does this by maintaining three data structures: a window, a history, and a pre-agreed diction. It also allows for matches to be longer by mixing all three into a traditional LZ pair.

## Format

As stated above, each match is a traditional LZ pair. This means there is a *dictionary* match, we will refer to it as the base, then an addition; the combination of the two being the final match. In LZ77 the base is a sliding window, and in LZ78 it is a constructed, true, dictionary. In LZD the base may be an explicit static dictionary, a prior match, or a sliding window. What sets LZD apart from other LZ family compressors is that the addition is also a *dictionary* match, meaning that the explicit dictionary **must** provide, at least, all single length elements because there are no literal matches. The base and addition, in LZD, are the same but allow for better matching because the base match may be made smaller to allow for a larger total match.

## Data Structures

### Window

The window is the largest amount of data the compressor is willing to remember after the current message element. The window shall be accessed via a negative offset from the start of the window and the length of the given, base or addition, match. 

Matches shall be pushed to the start of the window after the representation is emitted. The window shall be initialized with all zeros.

### History

The history is the largest amount of prior matches the compressor is willing to remember. The history shall be accessed via a negative offset from the end of the history.

Matches shall be pushed to the end of the history after the representation is emitted.

### Dictionary

The dictionary is a given, static, diction provided by the compressor or user. The dictionary must be provided at compression or decompression time because it shall not be included in the final message. The dictionary entries shall be accessed via a pre-agreed codeword.

The dictionary must be pre-agreed and must never be written to. The dictionary must include all single message element characters.

## Compression

An example compressor will find all possible LZ pairs for a given message. Then it will emit the largest match, with the smallest representation as a secondary constraint. The compressor will add all matches to the window and history. Remember the compressor may use the window, history, or the pre-agreed diction in either the base or addition allowing for better total match lengths.

It is recommended to use entropy encoding in combination with LZD.


# Stream Format

All sizes must be pre-agreed. The stream shall be a series of: identifiers, bases, and additions. An optional stream header may be provided.

## Header

```C
struct LZD_Stream_Header
{
    char magic[4];          // "LZD\0"
    unsigned char revision; // 0
    char dictionary[256];   // the name of the dictionary, may be NULL for the preset
    unsigned char diction;  // length of a dictionary code word, in bits
    unsigned char offset;   // length of an offset, in bits
    unsigned char length;   // length of a length, in bits
    unsigned char history;  // length of a history offset, in bits
};
```

## Identifiers

The identifiers shall two two bit fields, the first describing the base and the second describing the addition.

## 00 : End of Message

The processor shall not consider all data after this identifier.

## 01 : Select Pair

The selection pair shall have offset and length. The true length shall three plus the given length. The true offset shall the given offset plus length.

## 10 : History Selection

The history selection shall give an index into the history.

## 11 : Dictionary Selection

The dictionary selection shall give an index into the dictionary. The dictionary shall be initialized with all single bytes, in order, unless otherwise stated.

## Number Encoding

Unless otherwise stated, the size of each number category shall be:

| Category | Size, in bits |
| -------- | ------------- |
|  diction | 8             |
|  offset  | 16            |
|  length  | 8             |
|  history | 12            |

Unless otherwise stated, all numbers shall be encoded as such:

For each number category break the number into bytes, big endian, then run a move to front transform. Then fit the transformed number into one of these templates.

|    Template   |  Range |
| ------------- | ------ |
| 0          xx |  0-  3 |
| 10       xxxx |  4- 19 |
| 110   xx xxxx | 20- 83 |
| 111 xxxx xxxx | 84-255 |

Where x is the index into the range.

## Example

Input: `Hello, world!Hello, world!Hello, world!` 39 bytes

diction size: 1 byte
offset size:  1 byte
length size:  1 byte
history size: 1 byte

Output:
```
dict:dict 'H' 'e'
dict:dict 'l' 'l'
dict:dict 'o' ','
dict:dict ' ' 'w'
dict:dict 'o' 'r'
dict:dict 'l' 'd'
dict:pair '!' (-12,12)
hist:dict  0  '!'
eom
```

Binary Output:
```
11 11 110 11 0100 111 0001 0001
11 11 111 0001 1000 0 00
11 11 111 0001 1011 110 01 1100
11 11 110 01 0001 111 0010 0011
11 11 0 11 111 0001 1111
11 11 10 0001 111 0001 0101
11 01 110 01 0101 0 00 10 0101
10 11 0 00 0 00
00
```

Hex Output: 21 bytes
```
fd a7 11 fe 30 3f 8d e7
2f 23 c8 fd f1 ff 87 8a
ee 54 4b 60 00
```

Space savings: 46.16% ( 1-(21/39) )
Ratio:          1.86  (   39/21   )
