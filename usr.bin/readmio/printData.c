#include <endian.h>
#include <stdint.h>
#include <stdio.h>
#include <mio.h>
#include "defs.h"

void
printData (struct MiO_Data d)
{
	printf("\nData Header:\n");
	printf("Format: ");
	switch (d.format)
	{
	case MIO_DATA_FORMAT_RAW:
		printf("Raw\n");
		break;
	default:
		printf("(unrecognized)\n");
		break;
	}
	printf("Size:   %lu\n", le64toh(*(uint64_t *)d.size));
}
