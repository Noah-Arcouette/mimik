#ifndef __INCLUDE_STDINT_H__
#define __INCLUDE_STDINT_H__
#ifndef __mimik__
#	warning "Warning this is a mimik specific header file"
#endif

/// @see abi/x86-16
#ifdef __x86_16__
#define INT8_MIN   (-128)
#define INT8_MAX   (127)
#define UINT8_MAX  (255)
#define INT16_MIN  (-32768)
#define INT16_MAX  (32767)
#define UINT16_MAX (65535u)
#define INT32_MIN  (-2147483648l)
#define INT32_MAX  (2147483647l)
#define UINT32_MAX (4294967295lu)
#define INT64_MIN  (-9223372036854775808ll)
#define INT64_MAX  (9223372036854775807ll)
#define UINT64_MAX (18446744073709551615llu)
typedef char      int8_t;
typedef short     int16_t;
typedef long      int32_t;
typedef long long int64_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned long      uint32_t;
typedef unsigned long long uint64_t;

// int least
#define INT_LEAST8_MIN INT8_MIN
#define INT_LEAST8_MAX INT8_MAX
#define UINT_LEAST8_MAX UINT8_MAX
#define INT_LEAST16_MIN INT16_MIN
#define INT_LEAST16_MAX INT16_MAX
#define UINT_LEAST16_MAX UINT16_MAX
#define INT_LEAST32_MIN INT32_MIN
#define INT_LEAST32_MAX INT32_MAX
#define UINT_LEAST32_MAX UINT32_MAX
#define INT_LEAST64_MIN INT64_MIN
#define INT_LEAST64_MAX INT64_MAX
#define UINT_LEAST64_MAX UINT64_MAX

typedef char      int_least8_t;
typedef short     int_least16_t;
typedef long      int_least32_t;
typedef long long int_least64_t;
typedef unsigned char      uint_least8_t;
typedef unsigned short     uint_least16_t;
typedef unsigned long      uint_least32_t;
typedef unsigned long long uint_least64_t;

// int fast
#define INT_FAST8_MIN INT8_MIN
#define INT_FAST8_MAX INT8_MAX
#define UINT_FAST8_MAX UINT8_MAX
#define INT_FAST16_MIN INT16_MIN
#define INT_FAST16_MAX INT16_MAX
#define UINT_FAST16_MAX UINT16_MAX
#define INT_FAST32_MIN INT32_MIN
#define INT_FAST32_MAX INT32_MAX
#define UINT_FAST32_MAX UINT32_MAX
#define INT_FAST64_MIN INT64_MIN
#define INT_FAST64_MAX INT64_MAX
#define UINT_FAST64_MAX UINT64_MAX

typedef char      int_fast8_t;
typedef short     int_fast16_t;
typedef long      int_fast32_t;
typedef long long int_fast64_t;
typedef unsigned char      uint_fast8_t;
typedef unsigned short     uint_fast16_t;
typedef unsigned long      uint_fast32_t;
typedef unsigned long long uint_fast64_t;

// pointer, 16bit on x86 machines (not including segmentation of course)
#define INTPTR_MIN INT16_MIN
#define INTPTR_MAX INT16_MAX
#define UINTPTR_MAX UINT16_MAX
typedef short intptr_t;
typedef unsigned short uintptr_t;

// int max
#define INTMAX_MIN INT64_MIN
#define INTMAX_MAX INT64_MAX
#define UINTMAX_MAX UINT64_MAX
typedef long long intmax_t;
typedef unsigned long long uintmax_t;

// other mins and maxs
#define PTRDIFF_MIN INT32_MIN
#define PTRDIFF_MAX INT32_MAX
// #define SIG_ATOMIC_MIN
// #define SIG_ATOMIC_MAX
#define SIZE_MAX UINT64_MAX
// #define WCHAR_MIN
// #define WCHAR_MAX
// #define WINT_MIN
// #define WINT_MAX

// constants
#define INT8_C(value)    (value)
#define UINT8_C(value)   (value)
#define INT16_C(value)   (value)
#define UINT16_C(value)  (value##u)
#define INT32_C(value)   (value##l)
#define UINT32_C(value)  (value##lu)
#define INT64_C(value)   (value##ll)
#define UINT64_C(value)  (value##llu)
#define INTMAX_C(value)  (value##ll)
#define UINTMAX_C(value) (value##llu)
#else
#	error "Unknown architecture is set"
#endif

#endif
