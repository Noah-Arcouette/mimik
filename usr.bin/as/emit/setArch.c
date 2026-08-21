#include "../emit.h"
#include "../main.h"
#include <libintl.h>
#include <endian.h>
#include <wchar.h>
#include <mio.h>

void
setArch (const wchar_t *arch)
{
	if (!wcscmp(arch, L"undefined"))
	{
		currentArchitecture.arch      = 0;
		currentArchitecture.uarch     = 0;
		currentArchitecture.archflags = 0;
	}
	else if (!wcscmp(arch, L"x86_16"))
	{
		currentArchitecture.arch      = htole16(MIO_ARCH_ARCH_X86_16);
		currentArchitecture.uarch     = 0;
		currentArchitecture.archflags = 0;

	#ifndef X86_16
		prettyprint(gettext("Architecture `%S' not supported in this build\n"),
			arch);
		errors++;
	#endif
	}
	else
	{
		prettyprint(gettext(
			"Unknown architecture `%S', \
expected either: undefined, or x86_16\n"),
			arch);
		errors++;
	}
}
