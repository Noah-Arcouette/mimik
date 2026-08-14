#include "../args.h"
#include "../main.h"
#include "../pre.h"
#include <libintl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

char *
pre_findInclude (const char *path, int searchLocal)
{
	char *searchPath   = NULL;
	int   searchPathsz = 0;

	const int pathsz = strlen(path)+2;

	// local search
	if (searchLocal)
	{
		const char *_dirname = NULL;

		// find the last dirname
		int i = lex_contexts;
		while (i)
		{
			i--;
			struct lex_context *lc = &lex_context[i];

			switch (lc->type)
			{
			case LEX_CONTEXT_TYPE_NORMAL_FILE:
			case LEX_CONTEXT_TYPE_INCLUDED_FILE:
				i = 0;
				_dirname = lc->name;
				break;
			case LEX_CONTEXT_TYPE_MACRO_EXPAND: // not a path name
				break;
			}
		}

		if (_dirname)
		{
			searchPathsz = strlen(_dirname)+pathsz;
			searchPath   = malloc(searchPathsz);
			if (!searchPath)
			{
				fprintf(stderr, gettext("%s: %s\n"), self, strerror(errno));
				errors++;
			}
			else
			{
				strcpy(searchPath, _dirname);
				// use my own dirname, because we cant have memory regions
				// overlap
				char *slash = strrchr(searchPath, '/');
				if (!slash)
				{
					*searchPath = '\0';
				}
				else
				{
					*(slash+1) = '\0';
				}

				strcat(searchPath, path);

				if (!access(searchPath, R_OK))
				{
					return searchPath;
				}
			}
		}
	}

	// include path search
	for (int i = 0; i<args_includes; i++)
	{
		struct args_include *inc = &args_include[i];

		int size = strlen(inc->path)+pathsz;
		if (size > pathsz)
		{
			searchPathsz = size;
			void *buf = realloc(searchPath, searchPathsz);
			if (!buf)
			{
				fprintf(stderr, gettext("%s: %s\n"), self, strerror(errno));
				errors++;
				free(searchPath);
				return NULL;
			}
			searchPath = buf;
		}
		strcpy(searchPath, inc->path);
		strcat(searchPath, "/");
		strcat(searchPath, path);

		if (!access(searchPath, R_OK))
		{
			return searchPath;
		}
	}

	free(searchPath);
	return NULL;
}
