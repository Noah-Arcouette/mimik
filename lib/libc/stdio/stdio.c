#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

FILE *stdin;
FILE *stdout;
FILE *stderr;
FILE __stdio_files[FOPEN_MAX];

void
__fini_stdio (void)
{
	// close all streams
	for (size_t i = 0; i<FOPEN_MAX; i++)
	{
		fclose(&__stdio_files[i]);
	}
}

void
__init_stdio (void)
{
	for (size_t i = 0; i<FOPEN_MAX; i++)
	{
		__stdio_files[i].flags = 0;
	}

	stdin = fdopen(STDIN_FILENO, "r");
	setvbuf(stdin, (char*)NULL, _IOFBF, BUFSIZ);

	stdout = fdopen(STDOUT_FILENO, "w");
	setvbuf(stdout, (char*)NULL, _IOLBF, BUFSIZ);

	stderr = fdopen(STDERR_FILENO, "r+");
	setvbuf(stderr, (char*)NULL, _IONBF, 0);

	atexit(&__fini_stdio);
}
