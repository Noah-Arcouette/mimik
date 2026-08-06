#include "../main.h"
#include <libintl.h>
#include <endian.h>
#include <stdio.h>

void
mbr_listParts (void)
{
	if (!writeMBR)
	{
		fprintf(stderr, gettext("%s: No MBR\n"), self);
		return;
	}
	fprintf(stderr, gettext("%s:\tMBR\tID %08x\n"), self, le32toh(mbr.id));
	// else

	for (int i = 0; i<4; i++)
	{
		struct mbr_part *p = &mbr.part[i];

		// empty
		if (!p->type) continue;

		// print the partition
		fprintf(stderr, gettext("%s:\tMBR\tPart #%d\tStart "), self, i);
		printSize(le32toh(p->firstLBA)*bytesPerSector);
		fprintf(stderr, gettext(" (%d/%d/%d)\tEnd "),
			p->firstCHS[2]|((p->firstCHS[1]&0xc0)<<2),
			p->firstCHS[0],
			p->firstCHS[1]&0x3f);
		printSize((le32toh(p->firstLBA)+le32toh(p->sectors))*bytesPerSector);
		fprintf(stderr, gettext(" (%d/%d/%d)\tSize "),
			p->lastCHS[2]|((p->lastCHS[1]&0xc0)<<2),
			p->lastCHS[0],
			p->lastCHS[1]&0x3f);
		printSize(le32toh(p->sectors)*bytesPerSector);
		fprintf(stderr, gettext("\tType %02x ("), p->type);
		switch (p->type)
		{
		case MBR_PART_TYPE_VBR:
			fprintf(stderr, gettext("VBR"));
			break;
		case MBR_PART_TYPE_ROOT:
			fprintf(stderr, gettext("Root FS"));
			break;
		case MBR_PART_TYPE_FS:
			fprintf(stderr, gettext("FS"));
			break;
		case MBR_PART_TYPE_GPT_PROT:
			fprintf(stderr, gettext("GPT Protected"));
			break;
		case MBR_PART_TYPE_ESP:
			fprintf(stderr, gettext("uEFI Boot"));
			break;
		default:
			fprintf(stderr, gettext("Unknown"));
			break;
		}
		fprintf(stderr, gettext(")\tFlags %02x ("), p->flags);
		if (p->flags & MBR_PART_FLAG_BOOTABLE)
		{
			fprintf(stderr, " Bootable");
		}
		fprintf(stderr, gettext(" )\n"));
	}
}
