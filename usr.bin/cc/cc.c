#include <stdio.h>
#include <string.h>
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

int
main (void)
{
	// fill with zero
	memset(&root, 0, sizeof(struct node));

	// add nodes
	struct node test;
	memset(&test, 0, sizeof(struct node));

	addNode(&root, &test);
	struct node *c = addNode(&root, &test);
	addNode(c, &test);

	printf("Hello, world!\n");
	return 0;
}
