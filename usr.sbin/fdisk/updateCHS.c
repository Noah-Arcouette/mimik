#include "main.h"

void
updateCHS (void)
{
	diskSize = heads*cylindersPerHead*sectorsPerCylinder*bytesPerSector;

#ifdef MBR
	mbr_updateCHS();
#endif
}
