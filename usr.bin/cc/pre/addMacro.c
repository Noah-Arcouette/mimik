#include "../main.h"
#include "../pre.h"
#include <libintl.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

struct pre_macro *pre_macro     = NULL;
int               pre_macros    = 0;
int               pre_macroRoot = -1;

void
pre_addMacro (const char *name, const char *value)
{
	int *macroIndex = &pre_macroRoot;

	struct pre_macro *m;
	while ((*macroIndex) >= 0)
	{
		// find a leaf
		m = &pre_macro[*macroIndex];

		int cmp = strcmp(name, m->name);

		if (cmp > 0)
		{
			macroIndex = &m->right;
		}
		else if (cmp < 0)
		{
			macroIndex = &m->left;
		}
		else // cmp == 0
		{
			lex_prettyprint(gettext("Redefinition of macro `%s'\n"), name);

			void *buf = realloc(m->value, strlen(value)+1);
			if (!buf)
			{
				fprintf(stderr, gettext("%s: %s\n"), self, strerror(errno));
				errors++;
				return;
			}
			m->value = buf;
			strcpy(m->value, value);
			return;
		}
	}
	// insert

	// we can't remove the node after reloc
	// because the macroIndex may become invalid
	void *namedup = strdup(name);
	if (!namedup)
	{
	_strdup_err:
		fprintf(stderr, gettext("%s: %s\n"), self, strerror(errno));
		errors++;
		return;
	}
	void *valuedup = strdup(value);
	if (!valuedup)
	{
		free(namedup);
		goto _strdup_err;
	}

	*macroIndex = pre_macros; // add the macro, before to realloc

	void *buf = realloc(pre_macro, sizeof(struct pre_macro)*(pre_macros+1));
	if (!buf)
	{
		*macroIndex = -1; // remove the node
		free(namedup);
		free(valuedup);
		fprintf(stderr, gettext("%s: %s\n"), self, strerror(errno));
		errors++;
		return;
	}
	pre_macro = buf;
	m = &pre_macro[pre_macros];
	pre_macros++;

	m->left  = -1;
	m->right = -1;
	m->name  = namedup;
	m->value = valuedup;
}
