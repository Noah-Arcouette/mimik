#include "unreal.h"
#include "colors.h"

int
getDiskInfo (unsigned char disk)
{
	unsigned short cylinSect;
	unsigned char  errorCode;
	__asm__ (
		"xor %%di, %%di\n\t"   // clear DI to fix some buggy BIOSes
		"movb $0x08, %%ah\n\t" // read drive params
		"movb %3, %%dl\n\t"     // disk
		"int $0x13\n\t"        // disk services
		"movb %%dh, %0\n\t"    // amount of heads
		"movw %%cx, %1\n\t"    // amount of cylinders and sectors
		"movb %%ah, %2\n\t"    // error code
		"xor %%ax, %%ax\n\t"
		"movw %%ax, %%es\n\t" // fix segment to floppy drive parameter table
		: "=ms"(dinfo.heads),
		  "=ms"(cylinSect),
		  "=ms"(errorCode)
		: "ms"(disk)
		: "%di", "%ah", "%dx", "%cx", "%bl", "cc"
	);

	if (errorCode) // error
	{
		diskError(errorCode); // print error message
		return 1;
	}

	// no error
	dinfo.disk = disk;
	dinfo.heads++;
	dinfo.sectors   = cylinSect&0b111111;                           // the first 6 bits is the sector count
	dinfo.cylinders = (cylinSect>>8 | (cylinSect&0b11000000<<6))+1; // the rest is the cylinder count, kinda

	// cylinder : 76543210 98------
	// sector   : -------- --543210

	return 0;
}
