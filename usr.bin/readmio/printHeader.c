#include <mio-x86.h>
#include <string.h>
#include <mio.h>
#include "defs.h"

void
printHeader (struct MiO_Header h)
{
	printf("Magic:  `%.*s'\n", (int)sizeof(h.magic), h.magic);
	printf("Version: %d\n",                          h.version);
	printf("Flags:   ");
	if (h.flags & MIO_HEADER_FLAG_LAST)
	{
		printf("Last");
	}

	printf("\nArch:    ");
	switch (h.arch)
	{
	case MIO_ARCH_UNKNOWN:
		printf("Unknown\n"); // no uarch or features if unknown
		break;
	case MIO_ARCH_X86:
		printf("Intel x86\n");
		printf("UArch:   ");
		switch (h.uarch) // no features for now
		{
		case MIO_UARCH_I8086:
			printf("i8086\n");
			break;
		case MIO_UARCH_I386:
			printf("i386\n");
			break;
		default:
			printf("(unrecognized)\n");
			break;
		}
		break;
	default:
		printf("(unrecognized)\n");
		break;
	}

	printf("System:  Unknown\n"); // no systems for now

	// entry symbol
	printf("Entry:   `%.*s'\n", (int)sizeof(h.entry), h.entry);
}
