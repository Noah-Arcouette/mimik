#include "defs.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

size_t labelTemp = 0;

static struct label *
getLabel (char *name) // get or define a label
{
	// attempt to find the label
	// through all contexts
	struct context *c = ctx;
	while (c)
	{
		// for all labels
		size_t labels = c->labels;
		while (labels--)
		{
			// check for label
			if (!strcmp(name, c->label[labels].name))
			{
				return &c->label[labels]; // just leave with that variable
			}
		}

		// next context
		c = c->parent;
	}

	// else
	// add new labels to this context
	ctx->labels++; // add label
	if (ctx->labels >= ctx->labelcp) // larger than capacity
	{
		ctx->labelcp = (3*ctx->labels)/2; // grow by 3/2
		ctx->label   = (struct label *)realloc(ctx->label, ctx->labelcp*sizeof(struct label)); // reallocate
		if (!ctx->label) // failed
		{
			int errnum = errno;
			fprintf(stderr, "%s: Failed to allocate memory.\n", self);
			fprintf(stderr, "Error %d: %s.\n", errnum, strerror(errnum));

			// clean up
			ctx->labelcp = 0;
			ctx->labels  = 0;
			exit(1);
		}
	}
	// setup base for label
	struct label *l = &ctx->label[ctx->labels-1];

	l->name     = name;
	l->filename = (char *)NULL; // may be soft defined so don't set position
	l->lineno   = 0;
	l->label    = labelTemp++;
	return l;

	// also no printing anything, because we don't know what the label actually means to the program
}

int
defineLabel (char *name)
{
	struct label *l = getLabel(name);

	if (l->filename) // already defined
	{
		fprintf(stderr, "%s:%zu: Label, `%s',  already defined.\n", filename, lineno, name);
		fprintf(stderr, " -> First seen on line %zu in file `%s'.\n", l->lineno, l->filename);
		return 1;
	}

	// add line information
	l->lineno   = lineno;
	l->filename = filename;

	// print IR for it
	fprintf(fout, "\tgoto @%zu\n", l->label); // block follow through
	fprintf(fout, "%zu:\n", l->label);
	return 0;
}

// struct context
// {
// 	struct variable *var;
// 	size_t           vars;
// 	size_t           varcp;

// 	struct label *label;
// 	size_t        labels;
// 	size_t        labelcp;

// 	struct context *parent;
// };

// // free.c
// extern void freeCtx         (struct context *);
// extern void freeAllContexts (void);

// // labels.c
// struct label
// {
// 	char  *name;
// 	size_t label;

// 	size_t      lineno;
// 	const char *filename;
// };
