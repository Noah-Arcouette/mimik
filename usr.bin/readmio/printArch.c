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
	int archMinor = le16toh(arch.uarch);
	int archFlags = le64toh(arch.archflags);

	switch (archMajor)
	{
	case MIO_ARCH_ARCH_UNDEFINED:
		printf(gettext("\n\tArch: %04x(undefined) %04x(unknown) %016x( )\n"),
			archMajor,
			archMinor,
			archFlags);
		break;
	case MIO_ARCH_ARCH_X86_16:
		switch (archMinor)
		{
		case MIO_ARCH_ARCH_X86_UARCH_I8086:
			printf(
				gettext("\n\tArch: %04x(x86-16) %04x(i8086) %016x( )\n"),
				archMajor,
				archMinor,
				archFlags);
			break;
		default:
			printf(
				gettext("\n\tArch: %04x(x86-16) %04x(unknown) %016x( )\n"),
				archMajor,
				archMinor,
				archFlags);
			break;
		}
		break;
	default:
		printf(
			gettext("\n\tArch: %04x(unknown) %04x(unknown) %016x( )\n"),
			archMajor,
			archMinor,
			archFlags);
		break;
	}

	// print system information
	int sysMajor = le16toh(arch.sys);
	int sysMinor = le16toh(arch.usys);
	int sysFlags = le64toh(arch.sysflags);

	switch (sysMajor)
	{
	case MIO_ARCH_SYS_UNDEFINED:
		printf(gettext("\tSys : %04x(undefined) %04x(unknown) %016x( )\n"),
			sysMajor,
			sysMinor,
			sysFlags);
		break;
	default:
		printf(
			gettext("\tArch: %04x(unknown) %04x(unknown) %016x( )\n"),
			sysMajor,
			sysMinor,
			sysFlags);
		break;
	}

	// check if the size is different than sizeof(arch)
	if (sizeof(arch) != size)
	{
		printf(gettext(
			"\tError, architecture data size mismatched with section size\n"));
		errors++;
		fseek(fp, off+size, SEEK_SET);
	}
}
