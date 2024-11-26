#include <stdio.h>
#include "../defs.h"

int
if_ (void)
{
    if (token != IF)
    {
        return 1;
    }
    token = (enum token)yylex(); // accept

    if (token != LPAREN)
    {
        fprintf(stderr, "%s:%zu: Missing if statement's opening parenthesis.\n", filename, lineno);
        errors++;
        // just ignore and continue
    }
    else
    {
        token = (enum token)yylex(); // accept
    }

    // get the conditions value
    struct type ccType;
    size_t      ccVar;
    if (value(&ccVar, &ccType))
    {
        fprintf(stderr, "%s:%zu: Expected value in if statements condition.\n", filename, lineno);
        errors++;
        recover();
        return 0; // recover and leave
    }

    if (token != RPAREN)
    {
        fprintf(stderr, "%s:%zu: Expected a closing parenthesis for if statement.\n", filename, lineno);
        errors++;
        // just ignore and continue
    }
    else
    {
        token = (enum token)yylex(); // accept
    }

    size_t start = ctxLabel++;
    size_t end   = ctxLabel++;
    // if statement check
    fprintf(yyout, "\tgoto @%zu, if %%%zu\n", start, ccVar);
    fprintf(yyout, "\tgoto @%zu\n",           end);
    fprintf(yyout, "%zu:\n",                  start);

    // if statement body
    pushContext();
    if (body())
    {
        fprintf(stderr, "%s:%zu: Expected body after if statement.\n", filename, lineno);
        errors++;
    }
    popContext();

    fprintf(yyout, "\tgoto @%zu\n", end);
    fprintf(yyout, "%zu:\n",        end);

    return 0;
}
