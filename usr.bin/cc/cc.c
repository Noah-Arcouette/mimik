#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "defs.h"

/*

FUNCTION return name:
    PARAMETER type parameter
    CONTEXT:
        DEFINE type name
        SET name:
            CONST 10
EXTERN-FUNCTION return name:
    PARAMETER type parameter?
EXTERN-DEFINE type name

*/

const char *self = "cc";

struct node root;

const char *filename = "<stdin>";

int
main (void)
{
	// fill with zero
	memset(&root, 0, sizeof(struct node));

	// free all, known, nodes at end
	atexit(freeNodes);

	// parse
	yyparse();

	printf("Hello, world!\n");
	return 0;
}
