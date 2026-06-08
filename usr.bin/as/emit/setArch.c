#include "../emit.h"
#include "../main.h"
#include <libintl.h>
#include <string.h>
#include <endian.h>
#include <mio.h>

void
setArch (const char *arch)
{
	if (!strcmp(arch, "undefined"))
	{
		currentArchitecture.arch      = 0;
		currentArchitecture.uarch     = 0;
		currentArchitecture.archflags = 0;
	}
	else if (!strcmp(arch, "x86_16"))
	{
		currentArchitecture.arch      = htole16(MIO_ARCH_ARCH_X86_16);
		currentArchitecture.uarch     = 0;
		currentArchitecture.archflags = 0;

	#ifndef X86_16
		prettyprint(gettext("Architecture `%s' not supported in this build\n"),
			arch);
		errors++;
	#endif
	}
	else
	{
		prettyprint(gettext(
			"Unknown architecture `%s', \
expected either: undefined, or x86_16\n"),
			arch);
		errors++;
	}
}
