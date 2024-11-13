#include "defs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

struct prototype *
definePrototype (struct type t, char *name)
{
	// check for the symbol
	struct symbol sym;
	if (!getSymbol(name, &sym))
	{
		fprintf(stderr, "%s:%zu: Failed symbol `%s' already exists\n", filename, lineno, name);
		fprintf(stderr, " -> First seen on line %zu in file `%s'\n", sym.lineno, sym.filename);
		return (struct prototype *)NULL;
	}

	// allocate for the prototype
	ctx->prototypes++;
	if (ctx->prototypes >= ctx->prototypecp)
	{
		ctx->prototypecp = (3*ctx->prototypes)/2; // grow by 3/2

		// reallocate
		struct prototype *old = ctx->prototype; // save
		ctx->prototype = (struct prototype *)realloc(ctx->prototype, ctx->prototypecp*sizeof(struct prototype));
		if (!ctx->prototype) // failed to allocate
		{
			int errnum = errno;
			fprintf(stderr, "%s:%zu: Failed to allocate memory.\n", filename, lineno);
			fprintf(stderr, " -> Error %d: %s.\n", errnum, strerror(errnum));

			ctx->prototypes--;
			ctx->prototypecp = ctx->prototypes;
			ctx->prototype   = old; // restore
			return (struct prototype *)NULL; // soft fail
		}
	}

	// fill out information
	struct prototype *p = &ctx->prototype[ctx->prototypes-1];

	memset(p, 0, sizeof(struct prototype)); // fill out with null
	p->name = name;
	memcpy(&p->returnType, &t, sizeof(struct type));

	p->filename = filename;
	p->lineno   = lineno;

	return p;
}

int
defineParameter (struct prototype *p, struct parameter param)
{
	// check if parameter already exists
	// only if the parameter has a name
	if (!param.name)
	{
		goto skip_check;
	}

	// for each parameter
	for (size_t i = 0; i<p->parameters; i++)
	{
		// skip un-name parameters
		if (!p->parameter[i].name)
		{
			continue; // skip
		}

		// check name
		if (!strcmp(p->parameter[i].name, param.name))
		{
			// found
			fprintf(stderr, "%s:%zu: Parameter `%s' already exists.\n", filename, lineno, param.name);
			fprintf(stderr, " -> Function prototype seen on line %zu in file `%s'.\n", p->lineno, p->filename);
			return 1;
		}
	}
skip_check:

	// grow parameters
	p->parameters++;
	if (p->parameters >= p->parametercp) // if the capacity need to be grown
	{
		p->parametercp = (3*p->parameters)/2; // grow by 3/2

		struct parameter *old = p->parameter; // save old
		p->parameter = (struct parameter *)realloc(p->parameter, p->parametercp*sizeof(struct parameter)); // reallocate
		if (!p->parameter) // if failed
		{
			// restore
			p->parameters--;
			p->parametercp = p->parameters;
			p->parameter   = old;

			int errnum = errno;
			fprintf(stderr, "%s:%zu: Failed to allocate memory.\n", filename, lineno);
			fprintf(stderr, " -> Error %d: %s.\n", errnum, strerror(errnum));
			return 1;
		}
	}

	// fill out information
	struct parameter *new = &p->parameter[p->parameters-1];
	memcpy(new, &param, sizeof(struct parameter));
	return 0;
}

void
freeParameter (struct parameter *p)
{
	free(p->name);
	freeType(p->type);
	memset(p, 0, sizeof(struct parameter));
}

void
freePrototype (struct prototype *p)
{
	free(p->name);
	freeType(p->returnType);
	while (p->parameters--)
	{
		freeParameter(&p->parameter[p->parameters]);
	}
	free(p->parameter);

	// nullify
	memset(p, 0, sizeof(struct prototype));
}
