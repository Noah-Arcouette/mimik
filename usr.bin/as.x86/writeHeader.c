#include "defs.h"
#include <endian.h>
#include <mio.h>
#include <mio-x86.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

void
writeHeader (void)
{
	struct MiO_Header out;

	// magic, version, and flags
	memcpy(out.magic, MIO_MAGIC, sizeof(out.magic));
	out.version = MIO_CURRENT_VERSION;
	out.flags   = MIO_HEADER_FLAG_LAST; // last, and only, header

	// architecture information
	out.arch  = MIO_ARCH_X86; // intel x86 assembler
	out.uarch = header.uarch;

	// format and write architecture features
	size_t x = htole64(header.archFeatures);
	memcpy(out.archFeatures, &x, sizeof(out.archFeatures));

	// system information
	out.system = header.system;
	out.abi    = header.abi;

	// format and write the system features
	x = htole64(header.sysFeatures);
	memcpy(out.sysFeatures, &x, sizeof(out.sysFeatures));

	// no entry point
	memset(out.entry, 0, sizeof(out.entry));

	// write to output file
	if (fwrite(&out, sizeof(out), 1, fout) != 1)
	{
		int errnum = errno;
		fprintf(stderr, "%s: Failed to write to output file `%s'.\n", self, fileout);
		fprintf(stderr, "Error %d: %s.\n", errnum, strerror(errnum));
		exit(1);
	}
}
