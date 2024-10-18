#include "../unreal.h"
#include "../colors.h"
#include "../lang.h"

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
#define TAR_SYMLINK  '2'
#define TAR_HARDLINK '1'

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

// open file returning the pointer to its inode
int
fsopen (const char *filename)
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
			return -1; // not found
		}

		// is it the searched file
		if (!strncmp(tar.name, filename, 100))
		{
			if (tar.type == TAR_SYMLINK || tar.type == TAR_HARDLINK)
			{
				return fsopen(tar.linkName);
			}
			return currentBlock; // return inode
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

// read from file
int
fsRead (unsigned int fildes, unsigned int seek, unsigned int size, void *buf);
