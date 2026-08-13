#ifndef __LEX_H__
#define __LEX_H__
#include <stdio.h>

enum lex_contextType
{
	LEX_CONTEXT_TYPE_NORMAL_FILE
};

// a context stack element
struct lex_context
{
	enum lex_contextType type; // context type

	char *name; // the reference name

	// shall be closed when popped from the context stack
	FILE *fp; // the open file pointer

	// line and token identification (for prettyprint)
	int lineno;
	int offset;
	int size;
};

/**
 * The lexer context stack
 * @file lex/push.c
 */
extern struct lex_context *lex_context;
extern int lex_contexts;

/**
 * Push a new lexer context
 * @note Will free lc's internal data if it fails
 * @param lc The lexer context to push
 * @file lex/push.c
 */
extern void lex_push (struct lex_context *lc);

enum lex_tokenType
{
	LEX_TOKEN_TYPE_EOF = 0,
	LEX_TOKEN_TYPE_BITWISE_NOT,        // ~
	LEX_TOKEN_TYPE_LOGICAL_NOT,        // !
	LEX_TOKEN_TYPE_NOT_EQUALS,         // !=
	LEX_TOKEN_TYPE_HASH,               // #
	LEX_TOKEN_TYPE_MODULO,             // %
	LEX_TOKEN_TYPE_ASSIGN_MODULO,      // %=
	LEX_TOKEN_TYPE_XOR,                // ^
	LEX_TOKEN_TYPE_ASSIGN_XOR,         // ^=
	LEX_TOKEN_TYPE_BITWISE_AND,        // &
	LEX_TOKEN_TYPE_LOGICAL_AND,        // &&
	LEX_TOKEN_TYPE_ASSIGN_AND,         // &=
	LEX_TOKEN_TYPE_MULTIPLY,           // *
	LEX_TOKEN_TYPE_ASSIGN_MULTIPLY,    // *=
	LEX_TOKEN_TYPE_OPEN_PAREN,         // (
	LEX_TOKEN_TYPE_CLOSE_PAREN,        // )
	LEX_TOKEN_TYPE_MINUS,              // -
	LEX_TOKEN_TYPE_DECREMENT,          // --
	LEX_TOKEN_TYPE_ASSIGN_MINUS,       // -=
	LEX_TOKEN_TYPE_MEMBER,             // ->
	LEX_TOKEN_TYPE_ASSIGN,             // =
	LEX_TOKEN_TYPE_EQUALS,             // ==
	LEX_TOKEN_TYPE_PLUS,               // +
	LEX_TOKEN_TYPE_ASSIGN_PLUS,        // +=
	LEX_TOKEN_TYPE_INCREMENT,          // ++
	LEX_TOKEN_TYPE_OPEN_CURLY,         // {
	LEX_TOKEN_TYPE_CLOSE_CURLY,        // }
	LEX_TOKEN_TYPE_OPEN_SQUARE,        // [
	LEX_TOKEN_TYPE_CLOSE_SQUARE,       // ]
	LEX_TOKEN_TYPE_BITWISE_OR,         // |
	LEX_TOKEN_TYPE_LOGICAL_OR,         // ||
	LEX_TOKEN_TYPE_ASSIGN_OR,          // |=
	LEX_TOKEN_TYPE_SEMICOLON,          // ;
	LEX_TOKEN_TYPE_COLON,              // :
	LEX_TOKEN_TYPE_STRING,             // "..."
	LEX_TOKEN_TYPE_CHARACTER,          // '...'
	LEX_TOKEN_TYPE_GREATER,            // >
	LEX_TOKEN_TYPE_SHIFT_RIGHT,        // >>
	LEX_TOKEN_TYPE_ROLL_RIGHT,         // >>>
	LEX_TOKEN_TYPE_ASSIGN_ROLL_RIGHT,  // >>>=
	LEX_TOKEN_TYPE_ASSIGN_SHIFT_RIGHT, // >>=
	LEX_TOKEN_TYPE_GREATER_OR_EQUAL,   // >=
	LEX_TOKEN_TYPE_LESSER,             // <
	LEX_TOKEN_TYPE_SHIFT_LEFT,         // <<
	LEX_TOKEN_TYPE_ROLL_LEFT,          // <<<
	LEX_TOKEN_TYPE_ASSIGN_ROLL_LEFT,   // <<<=
	LEX_TOKEN_TYPE_ASSIGN_SHIFT_LEFT,  // <<=
	LEX_TOKEN_TYPE_LESSER_OR_EQUAL,    // <=
	LEX_TOKEN_TYPE_COMMA,              // ,
	LEX_TOKEN_TYPE_PERIOD,             // .
	LEX_TOKEN_TYPE_DIVIDE,             // /
	LEX_TOKEN_TYPE_ASSIGN_DIVIDE,      // /=
	LEX_TOKEN_TYPE_TERTIARY,           // ?
	LEX_TOKEN_TYPE_COMMENT,            // /* ... */ or // ... newline
	LEX_TOKEN_TYPE_WHITESPACE,
	LEX_TOKEN_TYPE_NEWLINE,
	LEX_TOKEN_TYPE_SYMBOL,  // symbol literal
	LEX_TOKEN_TYPE_NUMBER,  // whole number literal
	LEX_TOKEN_TYPE_DECIMAL, // decimal literal
	LEX_TOKEN_TYPE_ALIGNAS,       // alignas, _Alignas (Deprecated)
	LEX_TOKEN_TYPE_ALIGNOF,       // alignof, _Alignof (Deprecated)
	LEX_TOKEN_TYPE_AUTO,          // auto
	LEX_TOKEN_TYPE_BOOL,          // bool, _Bool (Deprecated)
	LEX_TOKEN_TYPE_BREAK,         // break
	LEX_TOKEN_TYPE_CASE,          // case
	LEX_TOKEN_TYPE_CHAR,          // char
	LEX_TOKEN_TYPE_CONST,         // const
	LEX_TOKEN_TYPE_CONSTEXPR,     // constexpr
	LEX_TOKEN_TYPE_CONTINUE,      // continue
	LEX_TOKEN_TYPE_DEFAULT,       // default
	LEX_TOKEN_TYPE_DO,            // do
	LEX_TOKEN_TYPE_DOUBLE,        // double
	LEX_TOKEN_TYPE_ELSE,          // else
	LEX_TOKEN_TYPE_ENUM,          // enum
	LEX_TOKEN_TYPE_EXTERN,        // extern
	LEX_TOKEN_TYPE_FLOAT,         // float
	LEX_TOKEN_TYPE_FOR,           // for
	LEX_TOKEN_TYPE_GOTO,          // goto
	LEX_TOKEN_TYPE_IF,            // if
	LEX_TOKEN_TYPE_INLINE,        // inline
	LEX_TOKEN_TYPE_INT,           // int
	LEX_TOKEN_TYPE_LONG,          // long
	LEX_TOKEN_TYPE_REGISTER,      // register
	LEX_TOKEN_TYPE_RESTRICT,      // restrict
	LEX_TOKEN_TYPE_RETURN,        // return
	LEX_TOKEN_TYPE_SHORT,         // short
	LEX_TOKEN_TYPE_SIGNED,        // signed
	LEX_TOKEN_TYPE_SIZEOF,        // sizeof
	LEX_TOKEN_TYPE_STATIC,        // static
	LEX_TOKEN_TYPE_STATIC_ASSERT, // static_assert, _Static_assert (Deprecated)
	LEX_TOKEN_TYPE_STRUCT,        // struct
	LEX_TOKEN_TYPE_SWITCH,        // switch
	LEX_TOKEN_TYPE_THREAD_LOCAL,  // thread_local, _Thread_local (Deprecated)
	LEX_TOKEN_TYPE_TYPEDEF,       // typedef
	LEX_TOKEN_TYPE_TYPEOF,        // typeof
	LEX_TOKEN_TYPE_TYPEOF_UNQUAL, // typeof_unqual
	LEX_TOKEN_TYPE_UNION,         // union
	LEX_TOKEN_TYPE_UNSIGNED,      // unsigned
	LEX_TOKEN_TYPE_VOID,          // void
	LEX_TOKEN_TYPE_VOLATILE,      // volatile
	LEX_TOKEN_TYPE_WHILE,         // while
	LEX_TOKEN_TYPE_ATOMIC,        // _Atomic
	LEX_TOKEN_TYPE_BITINT,        // _BitInt
	LEX_TOKEN_TYPE_COMPLEX,       // _Complex
	LEX_TOKEN_TYPE_COUNTOF,       // _Countof
	LEX_TOKEN_TYPE_DECIMAL32,     // _Decimal32
	LEX_TOKEN_TYPE_DECIMAL64,     // _Decimal64
	LEX_TOKEN_TYPE_DECIMAL128,    // _Decimal128
	LEX_TOKEN_TYPE_GENERIC,       // _Generic
	LEX_TOKEN_TYPE_NORETURN,      // _Noreturn (Deprecated)
	LEX_TOKEN_TYPE_PRAGMA,        // _Pragma
	LEX_TOKEN_TYPE_ASM,           // __asm__
	LEX_TOKEN_TYPE_ATTRIBUTE,     // __attribute__ (Deprecated)
	LEX_TOKEN_TYPE_NULLPTR,       // nullptr
	LEX_TOKEN_TYPE_TRUE,          // true
	LEX_TOKEN_TYPE_FALSE,         // false
	LEX_TOKEN_TYPE_ELLIPSES,      // ...
	LEX_TOKEN_TYPE_UNKNOWN // everything else hah
};

// A lexer token
struct lex_token
{
	enum lex_tokenType type;

	char *buf;
	int   bufsz;
	int   bufcp;
};

/**
 * The current lexer token
 * @file lex/lex.c
 */
extern struct lex_token lex_token;

/**
 * Get the next lexer token
 * @file lex/lex.c
 */
extern void lex (void);

/**
 * Pop the lexer context
 * @file lex/pop.c
 */
extern void lex_pop (void);

/**
 * Enter a new token, setting up the context (prettyprint info) for it
 * @file lex/newToken.c
 */
extern void lex_newToken (void);

/**
 * Free all lexer data
 * @file lex/free.c
 */
extern void lex_free (void);

/**
 * Get a character from the lexer context
 * @file lex/getc.c
 * @returns The character
 */
extern int lex_getc (void);

/**
 * Unget a character onto the lexer context
 * @file lex/ungetc.c
 * @param c The character to unget
 */
extern void lex_ungetc (char c);

/**
 * pretty print an error message
 * @param fmt The printf format string
 * @file lex/prettyprint.c
 */
extern void lex_prettyprint (const char *fmt, ...);

/**
 * Print line markers to the file
 * @file lex/push.c
 */
extern FILE *lex_lineMarkers;

/**
 * Get the next token ignoring whitespace (but not ignoring newlines)
 * @file lex/nowhitespace.c
 */
extern void lex_nowhitespace (void);

/**
 * Recover to a specific token
 * @file lex/recover.c
 * @param n The amount of allowed tokens to stop at
 * @param ... The given token types to stop at
 */
extern void lex_recover (int n, ...);

#endif
