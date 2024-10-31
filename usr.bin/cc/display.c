#include <stdio.h>
#include "defs.h"

void
displayType (struct type type)
{
	// base qualifiers
	if (type.isVolatile)
	{
		printf("volatile ");
	}
	if (type.isConst)
	{
		printf("const ");
	}
	if (type.isStatic)
	{
		printf("static ");
	}

	while (type.longness--)
	{
		printf("long ");
	}

	if (!type.signness)
	{
		printf("unsigned ");
	}

	// base type
	switch (type.type)
	{
	case TYPE_VOID:
		printf("void");
		break;
	case TYPE_CHAR:
		printf("char");
		break;
	case TYPE_SHORT:
		printf("short");
		break;
	case TYPE_INT:
		printf("int");
		break;
	case TYPE_FLOAT:
		printf("float");
		break;
	case TYPE_DOUBLE:
		printf("double");
		break;
	}

	// pointer
	for (int i = 0; i<4; i++)
	{
		// stop if not present
		if (!type.pointer[i].present)
		{
			break;
		}

		if (type.pointer[i].isVolatile)
		{
			printf(" volatile");
		}
		if (type.pointer[i].isConst)
		{
			printf(" const");
		}
		if (type.pointer[i].isRestrict)
		{
			printf(" restrict");
		}

		printf("* ");
	}
}

void
displayNode (struct node *node, int depth)
{
	// print out indents for depth
	int d = depth;
	while (d--)
	{
		printf("\t");
	}

	// type
	switch (node->nodeType)
	{
	case NODE_ROOT:
		printf("ROOT");
		break;
	case NODE_VALUE:
		printf("VALUE ");
		displayType(node->valueType);

		if (node->valueType.signness)
		{
			printf(" %lli", node->value.value);
			break;
		}
		printf(" %llu", node->value.uvalue);
		break;
	default:
		printf("UNKNOWN ");
		break;
	}
	printf("\n");

	// print child
	if (node->child)
		displayNode(node->child, depth+1);

	// print next
	if (node->next)
		displayNode(node->next, depth);
}
