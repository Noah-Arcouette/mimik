#include <lzd.h>
#include <stdio.h>
#include <stdlib.h>

#define STRING0 (unsigned char *)"He"
#define STRING0_SIZE             2

#define STRING1 (unsigned char *)"Hi"
#define STRING1_SIZE             2

#define STRING2 (unsigned char *)"Ho"
#define STRING2_SIZE             2

#define TITLE(x) printf("liblzd/%s %d: ", __FILE__, __LINE__)

int
main (void)
{
    struct LZD_Stream_Header header = 
    {
        .magic = "LZD",
        .revision = 0,
        .dictionary = "",
        .diction = 8,
        .offset = 12,
        .length = 8,
        .history = 16
    };

    if (startWindow(header))
    {
        TITLE();
        puts("Failed to start window of size 20");
        return 1;
    }

    int err = 0;

    struct LZD_Match match;

    pushWindow(STRING0, STRING0_SIZE);
    pushWindow(STRING1, STRING1_SIZE);
    pushWindow(STRING2, STRING2_SIZE);

    // multi-match
    findWindow(STRING0, STRING0_SIZE);
    if (matchWindow(&match))
    {
        TITLE();
        puts("Not matching first-0 enough");
        err = 1;
    }
    if (match.size != 1)
    {
        TITLE();
        puts("Mis-sizes first-0");
        err = 1;
    }
    if (match.index != 0)
    {
        TITLE();
        puts("Mismatches first-0");
        err = 1;
    }

    if (matchWindow(&match))
    {
        TITLE();
        puts("Not matching first-1 enough");
        err = 1;
    }
    if (match.size != 1)
    {
        TITLE();
        puts("Mis-sizes first-1");
        err = 1;
    }
    if (match.index != 2)
    {
        TITLE();
        puts("Mismatches first-1");
        err = 1;
    }

    if (matchWindow(&match))
    {
        TITLE();
        puts("Not matching first-2 enough");
        err = 1;
    }
    if (match.size != 1)
    {
        TITLE();
        puts("Mis-sizes first-2");
        err = 1;
    }
    if (match.index != 4)
    {
        TITLE();
        puts("Mismatches first-2");
        err = 1;
    }

    if (matchWindow(&match))
    {
        TITLE();
        puts("Matching first-3 to much");
        err = 1;
    }
    if (match.size != 2)
    {
        TITLE();
        puts("Mis-sizes first-3");
        err = 1;
    }
    if (match.index != 4)
    {
        TITLE();
        puts("Mismatches first-3");
        err = 1;
    }

    // single-match
    findWindow((unsigned char *)"i", 1);
    if (matchWindow(&match))
    {
        TITLE();
        puts("Matching single to much");
        err = 1;
    }
    if (match.size != 1)
    {
        TITLE();
        puts("Mis-sizes single");
        err = 1;
    }
    if (match.index != 3)
    {
        TITLE();
        puts("Mismatches single");
        err = 1;
    }

    // zero-match
    findWindow((unsigned char *)"P", 1);
    if (!matchWindow(&match))
    {
        TITLE();
        puts("Matching nothing to much");
        err = 1;
    }
    if (match.size != 0)
    {
        TITLE();
        puts("Mis-sizes nothing");
        err = 1;
    }

    stopWindow();

    if (err)
    {
        TITLE();
        puts("\tInconsistent!");
        return err;
    }

    TITLE();
    puts("\tConsistent");
    return 0;
}
