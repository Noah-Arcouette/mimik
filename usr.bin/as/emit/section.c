#include "../main.h"
#include "../emit.h"
#include <libintl.h>
#include <endian.h>
#include <string.h>
#include <stdlib.h>

long currentSection = -1;

void
emitSection (const wchar_t *name)
{
	struct MiO newSection;

	currentSection = -1; // clear current section
	currentSymbol  = -1;
	symbolFlags    = 0;

	// check if the name can fix
	if ((wcstombs(NULL, name, 0)-1) > sizeof(newSection.name))
	{
		prettyprint(gettext(
			"The section name `%S` does not fit into a MiO section name\n"),
			name);
		errors++;
		return;
	}

	// create empty section
	memset(&newSection, 0, sizeof(newSection));
	newSection.magic = htole32(MIO_MAGIC);

	// add the name
	wcstombs((void *)newSection.name, name, sizeof(newSection.name));

	// emit it
	currentSection = emitRaw(&newSection, sizeof(newSection));
}
