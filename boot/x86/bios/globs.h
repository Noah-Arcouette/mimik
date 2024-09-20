#ifndef __GLOBS_H__
#define __GLOBS_H__

// ./boot/bootsect.S
extern unsigned char bootDisk;

// ./boot/setupVideo.S
extern unsigned short columns;
extern unsigned short rows;
extern volatile unsigned char *videoMemory;

#endif
