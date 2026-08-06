#include "main.h"

void
updateCHS (void)
{
	diskSize  = heads*cylindersPerHead*sectorsPerCylinder*bytesPerSector;
	alignment = sectorsPerCylinder*bytesPerSector; // align to the cylinder

#ifdef MBR
	mbr_updateCHS();
#endif
}
