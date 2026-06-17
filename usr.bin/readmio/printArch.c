#include "main.h"
#include <libintl.h>
#include <endian.h>
#include <stdio.h>
#include <mio.h>

void
printArch (FILE *fp, unsigned long long size)
{
	long off = ftell(fp);

	// read the architecture information
	struct MiO_Arch arch;
	if (fread(&arch, sizeof(arch), 1, fp) != 1)
	{
		printf(gettext("\n\tFailed to read architecture\n"));
		errors++;
		fseek(fp, off+size, SEEK_SET);
		return;
	}

	// print architecture information
	int archMajor = le16toh(arch.arch);
	const char *archMajorName = "unknown";

	int archMinor = le16toh(arch.uarch);
	const char *archMinorName = "unknown";

	int archFlags = le64toh(arch.archflags);

	switch (archMajor)
	{
	case MIO_ARCH_ARCH_UNDEFINED:
		archMajorName = "undefined";
		break;
	case MIO_ARCH_ARCH_X86_16:
		archMajorName = "x86-16";

		switch (archMinor)
		{
		case MIO_ARCH_ARCH_X86_UARCH_I8086:
			archMinorName = "i8086";
			break;
		}
		break;
	}
	printf(gettext("\n\tArch: %04x(%s) %04x(%s) %016x( )\n"),
		archMajor,
		archMajorName,
		archMinor,
		archMinorName,
		archFlags);

	// print system information
	int sysMajor = le16toh(arch.sys);
	const char *sysMajorName = "unknown";

	int sysMinor = le16toh(arch.usys);
	const char *sysMinorName = "unknown";

	int sysFlags = le64toh(arch.sysflags);

	switch (sysMajor)
	{
	case MIO_ARCH_SYS_UNDEFINED:
		sysMajorName = "undefined";
		break;
	}
	printf(gettext("\tSys : %04x(%s) %04x(%s) %016x( )\n"),
		sysMajor,
		sysMajorName,
		sysMinor,
		sysMinorName,
		sysFlags);

	// check if the size is different than sizeof(arch)
	if (sizeof(arch) != size)
	{
		printf(gettext(
			"Error, architecture data size mismatched with section size\n"));
		errors++;
		fseek(fp, off+size, SEEK_SET);
	}
}
