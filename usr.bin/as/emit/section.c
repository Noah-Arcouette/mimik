#include "../main.h"
#include "../emit.h"
#include <libintl.h>
#include <string.h>

long currentSection = -1;

void
emitSection (const char *name)
{
	struct MiO newSection;

	currentSection = -1; // clear current section
	currentSymbol  = -1;

	// check if the name can fix
	if (strlen(name) > sizeof(newSection.name))
	{
		prettyprint(gettext(
			"The section name `%s` does not fit into a MiO section name\n"),
			name);
		errors++;
		return;
	}

	// create empty section
	memset(&newSection, 0, sizeof(newSection));
	memcpy(newSection.magic, MIO_MAGIC, sizeof(newSection.magic));

	// add the name
	strncpy((void *)newSection.name, name, sizeof(newSection.name));

	// emit it
	currentSection = emitRaw(&newSection, sizeof(newSection));
}
