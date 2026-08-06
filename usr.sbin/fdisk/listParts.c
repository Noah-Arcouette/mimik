#include "main.h"

void
listParts (void)
{
#ifdef MBR
	mbr_listParts();
#endif
}
