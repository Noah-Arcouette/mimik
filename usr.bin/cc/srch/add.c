#include "../srch.h"
#include "../main.h"
#include "../lex.h"
#include <libintl.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <errno.h>

static struct srch_elem *
_grow (struct srch *s)
{
	s->sz++;
	if (s->sz > s->cp)
	{
		s->cp = 3*s->sz/2;
		void *buf = realloc(s->elems, sizeof(struct srch_elem)*s->cp);
		if (!buf)
		{
			s->sz--;
			s->cp = s->sz;
			fprintf(stderr, gettext("%s: %s\n"), self, strerror(errno));
			errors++;
			return NULL;
		}
		s->elems = buf;
	}
	return &s->elems[s->sz-1];
}

static void
_add (struct srch *s, struct srch_elem *e, const char *name, void *dat)
{
	int namesz = strlen(name)+1;

	// check for prefix match
	int matches = 0;
	for (int i = 0; ; i++)
	{
		// out of bounds
		if (i >= e->prefixsz) break;
		if (i >= namesz) break;

		// check for compare
		if (name[i] != e->prefix[i]) break;

		matches++;
	}

	// no match
	if (!matches)
	{
		// has a sibling
		if (e->sibling >= 0)
		{
			// try it
			_add(s, &s->elems[e->sibling], name, dat);
		}
		else
		{
			// insert to the sibling slot
			ptrdiff_t reloc = (void *)e-(void *)s->elems;

			char *prefix = strdup(name);
			if (!prefix)
			{
				fprintf(stderr, gettext("%s: %s\n"), self, strerror(errno));
				free(dat);
				errors++;
				return;
			}

			// grow the buffer
			struct srch_elem *e = _grow(s);
			if (!e)
			{
				free(dat);
				free(prefix);
				return;
			}

			e->child    = -1;
			e->sibling  = -1;
			e->dat      = dat;
			e->prefix   = prefix;
			e->prefixsz = namesz;

			e = reloc+(void *)s->elems;
			e->sibling = s->sz-1;
		}
	}
	// complete match
	else if (matches == namesz)
	{
		lex_prettyprint(gettext("Redefinition of symbol\n"));
		free(e->dat);
		e->dat = dat;
	}
	// partial match
	else
	{
		// if there another depth
		if (e->child >= 0 && matches == e->prefixsz)
		{
			// try it
			_add(s, &s->elems[e->child], name+matches, dat);
		}
		else
		{
			// allocate data
			char *common_prefix = malloc(matches);
			if (!common_prefix)
			{
				fprintf(stderr, gettext("%s: %s\n"), self, strerror(errno));
				errors++;
				free(dat);
				return;
			}
			memcpy(common_prefix, e->prefix, matches);

			char *left_over_prefix = malloc(e->prefixsz-matches);
			if (!left_over_prefix)
			{
				fprintf(stderr, gettext("%s: %s\n"), self, strerror(errno));
				errors++;
				free(common_prefix);
				free(dat);
				return;
			}
			memcpy(left_over_prefix, e->prefix+matches, e->prefixsz-matches);

			char *left_over_name = strdup(name+matches);
			if (!left_over_name)
			{
				fprintf(stderr, gettext("%s: %s\n"), self, strerror(errno));
				errors++;
				free(left_over_prefix);
				free(common_prefix);
				free(dat);
				return;
			}

			// before we f-up the elements
			void *e_prefix_dat   = e->dat;
			int   e_prefix_size  = e->prefixsz;
			int   e_prefix_child = e->child;

			ptrdiff_t old_reloc = (void *)e-(void *)s->elems;

			// create the nodes
			struct srch_elem *e_prefix = _grow(s);
			if (!e_prefix)
			{
				free(left_over_name);
				free(left_over_prefix);
				free(common_prefix);
				free(dat);
				return;
			}

			// set up the child prefix
			e_prefix->sibling  = s->sz;
			e_prefix->dat      = e_prefix_dat;
			e_prefix->prefix   = left_over_prefix;
			e_prefix->prefixsz = e_prefix_size-matches;
			e_prefix->child    = e_prefix_child;

			struct srch_elem *e_name = _grow(s);
			if (!e_name)
			{
				s->sz--;
				free(left_over_name);
				free(left_over_prefix);
				free(common_prefix);
				free(dat);
				return;
			}

			// set up the child name
			e_name->sibling  = -1;
			e_name->dat      = dat;
			e_name->prefix   = left_over_name;
			e_name->prefixsz = namesz-matches;
			e_name->child    = -1;

			// setup the split node
			e = (void *)s->elems+old_reloc;

			free(e->prefix);
			e->child    = s->sz-2; // the e_prefix
			e->dat      = NULL;
			e->prefix   = common_prefix;
			e->prefixsz = matches;
			// e->sibling // keep the same, no need to change it
		}
	}
}

void
srch_add (struct srch *srch, const char *name, void *dat)
{
	// root
	if (!srch->sz)
	{
		char *prefix = strdup(name);
		if (!prefix)
		{
			fprintf(stderr, gettext("%s: %s\n"), self, strerror(errno));
			free(dat);
			errors++;
			return;
		}

		struct srch_elem *e = _grow(srch);
		if (!e)
		{
			free(dat);
			free(prefix);
			return;
		}
		// else

		e->child    = -1;
		e->sibling  = -1;
		e->dat      = dat;
		e->prefixsz = strlen(name)+1;
		e->prefix   = prefix;
	}
	else
	{
		_add(srch, srch->elems, name, dat);
	}
}
