#include "defs.h"
#include <stdlib.h>

static void
_freeNode (struct node *node)
{
	// skip if it doesn't exist
	if (!node)
	{
		return;
	}

	// free child
	_freeNode(node->child);

	// free next
	_freeNode(node->next);

	// free self
	free(node->symbol);
	node->symbol = (char*)NULL;

	free(node);
}

void
freeNodes (void)
{
	_freeNode(root.child); // root isn't allocated, nor should it have any siblings
}
