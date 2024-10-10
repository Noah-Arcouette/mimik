#ifndef __DEFS_H__
#define __DEFS_H__
#include <stdio.h>
#include <stddef.h>

// cpp.c
extern const char *self;

extern const char *filename;
extern FILE *fout;

extern char *expand_buf;
extern char *directive_buf;

extern size_t lineno;

// options.c
void options (int, char *const *);

// lineSplicing.c
extern void lineSplicing (int);

// comments.c
extern void comments (int);

// directives.h
extern void directives (int);

// expand.c
extern void expand (int);

#endif
