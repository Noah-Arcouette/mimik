#ifndef __LIB_C_STD_ARG_H__
#define __LIB_C_STD_ARG_H__

// get the compiler to do the, very hard and weird, work
#define va_start(l,a) __builtin_va_start(l,a)
#define va_end(l)     __builtin_va_end(l)
#define va_arg(l,t)   __builtin_va_arg(l,t)
#define va_copy(d,s)  __builtin_va_copy(d,s)
typedef __builtin_va_list va_list;

#endif
