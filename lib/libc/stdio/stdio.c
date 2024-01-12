#include "stdio.h"
#include <unistd.h>

FILE *stdin;
FILE *stdout;
FILE *stderr;
size_t __stdio_file_bitmap;
FILE   __stdio_files[FOPEN_MAX];

void
__init_stdio (void)
{
    __stdio_file_bitmap = 0; // nothing is in use
    stdin = fdopen(STDIN_FILENO, "r");
    setvbuf(stdin, (char*)NULL, _IOFBF, BUFSIZ);

    stdout = fdopen(STDOUT_FILENO, "w");
    setvbuf(stdout, (char*)NULL, _IOLBF, BUFSIZ);

    stderr = fdopen(STDERR_FILENO, "r+");
    setvbuf(stderr, (char*)NULL, _IONBF, BUFSIZ);
}
