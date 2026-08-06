#include "main.h"

void
updateCHS (void)
{
#ifdef MBR
	mbr_updateCHS();
#endif
}
