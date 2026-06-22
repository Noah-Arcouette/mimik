#include <libintl.h>
#include <endian.h>
#include <stdio.h>
#include "main.h"

struct MiO_Arch outputArch = {
	.arch      = 0,
	.uarch     = 0,
	.archflags = 0,
	.sys       = 0,
	.usys      = 0,
	.sysflags  = 0
};

void
mergeArchitecture (const char *path, const struct MiO_Arch *arch)
{
	// architecture
	if (le16toh(outputArch.arch) == MIO_ARCH_ARCH_UNDEFINED) // not set yet
	{
		// everything should be in little endian already
		outputArch.arch      = arch->arch;
		outputArch.uarch     = arch->uarch;
		outputArch.archflags = arch->archflags;
	}
	else if (le16toh(arch->arch) == MIO_ARCH_ARCH_UNDEFINED) // no architecture
	{
		// leave as is
	}
	else if (outputArch.arch == arch->arch) // little endian already, same major
	{
		// set minor to the max of the two
		if (le16toh(arch->uarch) > le16toh(outputArch.uarch))
		{
			outputArch.uarch = arch->uarch;
		}

		// no flags are defined
		// just double check
		if (outputArch.archflags)
		{
			fprintf(stderr,
				gettext("%s: `%s' contains unknown architecture flags\n"),
				self, path);
			errors++;
		}
	}
	else // incompatible
	{
		fprintf(stderr,
			gettext("%s: `%s' is incompatible with prior files' architecture\n"),
			self, path);
		errors++;
	}

	// system
	if (le16toh(outputArch.sys) == MIO_ARCH_SYS_UNDEFINED) // not set yet
	{
		// everything should be in little endian already
		outputArch.sys      = arch->sys;
		outputArch.usys     = arch->usys;
		outputArch.sysflags = arch->sysflags;
	}
	else if (le16toh(arch->sys) == MIO_ARCH_SYS_UNDEFINED) // no system
	{
		// leave as is
	}
	else if (outputArch.sys == arch->sys) // little endian already, same major
	{
		// set minor to the max of the two
		if (le16toh(arch->usys) > le16toh(outputArch.usys))
		{
			outputArch.usys = arch->usys;
		}

		// no flags are defined
		// just double check
		if (outputArch.sysflags)
		{
			fprintf(stderr, gettext("%s: `%s' contains unknown system flags\n"),
				self, path);
			errors++;
		}
	}
	else // incompatible
	{
		fprintf(stderr,
			gettext("%s: `%s' is incompatible with prior files' system\n"),
			self, path);
		errors++;
	}
}
