#ifndef __DEFS_H__
#define __DEFS_H__
#include <stddef.h>
#include <mio.h>

struct section 
{
	char *name;
	
	struct MiO_SymList *symbol;
	size_t              symbols;
	size_t              symbolcp;

	struct MiO_Gap *gap;
	size_t          gaps;
	size_t          gapcp;

	int flags;

	char  *data;
	size_t datasz;
	size_t datacp;

	struct MiO_Map map;
};

struct file
{
	struct section *section;
	size_t          sections;
	size_t          sectioncp;
};

// ld.c
extern const char *self;

// error.c
extern size_t errors;
extern void error (int, const char *, ...);

// free.c
extern void freeAll     (void);
extern void freeSection (struct section *);

// ld_func/input.c
extern void ld_input (const char *);

#endif
