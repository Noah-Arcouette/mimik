#ifndef __LIBC_STRING_H__
#define __LIBC_STRING_H__
#include <stddef.h>
#include <locale.h>

// string/strcmp.c
int 
strcmp (const char *s1, const char *s2);

// string/strncmp.c
int
strncmp (const char *s1, const char *s2, size_t n);

// string/strcpy.c
char *
strcpy (char *restrict dst, const char *restrict src);

char *
stpcpy (char *restrict dst, const char *restrict src);

// string/strncpy.c
char *
strncpy (char *restrict dst, const char *restrict src, size_t n);

char *
stpncpy (char *restrict dst, const char *restrict src, size_t n);

// string/strlen.c
size_t
strlen (const char *s);

size_t
strnlen (const char *s, size_t n);

// string/strcat.c
char *
strcat (char *restrict s1, const char *restrict s2);

char *
strncat (char *restrict s1, const char *restrict s2, size_t n);

// string/strchr.c
char *
strchr (const char *s, int c);

char *
strrchr (const char *s, int c);

// string/strpbrk.c
char *
strpbrk (const char *s1, const char *s2);

// string/memcmp.c
int 
memcmp (const void *s1, const void *s2, size_t n);

// string/memset.c
void *
memset (void *s, int c, size_t n);

// string/memcpy.c
void *
memcpy (void *restrict dst, const void *restrict src, size_t n);

// string/memchr.c
void *
memchr (const void *s, int c, size_t n);

// string/memccpy.c
void *
memccpy (void *restrict dst, const void *restrict src, int c, size_t n);

#endif
