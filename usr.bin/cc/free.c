#include "defs.h"
#include <stdlib.h>

void
freeNode (struct node *node)
{
	// skip if it doesn't exist
	if (!node)
	{
		return;
	}

	// free child
	freeNode(node->child);
	node->child = (struct node *)NULL;

	// free next
	freeNode(node->next);
	node->next = (struct node *)NULL;

	// free self
	free(node->symbol);
	node->symbol = (char*)NULL;

	free(node);
}

void
freeNodes (void)
{
	freeNode(root.child); // root isn't allocated, nor should it have any siblings
}
