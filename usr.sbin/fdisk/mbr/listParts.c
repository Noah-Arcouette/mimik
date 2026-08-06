#include "../main.h"
#include <libintl.h>
#include <endian.h>
#include <stdio.h>

void
mbr_listParts (void)
{
	if (!writeMBR)
	{
		fprintf(stderr, gettext("%s: No MBR\n\n"), self);
		return;
	}
	// else

	fprintf(stderr, gettext("%s: MBR:\n"), self);
	for (int i = 0; i<4; i++)
	{
		struct mbr_part *p = &mbr.part[i];

		// empty
		if (!p->type) continue;

		// print the partition
		fprintf(stderr, gettext("%s: Part #%d : Start "), self, i);
		printSize(le32toh(p->firstLBA)*bytesPerSector);
		fprintf(stderr, gettext(" (%d/%d/%d) : End "),
			p->firstCHS[2]|((p->firstCHS[1]&0xc0)<<2),
			p->firstCHS[0],
			p->firstCHS[1]&0x3f);
		printSize((le32toh(p->firstLBA)+le32toh(p->sectors))*bytesPerSector);
		fprintf(stderr, gettext(" (%d/%d/%d) : Size "),
			p->lastCHS[2]|((p->lastCHS[1]&0xc0)<<2),
			p->lastCHS[0],
			p->lastCHS[1]&0x3f);
		printSize(le32toh(p->sectors)*bytesPerSector);
		fprintf(stderr, gettext(" : Type %02x ("), p->type);
		switch (p->type)
		{
		case MBR_PART_TYPE_VBR:
			fprintf(stderr, gettext("VBR)\n"));
			break;
		case MBR_PART_TYPE_ROOT:
			fprintf(stderr, gettext("Root FS)\n"));
			break;
		case MBR_PART_TYPE_FS:
			fprintf(stderr, gettext("FS)\n"));
			break;
		case MBR_PART_TYPE_GPT_PROT:
			fprintf(stderr, gettext("GPT Protected)\n"));
			break;
		case MBR_PART_TYPE_ESP:
			fprintf(stderr, gettext("uEFI Boot)\n"));
			break;
		default:
			fprintf(stderr, gettext("Unknown)\n"));
			break;
		}
	}
	fprintf(stderr, "\n");
}
