#include "main.h"
#include <libintl.h>
#include <unistd.h>
#include <locale.h>
#include <stdlib.h>

const char *self;

long errors = 0;

int bytesPerSector     = 512;
int sectorsPerCylinder = 18;
int cylindersPerHead   = 80;
int heads              = 2;
int alignment          = 1024*1024;

int dryRun       = 0;
int mayBeCorrupt = 0;

int
main (int argc, char *argv[])
{
	self = argv[0];
	setlocale(LC_ALL, "");
	textdomain("fdisk");

	// disk file
	if (openDisk(argc, argv)) return 1;
	self = argv[1];

#ifdef MBR
	mbr_enterTable(1, 1);
#endif

	int c;
	argv++;
	argc--;
	do
	{
		c = getopt(argc, argv, "+p:z:s:t:a:o:f:A:Z:C:B:H:S:dli:m:M:u:");

		switch (c)
		{
		case 'p':
			selectPartition(strtol(optarg, NULL, 10));
			break;
		// -z
		// -s
		case 't':
			changeType(optarg);
			break;
		case 'a':
			complimentFlag(optarg);
			break;

		// -o
		case 'f':
			loadFile(optarg);
			break;

		// -A
		// -Z
		case 'C':
			cylindersPerHead = strtol(optarg, NULL, 10);
			updateCHS();
			break;
		case 'H':
			heads = strtol(optarg, NULL, 10);
			updateCHS();
			break;
		case 'S':
			sectorsPerCylinder = strtol(optarg, NULL, 10);
			updateCHS();
			break;
		case 'B':
			bytesPerSector = strtol(optarg, NULL, 10);
			updateCHS();
			break;
		case 'd':
			dryRun = 1;
			break;
		case 'l':
			listParts();
			break;
		// -i
		case 'm':
			enterTable(optarg, 1);
			break;
		case 'M':
			enterTable(optarg, 0);
			break;
		case 'u':
			setBootCode(optarg);
			break;
		case ':':
		case '?':
			errors++;
			break;
		case -1:
			break;
		default:
			fprintf(stderr, gettext("%s: Unhandled option -- %c\n"), self, c);
			errors++;
			break;
		}

		// error?
		if (errors)
		{
			fprintf(stderr, gettext("%s: Aborting on argv index, %d\n"), self,
				optind);
			break;
		}
	} while (c != -1);

	// commit changes
	if (!errors)
	{
	#ifdef MBR
		mbr_commit();
	#endif
	}

	fclose(disk);

	if (mayBeCorrupt && errors)
	{
		fprintf(stderr, gettext("%s: Disk may have been corrupted\n"), self);
	}
	else if (errors)
	{
		fprintf(stderr, gettext("%s: Disk has not been written to\n"), self);
	}

	if (errors) return 1;
	return 0;
}
