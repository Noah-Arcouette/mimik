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
	case NODE_CONTEXT:
		printf("CONTEXT");
		break;
	case NODE_ROOT:
		printf("ROOT");
		break;
	// basics and stuff
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
	// symbols and assignment
	case NODE_SYMBOL:
		printf("SYMBOL `%s'", node->symbol);
		break;
	case NODE_ASSIGN:
		printf("ASSIGN");
		break;
	case NODE_EXTERN_DEFINE:
		printf("EXTERN-");
	case NODE_DEFINE:
		printf("DEFINE ");
		displayType(node->valueType);
		printf(" `%s'", node->symbol);
		break;
	case NODE_EXTERN_FUNCTION:
		printf("EXTERN-");
	case NODE_FUNCTION:
		printf("FUNCTION ");
		displayType(node->valueType);
		printf(" `%s'", node->symbol);
		break;
	case NODE_PARAM:
		printf("PARAM "); // parameter
		displayType(node->valueType);
		printf(" `%s'", node->symbol);
		break;
	// binary operations
	//  math
	case NODE_ADD:
		printf("ADD");
		break;
	case NODE_SUB:
		printf("SUB");
		break;
	case NODE_DIV:
		printf("DIV");
		break;
	case NODE_MOD:
		printf("MOD");
		break;
	case NODE_MUL:
		printf("MUL");
		break;
	// binary arithmetic
	case NODE_AND:
		printf("AND");
		break;
	case NODE_OR:
		printf("OR");
		break;
	case NODE_XOR:
		printf("XOR");
		break;
	// boolean operations
	case NODE_BOOL_AND:
		printf("BOOL-AND");
		break;
	case NODE_BOOL_OR:
		printf("BOOL-OR");
		break;
	case NODE_BOOL_EQ:
		printf("EQ");
		break;
	case NODE_BOOL_NEQ:
		printf("NEQ");
		break;
	case NODE_BOOL_GTE:
		printf("GTE");
		break;
	case NODE_BOOL_LTE:
		printf("LTE");
		break;
	case NODE_BOOL_GT:
		printf("GT");
		break;
	case NODE_BOOL_LT:
		printf("LT");
		break;
	// unary
	case NODE_NEG:
		printf("NEG");
		break;
	case NODE_POS:
		printf("POS");
		break;
	case NODE_NOT:
		printf("NOT");
		break;
	case NODE_BOOL_NOT:
		printf("BOOL-NOT");
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
