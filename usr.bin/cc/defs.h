#ifndef __DEFS_H__
#define __DEFS_H__

struct type
{
	enum { // base type
		TYPE_VOID,
		TYPE_CHAR,
		TYPE_SHORT,
		TYPE_INT,
		TYPE_FLOAT,
		TYPE_DOUBLE
	} type;
	unsigned int longness   : 2;
	unsigned int signness   : 1; // is signed?
	unsigned int isVolatile : 1;
	unsigned int isConst    : 1;
	unsigned int isStatic   : 1;

	struct
	{
		unsigned int present    : 1;
		unsigned int isVolatile : 1;
		unsigned int isConst    : 1;
		unsigned int isRestrict : 1;
	} pointer[4]; // only four nested pointers
};

struct node
{
	enum {
		NODE_ROOT,
		NODE_VALUE,
		// binary operations
		//  math
		NODE_ADD,
		NODE_SUB,
		NODE_DIV,
		NODE_MOD,
		NODE_MUL,
		// binary arithmetic
		NODE_AND,
		NODE_OR,
		NODE_XOR,
		// boolean operations
		NODE_BOOL_AND,
		NODE_BOOL_OR,
		NODE_BOOL_EQ,
		NODE_BOOL_NEQ,
		NODE_BOOL_GTE,
		NODE_BOOL_LTE,
		NODE_BOOL_LT,
		NODE_BOOL_GT
	} nodeType;

	struct type valueType; // resolvable type of the expression

	char *symbol; // symbol name
	union { // value
		unsigned long long int uvalue;
		  signed long long int  value;
	} value;

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

extern const char *filename;

// free.c
extern void freeNodes (void);

// lexer.l
extern int yylex (void);
extern int lineno;
extern int yylex_destroy (void);

// parser.y
extern void yyerror (const char *);
extern int  yyparse (void);
#define YYSTYPE struct node
extern YYSTYPE yylval;

// display.c
extern void displayNode (struct node *, int);
extern void displayType (struct type       );

#endif
