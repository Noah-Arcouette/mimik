#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>

int
main (int argc, const char **argv)
{
	const char *self = "cp";
	if (argc >= 1)
	{
		self = argv[0];
	}

	if (argc != 3)
	{
		fprintf(stderr, "%s: Error insufficent amount of operands.\n", self);
		return 1;
	}

	struct stat statbuf;
	int error;
	// open source file
	if (stat(argv[1], &statbuf))
	{
		error = errno;
		fprintf(stderr, "%s: Failed to stat file `%s'.\n", self, argv[1]);
		fprintf(stderr, "%s: Errno %d: %s\n", self, error, strerror(error));
		return 1;
	}
	if (!S_ISREG(statbuf.st_mode))
	{
		fprintf(stderr, "%s: Error file `%s' is not a regular file.\n", self, argv[1]);
		return 1;
	}

	FILE *source = fopen(argv[1], "r");
	if (!source)
	{
		error = errno;
		fprintf(stderr, "%s: Failed to open file `%s' for reading.\n", self, argv[1]);
		fprintf(stderr, "%s: Errno %d: %s\n", self, error, strerror(error));
		return 1;
	}

	// open destination file
	if (!stat(argv[2], &statbuf))
	{
		if (!S_ISREG(statbuf.st_mode))
		{
			fprintf(stderr, "%s: Error file `%s' is not a regular file.\n", self, argv[2]);

			fclose(source);
			return 1;
		}
	}

	FILE *dest = fopen(argv[2], "w");
	if (!dest)
	{
		error = errno;
		fprintf(stderr, "%s: Failed to open file `%s' for reading.\n", self, argv[2]);
		fprintf(stderr, "%s: Errno %d: %s\n", self, error, strerror(error));

		fclose(source);
		return 1;
	}

	// copy data
	char buf[BUFSIZ];
	size_t amountRead;
	while (1)
	{
		// read data from source
		amountRead = fread(buf, 1, sizeof(buf), source);
		error = errno;

		if (ferror(source))
		{
			fprintf(stderr, "%s: Failed to read from file `%s'.\n", self, argv[1]);
			goto hardexit;
		}

		// write data to source
		// make sure to only write the amount read
		fwrite(buf, 1, amountRead, dest);
		error = errno;

		if (ferror(dest))
		{
			fprintf(stderr, "%s: Failed to write to file `%s'.\n", self, argv[2]);
			goto hardexit;
		}

		// check if we should exit
		if (feof(source))
		{
			break;
		}

		continue;

		// exit on stream error
	hardexit:
		fprintf(stderr, "%s: Errno %d: %s\n", self, error, strerror(error));

		fclose(source);
		fclose(dest);
		return 1;
	}

	// close up cleanly
	fclose(source);
	fclose(dest);
	return 0;
}
