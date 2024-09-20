#include "unreal.h"
#include "colors.h"
#include "lang.h"

int
diskRead (unsigned int lba, unsigned char amount, void *buf)
{
	// extra CHS from LBA
	unsigned char temp     = lba / dinfo.sectors;
	unsigned char sector   = (lba % dinfo.sectors)+1;
	unsigned char cylinder = temp/dinfo.heads;
	unsigned char head     = temp%dinfo.heads;

	unsigned short ax = 0x0200 | amount;
	unsigned short cx = (cylinder<<8)|sector;
	unsigned short dx = (head<<8)|dinfo.disk;
	unsigned char  errorCode;
	__asm__ (
		"movw %1, %%ax\n\t"
		"movw %2, %%cx\n\t"
		"movw %3, %%dx\n\t"
		"movw %4, %%bx\n\t"
		"int $0x13\n\t"
		"movw %%ax, %0\n\t"
		: "=rmsg"(ax)
		: "rmsg"(ax),
		  "rmsg"(cx),
		  "rmsg"(dx),
		  "rmsg"(buf)
		: "cc", "%ax", "%bx", "%cx", "%dx"
	);

	errorCode = ax>>8;
	if (errorCode)
	{
		diskError(errorCode);
	}

	// didn't read the right amount of stuff
	if ((ax&0xff) != amount)
	{
		puts(DISK_READ_AMOUNT, FG_RED);
		return 1;
	}
	return errorCode;
}
