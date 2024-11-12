#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

const char *self = "bin/cp";

#define OPENFILE_READ  0
#define OPENFILE_WRITE 1
FILE *
openFile (const char *file, int rw)
{
	struct stat statbuf;
	int error;
	if (stat(file, &statbuf)) // check if it exists
	{
		if (!rw) // if reading then fail
		{
			error = errno;
			fprintf(stderr, "%s: Failed to stat file `%s'\n", self, file);
			fprintf(stderr, "%s: Errno %d: %s.\n", self, error, strerror(error));
			exit(1);
		}
	}
	else if (!S_ISREG(statbuf.st_mode)) // make sure it's a regular file, if it exists
	{
		fprintf(stderr, "%s: File `%s' is not a regular file\n", self, file);
		exit(1);
	}

	FILE *fp = fopen(file, rw ? "w" : "r"); // open
	if (!fp) // failed to open
	{
		error = errno;
		fprintf(stderr, "%s: Failed to open `%s' for %s\n", self, file, rw ? "writting" : "reading");
		fprintf(stderr, "%s: Errno %d: %s.\n", self, error, strerror(error));
		exit(1);
	}

	return fp;
}

int
main (int argc, const char **argv)
{
	if (argc > 0)
	{
		self = argv[0];
	}

	if (argc != 3)
	{
		fprintf(stderr, "%s: Incorrect amount of operands\n", self);
		return 1;
	}

	// open files
	FILE *src = openFile(argv[1], OPENFILE_READ);
	FILE *dst = openFile(argv[2], OPENFILE_WRITE);

	// copy over files
	char buf[BUFSIZ];
	size_t red = 1;

	while (red)
	{
		red = fread(buf, 1, BUFSIZ, src);
		fwrite(buf, 1, red, dst);
	}

	fclose(src);
	fclose(dst);

	return 0;
}
