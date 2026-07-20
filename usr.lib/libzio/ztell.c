#include "_zio.h"

long
ztell (zFILE *fp)
{
	return (long)ztello(fp);
}
