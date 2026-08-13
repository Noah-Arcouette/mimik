#include "../main.h"
#include "../lex.h"
#include <libintl.h>
#include <string.h>
#include <ctype.h>

struct lex_token lex_token = {
	.type  = LEX_TOKEN_TYPE_EOF,
	.buf   = NULL,
	.bufsz = 0,
	.bufcp = 0
};

void
lex (void)
{
	// reset the lexer context
	lex_newToken();

	// what is the character
	int c = lex_getc();
	int d;

	switch (c)
	{
	case '\n':
		lex_token.type = LEX_TOKEN_TYPE_NEWLINE;
		break;
	case EOF:
		lex_token.type = LEX_TOKEN_TYPE_EOF;
		break;
	case '!':
		lex_token.type = LEX_TOKEN_TYPE_LOGICAL_NOT;

		c = lex_getc();
		if (c == '=')
		{
			lex_token.type = LEX_TOKEN_TYPE_NOT_EQUALS;
		}
		else lex_ungetc(c);
		break;
	case '%':
		lex_token.type = LEX_TOKEN_TYPE_MODULO;

		c = lex_getc();
		if (c == '=')
		{
			lex_token.type = LEX_TOKEN_TYPE_ASSIGN_MODULO;
		}
		else lex_ungetc(c);
		break;
	case '^':
		lex_token.type = LEX_TOKEN_TYPE_XOR;

		c = lex_getc();
		if (c == '=')
		{
			lex_token.type = LEX_TOKEN_TYPE_ASSIGN_XOR;
		}
		else lex_ungetc(c);
		break;
	case '&':
		lex_token.type = LEX_TOKEN_TYPE_BITWISE_AND;

		c = lex_getc();
		if (c == '=')
		{
			lex_token.type = LEX_TOKEN_TYPE_ASSIGN_AND;
		}
		else if (c == '&')
		{
			lex_token.type = LEX_TOKEN_TYPE_LOGICAL_AND;
		}
		else lex_ungetc(c);
		break;
	case '*':
		lex_token.type = LEX_TOKEN_TYPE_MULTIPLY;

		c = lex_getc();
		if (c == '=')
		{
			lex_token.type = LEX_TOKEN_TYPE_ASSIGN_MULTIPLY;
		}
		else lex_ungetc(c);
		break;
	case '-':
		lex_token.type = LEX_TOKEN_TYPE_MINUS;

		c = lex_getc();
		if (c == '=')
		{
			lex_token.type = LEX_TOKEN_TYPE_ASSIGN_MINUS;
		}
		else if (c == '-')
		{
			lex_token.type = LEX_TOKEN_TYPE_DECREMENT;
		}
		else if (c == '>')
		{
			lex_token.type = LEX_TOKEN_TYPE_MEMBER;
		}
		else lex_ungetc(c);
		break;
	case '=':
		lex_token.type = LEX_TOKEN_TYPE_ASSIGN;

		c = lex_getc();
		if (c == '=')
		{
			lex_token.type = LEX_TOKEN_TYPE_EQUALS;
		}
		else lex_ungetc(c);
		break;
	case '+':
		lex_token.type = LEX_TOKEN_TYPE_PLUS;

		c = lex_getc();
		if (c == '=')
		{
			lex_token.type = LEX_TOKEN_TYPE_ASSIGN_PLUS;
		}
		else if (c == '+')
		{
			lex_token.type = LEX_TOKEN_TYPE_INCREMENT;
		}
		else lex_ungetc(c);
		break;
	case '|':
		lex_token.type = LEX_TOKEN_TYPE_BITWISE_OR;

		c = lex_getc();
		if (c == '=')
		{
			lex_token.type = LEX_TOKEN_TYPE_ASSIGN_OR;
		}
		else if (c == '|')
		{
			lex_token.type = LEX_TOKEN_TYPE_LOGICAL_OR;
		}
		else lex_ungetc(c);
		break;
	case '/':
		lex_token.type = LEX_TOKEN_TYPE_DIVIDE;

		c = lex_getc();
		if (c == '=')
		{
			lex_token.type = LEX_TOKEN_TYPE_ASSIGN_DIVIDE;
		}
		else if (c == '/') // single line comment
		{
			while (c != '\n' && c != EOF)
			{
				c = lex_getc();
			}
			lex_ungetc('\n');
			lex_token.type = LEX_TOKEN_TYPE_COMMENT;
		}
		else if (c == '*') // multi-line comment
		{
			d = '\0';
			while (!(c == '/' && d == '*') && c != EOF)
			{
				d = c;
				c = lex_getc();
			}
			lex_token.type = LEX_TOKEN_TYPE_COMMENT;
		}
		else lex_ungetc(c);
		break;
	case '>':
		lex_token.type = LEX_TOKEN_TYPE_GREATER;

		c = lex_getc();
		if (c == '=')
		{
			lex_token.type = LEX_TOKEN_TYPE_GREATER_OR_EQUAL;
		}
		else if (c == '>')
		{
			lex_token.type = LEX_TOKEN_TYPE_SHIFT_RIGHT;

			c = lex_getc();
			if (c == '=')
			{
				lex_token.type = LEX_TOKEN_TYPE_ASSIGN_SHIFT_RIGHT;
			}
			else if (c == '>')
			{
				lex_token.type = LEX_TOKEN_TYPE_ROLL_RIGHT;

				c = lex_getc();
				if (c == '=')
				{
					lex_token.type = LEX_TOKEN_TYPE_ASSIGN_ROLL_RIGHT;
				}
				else lex_ungetc(c);
			}
			else lex_ungetc(c);
		}
		else lex_ungetc(c);
		break;
	case '<':
		lex_token.type = LEX_TOKEN_TYPE_LESSER;

		c = lex_getc();
		if (c == '=')
		{
			lex_token.type = LEX_TOKEN_TYPE_LESSER_OR_EQUAL;
		}
		else if (c == '<')
		{
			lex_token.type = LEX_TOKEN_TYPE_SHIFT_LEFT;

			c = lex_getc();
			if (c == '=')
			{
				lex_token.type = LEX_TOKEN_TYPE_ASSIGN_SHIFT_LEFT;
			}
			else if (c == '<')
			{
				lex_token.type = LEX_TOKEN_TYPE_ROLL_LEFT;

				c = lex_getc();
				if (c == '=')
				{
					lex_token.type = LEX_TOKEN_TYPE_ASSIGN_ROLL_LEFT;
				}
				else lex_ungetc(c);
			}
			else lex_ungetc(c);
		}
		else lex_ungetc(c);
		break;
	case '.':
		lex_token.type = LEX_TOKEN_TYPE_PERIOD;

		c = lex_getc();
		if (c == '.')
		{
			c = lex_getc();
			if (c == '.')
			{
				lex_token.type = LEX_TOKEN_TYPE_ELLIPSES;
			}
			else
			{
				lex_ungetc(c);
				lex_ungetc('.');
			}
		}
		else if (isdigit(c))
		{
			c = '.'; // shhhhhh, we'll just lie to it don't worry
			goto _number;
		}
		else lex_ungetc(c);
		break;
	case '"':
		lex_token.type = LEX_TOKEN_TYPE_STRING;
		d = '\\'; // pretend we escaped the first one
		while (c != EOF && (c != '"' || d == '\\'))
		{
			d = c;
			c = lex_getc();
		}
		break;
	case '\'':
		lex_token.type = LEX_TOKEN_TYPE_CHARACTER;
		d = '\\'; // pretend we escaped the first one
		while (c != EOF && (c != '\'' || d == '\\'))
		{
			d = c;
			c = lex_getc();
		}
		break;
	case '~':
		lex_token.type = LEX_TOKEN_TYPE_BITWISE_NOT;
		break;
	case '#':
		lex_token.type = LEX_TOKEN_TYPE_HASH;
		break;
	case '(':
		lex_token.type = LEX_TOKEN_TYPE_OPEN_PAREN;
		break;
	case ')':
		lex_token.type = LEX_TOKEN_TYPE_CLOSE_PAREN;
		break;
	case '[':
		lex_token.type = LEX_TOKEN_TYPE_OPEN_SQUARE;
		break;
	case ']':
		lex_token.type = LEX_TOKEN_TYPE_CLOSE_SQUARE;
		break;
	case '{':
		lex_token.type = LEX_TOKEN_TYPE_OPEN_CURLY;
		break;
	case '}':
		lex_token.type = LEX_TOKEN_TYPE_CLOSE_CURLY;
		break;
	case ';':
		lex_token.type = LEX_TOKEN_TYPE_SEMICOLON;
		break;
	case ':':
		lex_token.type = LEX_TOKEN_TYPE_COLON;
		break;
	case ',':
		lex_token.type = LEX_TOKEN_TYPE_COMMA;
		break;
	case '?':
		lex_token.type = LEX_TOKEN_TYPE_TERTIARY;
		break;
	default:
		// whitespace
		if (isspace(c))
		{
			while (isspace(c))
			{
				c = lex_getc();
			}
			lex_ungetc(c);
			lex_token.type = LEX_TOKEN_TYPE_WHITESPACE;
			break;
		}

		// symbols
		if (isalpha(c) || c == '_')
		{
			while (isalnum(c) || c == '_')
			{
				c = lex_getc();
			}
			lex_ungetc(c);
			lex_token.type = LEX_TOKEN_TYPE_SYMBOL;

			// check for reserved words
			switch (lex_token.buf[0])
			{
			case '_':
				switch (lex_token.buf[1])
				{
				case 'A':
					if (!strcmp(lex_token.buf+2, "tomic"))
					{
						lex_token.type = LEX_TOKEN_TYPE_ATOMIC;
					}
					else if (!strcmp(lex_token.buf+2, "lignas"))
					{
						lex_prettyprint(gettext(
							"`_Alignas' is deprecated, use `alignas'\n"));
						lex_token.type = LEX_TOKEN_TYPE_ALIGNAS;
					}
					else if (!strcmp(lex_token.buf+2, "lignof"))
					{
						lex_prettyprint(gettext(
							"`_Alignof' is deprecated, use `alignof'\n"));
						lex_token.type = LEX_TOKEN_TYPE_ALIGNOF;
					}
					break;
				case 'B':
					if (!strcmp(lex_token.buf+2, "itInt"))
					{
						lex_token.type = LEX_TOKEN_TYPE_BITINT;
					}
					else if (!strcmp(lex_token.buf+2, "ool"))
					{
						lex_prettyprint(
							gettext("`_Bool' is deprecated, use `bool'\n"));
						lex_token.type = LEX_TOKEN_TYPE_BOOL;
					}
					break;
				case 'C':
					if (!strcmp(lex_token.buf+2, "omplex"))
					{
						lex_token.type = LEX_TOKEN_TYPE_COMPLEX;
					}
					else if (!strcmp(lex_token.buf+2, "ountof"))
					{
						lex_token.type = LEX_TOKEN_TYPE_COUNTOF;
					}
					break;
				case 'D':
					if (!strcmp(lex_token.buf+2, "ecimal32"))
					{
						lex_token.type = LEX_TOKEN_TYPE_DECIMAL32;
					}
					else if (!strcmp(lex_token.buf+2, "ecimal64"))
					{
						lex_token.type = LEX_TOKEN_TYPE_DECIMAL64;
					}
					else if (!strcmp(lex_token.buf+2, "ecimal128"))
					{
						lex_token.type = LEX_TOKEN_TYPE_DECIMAL128;
					}
					break;
				case 'G':
					if (!strcmp(lex_token.buf+2, "eneric"))
					{
						lex_token.type = LEX_TOKEN_TYPE_GENERIC;
					}
					break;
				case 'N':
					if (!strcmp(lex_token.buf+2, "oreturn"))
					{
						lex_prettyprint(gettext(
					"`_Noreturn' is deprecated, use `[[noreturn]]'\n"));
						lex_token.type = LEX_TOKEN_TYPE_NORETURN;
					}
					break;
				case 'P':
					if (!strcmp(lex_token.buf+2, "ragma"))
					{
						lex_token.type = LEX_TOKEN_TYPE_PRAGMA;
					}
					break;
				case 'S':
					if (!strcmp(lex_token.buf+2, "tatic_assert"))
					{
						lex_prettyprint(gettext(
					"`_Static_assert' is deprecated, use `static_assert'\n"));
						lex_token.type = LEX_TOKEN_TYPE_STATIC_ASSERT;
					}
					break;
				case 'T':
					if (!strcmp(lex_token.buf+2, "hread_local"))
					{
						lex_prettyprint(gettext(
					"`_Thread_local' is deprecated, use `thread_local'\n"));
						lex_token.type = LEX_TOKEN_TYPE_THREAD_LOCAL;
					}
					break;
				case '_':
					if (!strcmp(lex_token.buf+2, "asm__"))
					{
						lex_token.type = LEX_TOKEN_TYPE_ASM;
					}
					else if (!strcmp(lex_token.buf+2, "attribute__"))
					{
						lex_prettyprint(gettext(
					"`__attribute__' is deprecated, use `[[...]]'\n"));
						lex_token.type = LEX_TOKEN_TYPE_ATTRIBUTE;
					}
					break;
				}
				break;
			case 'a':
				if (!strcmp(lex_token.buf+1, "lignas"))
				{
					lex_token.type = LEX_TOKEN_TYPE_ALIGNAS;
				}
				else if (!strcmp(lex_token.buf+1, "lignof"))
				{
					lex_token.type = LEX_TOKEN_TYPE_ALIGNOF;
				}
				else if (!strcmp(lex_token.buf+1, "uto"))
				{
					lex_token.type = LEX_TOKEN_TYPE_AUTO;
				}
				break;
			case 'b':
				if (!strcmp(lex_token.buf+1, "ool"))
				{
					lex_token.type = LEX_TOKEN_TYPE_BOOL;
				}
				else if (!strcmp(lex_token.buf+1, "reak"))
				{
					lex_token.type = LEX_TOKEN_TYPE_BREAK;
				}
				break;
			case 'c':
				if (!strcmp(lex_token.buf+1, "ase"))
				{
					lex_token.type = LEX_TOKEN_TYPE_CASE;
				}
				else if (!strcmp(lex_token.buf+1, "har"))
				{
					lex_token.type = LEX_TOKEN_TYPE_CHAR;
				}
				else if (!strcmp(lex_token.buf+1, "onst"))
				{
					lex_token.type = LEX_TOKEN_TYPE_CONST;
				}
				else if (!strcmp(lex_token.buf+1, "onstexpr"))
				{
					lex_token.type = LEX_TOKEN_TYPE_CONSTEXPR;
				}
				else if (!strcmp(lex_token.buf+1, "ontinue"))
				{
					lex_token.type = LEX_TOKEN_TYPE_CONTINUE;
				}
				break;
			case 'd':
				if (!strcmp(lex_token.buf+1, "efault"))
				{
					lex_token.type = LEX_TOKEN_TYPE_DEFAULT;
				}
				else if (!strcmp(lex_token.buf+1, "o"))
				{
					lex_token.type = LEX_TOKEN_TYPE_DO;
				}
				else if (!strcmp(lex_token.buf+1, "ouble"))
				{
					lex_token.type = LEX_TOKEN_TYPE_DOUBLE;
				}
				break;
			case 'e':
				if (!strcmp(lex_token.buf+1, "lse"))
				{
					lex_token.type = LEX_TOKEN_TYPE_ELSE;
				}
				else if (!strcmp(lex_token.buf+1, "num"))
				{
					lex_token.type = LEX_TOKEN_TYPE_ENUM;
				}
				else if (!strcmp(lex_token.buf+1, "xtern"))
				{
					lex_token.type = LEX_TOKEN_TYPE_EXTERN;
				}
				break;
			case 'f':
				if (!strcmp(lex_token.buf+1, "alse"))
				{
					lex_token.type = LEX_TOKEN_TYPE_FALSE;
				}
				else if (!strcmp(lex_token.buf+1, "loat"))
				{
					lex_token.type = LEX_TOKEN_TYPE_FLOAT;
				}
				else if (!strcmp(lex_token.buf+1, "or"))
				{
					lex_token.type = LEX_TOKEN_TYPE_FOR;
				}
				break;
			case 'g':
				if (!strcmp(lex_token.buf+1, "oto"))
				{
					lex_token.type = LEX_TOKEN_TYPE_GOTO;
				}
				break;
			case 'i':
				if (!strcmp(lex_token.buf+1, "f"))
				{
					lex_token.type = LEX_TOKEN_TYPE_IF;
				}
				else if (!strcmp(lex_token.buf+1, "nline"))
				{
					lex_token.type = LEX_TOKEN_TYPE_INLINE;
				}
				else if (!strcmp(lex_token.buf+1, "nt"))
				{
					lex_token.type = LEX_TOKEN_TYPE_INT;
				}
				break;
			case 'l':
				if (!strcmp(lex_token.buf+1, "ong"))
				{
					lex_token.type = LEX_TOKEN_TYPE_LONG;
				}
				break;
			case 'n':
				if (!strcmp(lex_token.buf+1, "ullptr"))
				{
					lex_token.type = LEX_TOKEN_TYPE_NULLPTR;
				}
				break;
			case 'r':
				if (!strcmp(lex_token.buf+1, "egister"))
				{
					lex_token.type = LEX_TOKEN_TYPE_REGISTER;
				}
				else if (!strcmp(lex_token.buf+1, "estrict"))
				{
					lex_token.type = LEX_TOKEN_TYPE_RESTRICT;
				}
				else if (!strcmp(lex_token.buf+1, "eturn"))
				{
					lex_token.type = LEX_TOKEN_TYPE_RETURN;
				}
				break;
			case 's':
				if (!strcmp(lex_token.buf+1, "hort"))
				{
					lex_token.type = LEX_TOKEN_TYPE_SHORT;
				}
				else if (!strcmp(lex_token.buf+1, "igned"))
				{
					lex_token.type = LEX_TOKEN_TYPE_SIGNED;
				}
				else if (!strcmp(lex_token.buf+1, "izeof"))
				{
					lex_token.type = LEX_TOKEN_TYPE_SIZEOF;
				}
				else if (!strcmp(lex_token.buf+1, "tatic"))
				{
					lex_token.type = LEX_TOKEN_TYPE_STATIC;
				}
				else if (!strcmp(lex_token.buf+1, "tatic_assert"))
				{
					lex_token.type = LEX_TOKEN_TYPE_STATIC_ASSERT;
				}
				else if (!strcmp(lex_token.buf+1, "truct"))
				{
					lex_token.type = LEX_TOKEN_TYPE_STRUCT;
				}
				else if (!strcmp(lex_token.buf+1, "witch"))
				{
					lex_token.type = LEX_TOKEN_TYPE_SWITCH;
				}
				break;
			case 't':
				if (!strcmp(lex_token.buf+1, "hread_local"))
				{
					lex_token.type = LEX_TOKEN_TYPE_THREAD_LOCAL;
				}
				else if (!strcmp(lex_token.buf+1, "rue"))
				{
					lex_token.type = LEX_TOKEN_TYPE_TRUE;
				}
				else if (!strcmp(lex_token.buf+1, "ypedef"))
				{
					lex_token.type = LEX_TOKEN_TYPE_TYPEDEF;
				}
				else if (!strcmp(lex_token.buf+1, "ypeof"))
				{
					lex_token.type = LEX_TOKEN_TYPE_TYPEOF;
				}
				else if (!strcmp(lex_token.buf+1, "ypeof_unqual"))
				{
					lex_token.type = LEX_TOKEN_TYPE_TYPEOF_UNQUAL;
				}
				break;
			case 'u':
				if (!strcmp(lex_token.buf+1, "nion"))
				{
					lex_token.type = LEX_TOKEN_TYPE_UNION;
				}
				else if (!strcmp(lex_token.buf+1, "nsigned"))
				{
					lex_token.type = LEX_TOKEN_TYPE_UNSIGNED;
				}
				break;
			case 'v':
				if (!strcmp(lex_token.buf+1, "oid"))
				{
					lex_token.type = LEX_TOKEN_TYPE_VOID;
				}
				else if (!strcmp(lex_token.buf+1, "olatile"))
				{
					lex_token.type = LEX_TOKEN_TYPE_VOLATILE;
				}
				break;
			case 'w':
				if (!strcmp(lex_token.buf+1, "hile"))
				{
					lex_token.type = LEX_TOKEN_TYPE_WHILE;
				}
				break;
			}
			break;
		}

		// numbers and decimals
		if (isdigit(c))
		{
		_number:
			lex_token.type = LEX_TOKEN_TYPE_NUMBER;
			while (isalnum(c) || c == '\'' || c == '.')
			{
				if (c == '.')
				{
					lex_token.type = LEX_TOKEN_TYPE_DECIMAL;
				}
				c = lex_getc();
			}
			lex_ungetc(c);
			break;
		}

		lex_token.type = LEX_TOKEN_TYPE_UNKNOWN;
		break;
	}
}
