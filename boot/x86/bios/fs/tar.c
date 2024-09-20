#include "../unreal.h"
#include "../colors.h"
#include "../lang.h"

#define __STR(X) #X
#define STR(X) __STR(X)

// first LBA for the data of the payload in the file system
unsigned int payloadDataStart;

// old tar format, USTAr additions aren't really needed
struct tar
{
	char name[100];     // file name
	char mode[8];       // file mode
	char uid [8];       // owner's id
	char gid [8];       // group's id
	char size[12];      // file size, in bytes
	char time[12];      // modification time
	char sum[8];        // check sum
	char type;          // file type
	char linkName[100]; // name of linked file, if any
	char padding[255];
} __attribute__((packed));

// get octal for tar.size
unsigned int
tar_getSize (const char *size)
{
	unsigned int val = 0;

	while (*size)
	{
		val *= 8; // oct
		val += (*size) - '0'; // ascii

		size++;
	}

	return val;
}

// WARNING: Does not follow any links
// setup for reading from payload file
int
fsInit (void)
{
	unsigned int currentBlock = pinfo.start;
	struct tar tar;

	unsigned int size;

	while (1)
	{
		// read new tar
		if (diskRead(currentBlock, 1, &tar))
		{
			return 1;
		}

		// tar terminator
		if (tar.name[0] == '\0')
		{
			// boot file not found
			puts(NO_BOOT_FILE, FG_RED);
			puts(STR(PAYLOAD), FG_WHITE);
			puts(NO_BOOT_FILE2, FG_RED);
			return 1;
		}

		// is it the boot file
		if (!strncmp(tar.name, STR(PAYLOAD), 100))
		{
			// set the data block
			payloadDataStart = currentBlock+1;
			return 0;
		}

		// get offset to next tar block
		size = tar_getSize(tar.size);
		currentBlock += size/512+1;

		if (size % 512)
		{
			currentBlock++;
		}
	}
}

// read from payload file
int
fsRead (unsigned int seek, unsigned int size, void *buf);
