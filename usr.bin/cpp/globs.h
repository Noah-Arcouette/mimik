#ifndef __GLOBS_H__
#define __GLOBS_H__
#include <stdio.h>
#include <stddef.h>

// cpp.c
extern const char *self;

extern const char *filename;
extern FILE *fout;

extern char *expand_buf;
extern char *directive_buf;

extern size_t lineno;

#endif
