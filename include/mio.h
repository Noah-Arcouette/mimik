#ifndef __MIO_H__
#define __MIO_H__

// multibyte data is in little endian

#define MIO_MAGIC "\xe1MiO"
#define MIO_CURRENT_VERSION 0
#define MIO_HEADER_FLAG_LAST 1 // final header

// unknown values
#define MIO_ARCH_UNKNOWN   0
#define MIO_SYSTEM_UNKNOWN 0
#define MIO_ABI_UNKNOWN    0

typedef unsigned char MiO_byte;
struct MiO_Header
{
    MiO_byte magic[4]; // header magic number
    MiO_byte version;  // format version
    MiO_byte flags;    // header flags

    MiO_byte arch;            // architecture
    MiO_byte uarch;           // microarchitecture
    MiO_byte archFeatures[8]; // 64bit architecture feature bitmap

    MiO_byte system;         // operating system
    MiO_byte abi;            // application binary interface
    MiO_byte sysFeatures[8]; // 64bit operating system feature bitmap

    MiO_byte entry[64]; // C-string entry symbol
} __attribute__((packed));

#define MIO_SECTION_FLAG_PERMISSION_READ    1 // program readable section
#define MIO_SECTION_FLAG_PERMISSION_WRITE   2 // program writeable section
#define MIO_SECTION_FLAG_PERMISSION_EXECUTE 4 // program executable section
#define MIO_SECTION_FLAG_BSS                8 // section is allocated but not in object data, .bss
#define MIO_SECTION_FLAG_LAST              16 // last section
struct MiO_Section
{
    MiO_byte name  [64]; // section name
    MiO_byte offset[8];  // offset of section into file
    MiO_byte size  [8];  // size of section
    MiO_byte flags;
} __attribute__((packed));

#define MIO_DATA_FORMAT_RAW 1 // raw bytes
struct MiO_Data
{
    MiO_byte format;  // format of the data
    MiO_byte size[8]; // amount of data
    MiO_byte data[];
} __attribute__((packed));

#define MIO_LIB_NAME ".libraries"
#define MIO_LIB_TYPE_NEEDED   1 // needed for successful loading
#define MIO_LIB_TYPE_OPTIONAL 2 // not needed
struct MiO_Lib // libraries
{
    MiO_byte path[256]; // path/filename to libraries
    MiO_byte type;      // type of library
} __attribute__((packed));

#define MIO_SYMLIST_NAME ".symbols.list"
#define MIO_SYMLIST_TYPE_ABSOLUTE  0 // absolute symbol
#define MIO_SYMLIST_TYPE_BSS       1 // bss, uninitialized data ( offset only applies into uninitialized sections not normal sections ) MIO_SECTION_FLAG_ALLOC
#define MIO_SYMLIST_TYPE_ADDRESS   2 // address data, offset
#define MIO_SYMLIST_TYPE_FILE      3 // file symbol
#define MIO_SYMLIST_TYPE_MASK      3 // mask for symbol type
#define MIO_SYMLIST_GLOBAL         4 // global symbol, bit flag
struct MiO_SymList
{
    MiO_byte name[64]; // name of symbol
    MiO_byte size[8];  // size of symbol
    MiO_byte val [8];  // value/offset of symbol
    MiO_byte flags;    // the symbol type and flags
} __attribute__((packed));

#define MIO_RELOC_NAME ".relocations"
#define MIO_RELOC_FLAG_READ    1
#define MIO_RELOC_FLAG_WRITE   2
#define MIO_RELOC_FLAG_EXECUTE 4
struct MiO_Reloc
{
    MiO_byte name  [64]; // name of symbol to relocate
    MiO_byte offset[8];  // byte offset into file
    MiO_byte type;       // type of relocation format and flags, see architecture specific definitions
} __attribute__((packed));

#define MIO_MAP_NAME ".map"
#define MIO_MAP_FLAG_BSS 1 // map uninitialized symbols
struct MiO_Map
{
    MiO_byte flags;
    MiO_byte offset  [8]; // offset into file
    MiO_byte fsize   [8]; // amount of file data to copy
    MiO_byte virt    [8]; // virtual address, set to all ones for undefined
    MiO_byte physical[8]; // physical address, set to all ones for undefined
    MiO_byte align   [8]; // align undefined address to boundary
    MiO_byte size    [8]; // memory size
} __attribute__((packed));

#define MIO_SEG_NAME ".segments"
#define MIO_SEG_FLAG_BSS 1 // map uninitialized symbols
struct MiO_Seg
{
    MiO_byte flags;
    MiO_byte offset  [8]; // offset into file
    MiO_byte fsize   [8]; // amount of file data to copy
    MiO_byte segment;     // see architecture defined values
    MiO_byte physical[8]; // physical address, set to all ones for undefined
    MiO_byte align   [8]; // align undefined address to boundary
    MiO_byte size    [8]; // memory size
} __attribute__((packed));

#endif
