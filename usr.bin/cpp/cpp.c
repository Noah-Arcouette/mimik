#include <stdio.h>
#include "pipeline.h"

const char *self = "/usr/bin/cpp";

// I/O
const char *filename = "<stdin>"; // default to standard input
FILE       *fin;
FILE       *fout;

int
main (int argc, const char **argv)
{
    // defaults
    fin  = stdin;
    fout = stdout;

    // find program name
    if (argc > 0)
    {
        self = argv[0];
    }

    // read each character
    int c;
    while ((c = fgetc(fin)) != EOF)
    {
        // send character down the pipeline, starting at line splicing
        lineSplicing(c);
    }
}
