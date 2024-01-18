#ifndef __LIB_C_STDLIB_H__
#define __LIB_C_STDLIB_H__
#include <stddef.h>
#include <sys/wait.h>
#include <math.h>
#include <limits.h>

// null
void *malloc (size_t);
void  free   (void *);
void  exit   (int);
void  abort  (void);

#endif
