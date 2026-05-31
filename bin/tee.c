#include <libintl.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <locale.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

int
main (int argc, char *argv[])
{
	setlocale(LC_ALL, "");
	textdomain("tee");

	int append = 0;

	// parse the arguments
	int c;
	do
	{
		c = getopt(argc, argv, "ai");

		switch (c)
		{
		case 'a':
			append = 1;
			break;
		case 'i':
			if (signal(SIGINT, SIG_IGN) == SIG_ERR)
			{
				int error = errno;
				fprintf(stderr, gettext("%s: %s\n"), argv[0], strerror(error));
				return 1;
			}
			break;
		case ':':
		case '?':
			return 1;
		}
	} while (c != -1);

	// open the output files
	int     files = argc-optind; // the rest of the arguments should be files
	FILE  **file  = malloc(sizeof(FILE *)*files);
	if (!file)
	{
		int error = errno;
		fprintf(stderr, gettext("%s: %s\n"), argv[0], strerror(error));
		return 1;
	}

	// open them up
	int bad = 0;
	for (int i = optind; i<argc; i++)
	{
		int index = i-optind;
		file[index] = fopen(argv[i], append ? "a" : "w");
		if (!file[index])
		{
			int error = errno;
			fprintf(stderr, gettext("%s: %s\n"), argv[i], strerror(error));
			bad = 1;
		}
		else
		{
			if (setvbuf(file[index], NULL, _IONBF, 0))
			{
				int error = errno;
				fprintf(stderr, gettext("%s: %s\n"), argv[i], strerror(error));
				bad = 1;
			}
		}
	}

	if (bad) goto _leave;

	// unbuffer std i/o
	if (setvbuf(stdin, NULL, _IONBF, 0))
	{
		int error = errno;
		fprintf(stderr, gettext("stdin: %s\n"), strerror(error));
		bad = 1;
	}

	if (setvbuf(stdout, NULL, _IONBF, 0))
	{
		int error = errno;
		fprintf(stderr, gettext("stdout: %s\n"), strerror(error));
		bad = 1;
	}
	if (bad) goto _leave;

	// read input into the outputs
	while (1)
	{
		int c = fgetc(stdin);
		if (c == EOF)
		{
			int error = errno;
			if (ferror(stdin))
			{
				fprintf(stderr, gettext("stdin: %s\n"), strerror(error));
				bad = 1;
			}

			break;
		}

		for (int i = 0; i<files; i++)
		{
			if (fputc(c, file[i]) == EOF)
			{
				int error = errno;
				fprintf(stderr, gettext("%s: %s\n"),
					argv[optind+i], strerror(error));
				bad = 1;
			}
		}
		if (fputc(c, stdout) == EOF)
		{
			int error = errno;
			fprintf(stderr, gettext("stdout: %s\n"), strerror(error));
			bad = 1;
		}
	}

	// free stuff
_leave:
	for (int i = 0; i<files; i++)
	{
		if (file[i]) fclose(file[i]);
	}
	free(file);

	return bad;
}
