#include "../emit.h"
#include <mio.h>

struct MiO_Arch currentArchitecture = {
	.arch      = 0, // this is undefined
	.uarch     = 0,
	.archflags = 0,
	.sys       = 0, // this is undefined
	.usys      = 0,
	.sysflags  = 0,
};

void
emitArchitecture (void)
{
	emitSection(MIO_SPECIAL_MIO_ARCH_W);
	emit(&currentArchitecture, sizeof(currentArchitecture));
}
