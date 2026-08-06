#include "../main.h"
#include <endian.h>

void
mbr_updateCHS (void)
{
	for (int i = 0; i<4; i++)
	{
		struct mbr_part *p = &mbr.part[i];

		if (!p->type) continue;

		int firstLBA = le32toh(p->firstLBA);
		int lastLBA  = firstLBA+le32toh(p->sectors);

		// first CHS
		int a = firstLBA/sectorsPerCylinder;
		int h = a % cylindersPerHead;
		int c = a / cylindersPerHead;
		int s = (firstLBA % sectorsPerCylinder)+1;
		p->firstCHS[0] = h&0xff;
		p->firstCHS[1] = (c>>2&0xc0) | (s&0x3f);
		p->firstCHS[2] = c&0xff;

		// last CHS
		a = lastLBA/sectorsPerCylinder;
		h = a % cylindersPerHead;
		c = a / cylindersPerHead;
		s = (lastLBA % sectorsPerCylinder)+1;
		p->lastCHS[0] = h&0xff;
		p->lastCHS[1] = (c>>2&0xc0) | (s&0x3f);
		p->lastCHS[2] = c&0xff;
	}
}
