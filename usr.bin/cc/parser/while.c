#include "../defs.h"

int
while_ (void)
{
    if (token != WHILE)
    {
        return 1;
    }
    token = (enum token)yylex(); // accept WHILE

    if (token != LPAREN)
    {
        fprintf(stderr, "%s:%zu: Missing left parenthesis on while loop.\n", filename, lineno);
        errors++;
        // continue on hoping the best
    }
    else
    {
        token = (enum token)yylex(); // accept (
    }

    // the while loop head
    size_t head = ctxLabel++;
    fprintf(yyout, "\tgoto @%zu\n", head);
    fprintf(yyout, "x %zu:\n", head);

    // get condition value
    size_t ccArg;
    if (value(&ccArg, (struct type *)NULL))
    {
        fprintf(stderr, "%s:%zu: While loop has no condition value.\n", filename, lineno);
        errors++;
        recover();
        return 0;
    }

    // get closing parameter
    if (token != RPAREN)
    {
        fprintf(stderr, "%s:%zu: Missing right parenthesis after condition value.\n", filename, lineno);
        errors++;
        // continue on
    }
    else
    {
        token = (enum token)yylex(); // accept the )
    }

    // the gotos and body
    size_t bod  = ctxLabel++;
    size_t end  = ctxLabel++;
    fprintf(yyout, "\tgoto @%zu, if %%%zu\n", bod, ccArg);
    fprintf(yyout, "\tgoto @%zu\n", end);
    fprintf(yyout, "x %zu:\n", bod);

    // body
    pushContext();
    ctx->continueTo = head; // continue and break keywords
    ctx->breakTo    = end;

    // while loop body
    if (body())
    {
        fprintf(stderr, "%s:%zu: Expected a body after closing parenthesis of while loop.\n", filename, lineno);
        errors++;
    }

    popContext();

    // end of loop
    fprintf(yyout, "\tgoto @%zu\n", head); // goto start
    fprintf(yyout, "x %zu:\n", end);
    return 0;
}
