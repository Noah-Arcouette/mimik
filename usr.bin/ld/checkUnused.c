#include "main.h"
#include <libintl.h>
#include <endian.h>
#include <stdio.h>

void
checkUnused (void)
{
	for (long i = 0; i<inputs; i++)
	{
		// check for unused symbols
		struct MiO_Symbol *symbol = input[i].symbol;
		for (long j = 0; j<input[i].symbols; j++)
		{
			if (symbol[j].name[0])
			{
				fprintf(stderr,
					gettext("%s: Symbol `%s:%.*s' never linked\n"),
					self, input[i].path, 256, symbol[j].name);
				errors++;
			}
		}

		// check for unused gaps
		struct MiO_Gap *gap = input[i].gap;
		for (long j = 0; j<input[i].gaps; j++)
		{
			if (gap[j].symbol[0])
			{
				fprintf(stderr,
					gettext("%s: Gap `%s:%.*s' never linked\n"),
					self, input[i].path, 256, gap[j].symbol);
				errors++;
			}
		}

		// check for unused sections
		long offset = 0;
		while (offset < input[i].size)
		{
			struct MiO *section = input[i].data+offset;

			// user defined sections
			if (section->name[0] == '.')
			{
				fprintf(stderr,
					gettext("%s: Section `%s:%.*s' never linked\n"),
					self, input[i].path, 256, section->name);
				errors++;
			}

			if (section->flags & MIO_FLAG_VIRTUAL)
			{
				offset += sizeof(struct MiO);
			}
			else
			{
				offset += sizeof(struct MiO)+le64toh(section->size);
			}
		}
	}
}
