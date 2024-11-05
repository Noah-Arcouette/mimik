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
		// Root and contexts
		NODE_ROOT,
		NODE_CONTEXT,
		// statements
		NODE_RETURN,
		NODE_IF,
		NODE_ELSE,
		// basics and lines and stuff
		NODE_VALUE,
		NODE_SYMBOL,
		NODE_ASSIGN, // symbol = value
		NODE_DEFINE,
		NODE_FUNCTION,
		NODE_PARAM, // function parameter
		NODE_EXTERN_DEFINE,
		NODE_EXTERN_FUNCTION,
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
		NODE_BOOL_GT,
		// unary operations
		NODE_NEG,
		NODE_POS,
		NODE_NOT,
		NODE_BOOL_NOT
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
extern struct node *addNode    (struct node *restrict parent, const struct node *restrict child  );
extern struct node *attachNode (struct node *restrict parent, const struct node *restrict sibling);

// cc.c
extern const  char *self;
extern struct node  root;
extern int          errors;

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
