#ifndef __LIB_C_STDLIB_H__
#define __LIB_C_STDLIB_H__
#include <stddef.h>
#include <sys/wait.h>
#include <math.h>
#include <limits.h>

// stdlib/atexit.c
int atexit (void (*func)(void));

extern void (*__at_exit_funcs[ATEXIT_MAX])(void);
extern size_t __at_exit_amount;

// null
void *malloc (size_t);
void  free   (void *);
void  exit   (int);
void  abort  (void);

#endif
