#include <lzd.h>
#include <stdio.h>
#include <stdlib.h>

#define STRING0 (unsigned char *)"Hello, world!"
#define STRING0_SIZE             13
#define STRING0_FOUND            0b0001

#define STRING1 (unsigned char *)"Hi"
#define STRING1_SIZE             2
#define STRING1_FOUND            0b0010

#define STRING2 (unsigned char *)"Hello"
#define STRING2_SIZE             5
#define STRING2_FOUND            0b0100

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

    TITLE();
    puts("Warning this test may loop to infinity, treat this as a failure");
    if (startHistory(header))
    {
        TITLE();
        puts("Failed to start history of size 16");
        return 1;
    }

    int err = 0;

    // test first character
    struct LZD_Match match;

    pushHistory(STRING0, STRING0_SIZE);
    pushHistory(STRING1, STRING1_SIZE);
    pushHistory(STRING2, STRING2_SIZE);

    // multi-match
    int found = 0;

    findHistory(STRING0, STRING0_SIZE);
    int cont;
    do
    {
        cont = matchHistory(&match);

        if (!match.size)
            continue;

        switch (match.index)
        {
        case 0:
            if (match.size != STRING2_SIZE)
            {
                TITLE();
                puts("Incorrectly sizes first on multi-match");
                err = 1;
            }
            found |= STRING2_FOUND;
            break;
        case 1:
            TITLE();
            puts("Matches incorrectly on multi-match");
            err    = 1;
            found |= STRING1_FOUND;
            break;
        case 2:
            if (match.size != STRING0_SIZE)
            {
                TITLE();
                puts("incorrectly sizes last on multi-match");
                err = 1;
            }
            found |= STRING0_FOUND;
            break;
        default:
            TITLE();
            puts("Matched unknown on multi-match");
            err = 1;
        }
    } while (cont);

    if (found != (STRING0_FOUND | STRING2_FOUND))
    {
        TITLE();
        puts("Doesn't find matches correctly on multi-match");
        err = 1;
    }

    // single-match
    found = 0;

    findHistory(STRING1, STRING1_SIZE);
    do
    {
        cont = matchHistory(&match);

        if (!match.size)
            continue;

        switch (match.index)
        {
        case 0:
            TITLE();
            puts("Matches first incorrectly on single-match");
            err    = 1;
            found |= STRING2_FOUND;
            break;
        case 1:
            if (match.size != STRING1_SIZE)
            {
                TITLE();
                puts("Incorrectly sizes middle on single-match");
                err = 1;
            }
            found |= STRING1_FOUND;
            break;
        case 2:
            TITLE();
            puts("Matches last incorrectly on single-match");
            err    = 1;
            found |= STRING0_FOUND;
            break;
        default:
            TITLE();
            puts("Matched unknow on multi-match");
            err = 1;
        }
    } while (cont);

    if (found != STRING1_FOUND)
    {
        TITLE();
        puts("Doesn't find matches correctly on single-match");
        err = 1;
    }

    // zero-match
    findHistory((unsigned char *)"TEST", 4);
    do
    {
        cont = matchHistory(&match);

        if (!match.size)
            continue;

        switch (match.index)
        {
        case 0:
            TITLE();
            puts("Matches first incorrectly on zero-match");
            err    = 1;
            break;
        case 1:
            TITLE();
            puts("Matches middle incorrectly on zero-match");
            err    = 1;
            break;
        case 2:
            TITLE();
            puts("Matches last incorrectly on zero-match");
            err    = 1;
            break;
        default:
            TITLE();
            puts("Matched unknow on multi-match");
            err = 1;
        }
    } while (cont);

    stopHistory();

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
