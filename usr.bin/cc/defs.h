#ifndef __DEFS_H__
#define __DEFS_H__

struct type
{
	enum { // base type
		VOID,
		CHAR,
		SHORT,
		INT,
		FLOAT,
		DOUBLE
	};
	int longness   : 2;
	int signness   : 1;
	int isVolatile : 1;
	int isConst    : 1;
	int isStatic   : 1;

	struct
	{
		int present    : 1;
		int isVolatile : 1;
		int isConst    : 1;
		int isRestrict : 1;
	} pointer[4]; // only four nested pointers
};

struct node
{
	enum {
		NODE_ROOT
	} nodeType;

	struct type valueType; // resolvable type of the expression

	char *symbol; // symbol name

	// register for definitions
	// noreturn, and inline, for functions

	struct node *next;
	struct node *child; // first child
	struct node *last;  // last child
};

// add.c
// copies child and attacks it to parent, returning a pointer to a copy of it or NULL
extern struct node *addNode (struct node *restrict parent, const struct node *restrict child);

// cc.c
extern const  char *self;
extern struct node  root;

// free.c
extern void freeNodes (void);

#endif
