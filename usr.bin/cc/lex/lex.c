#include "../main.h"
#include "../lex.h"
#include <libintl.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <ctype.h>

static int
_getc (void)
{
	int c = fgetc(lex_context.fp);

	if (c == EOF)
	{
		if (ferror(lex_context.fp))
		{
			fprintf(stderr, gettext("%s: Failed to read from file `%s', %s\n"),
				self, lex_context.path, strerror(errno));
			errors++;
		}
		return EOF;
	}

	// grow buffer
	lex_context.size++;
	lex_token.bufsz++;
	if ((lex_token.bufsz+1) > lex_token.bufcp)
	{
		lex_token.bufcp = 3*(lex_token.bufsz+1)/2;
		void *buf = realloc(lex_token.buf, lex_token.bufcp);
		if (!buf)
		{
			lex_token.bufsz--;
			lex_token.bufcp = lex_token.bufsz;
			fprintf(stderr, gettext("%s: %s\n"), self, strerror(errno));
			errors++;
			return EOF;
		}
		lex_token.buf = buf;
	}

	// add the character to the buffer
	lex_token.buf[lex_token.bufsz-1] = c;
	lex_token.buf[lex_token.bufsz  ] = '\0';

	// specials
	if (c == '\n')
	{
		lex_context.size   = 0;
		lex_context.offset = 0;
		lex_context.lineno++;
	}
	else if (c == '\\')
	{
		int c = fgetc(lex_context.fp);
		if (c == '\n')
		{
			lex_token.bufsz--;
			lex_context.size--;
			lex_token.buf[lex_token.bufsz] = '\0';
			return _getc(); // ignore the newline
		}
		ungetc(c, lex_context.fp);
		c = '\\';
	}
	return c;
}

static void
_ungetc (int c)
{
	if (c != EOF) ungetc(c, lex_context.fp);

	lex_context.size--;
	lex_token.bufsz--;
	lex_token.buf[lex_token.bufsz] = '\0';
}

void
lex (void)
{
	// set size and offset
	lex_context.offset += lex_context.size;
	lex_context.size = 0;
	lex_token.bufsz  = 0;

	// get first letter
	int c = _getc();
	int d;

	// what is it
	switch (c)
	{
	case EOF:
		lex_token.type = LEX_TOKEN_TYPE_EOF;
		break;
	case '/':
		lex_token.type = c;

		c = _getc();
		if (c == '/') // line comment
		{
			while (c != '\n' && c != EOF)
			{
				c = _getc();
			}
			_ungetc(c);
			lex_token.type = LEX_TOKEN_TYPE_COMMENT;
		}
		else if (c == '*') // block comment
		{
			d = c;/**/
			c = _getc();
			while (c != EOF && !(c == '/' && d == '*'))
			{
				d = c;
				c = _getc();
			}
			lex_token.type = LEX_TOKEN_TYPE_COMMENT;
		}
		else _ungetc(c);
		break;
	case '\'':
		d = '\\';
		while (c != EOF && c != '\n' && (c != '\'' || d == '\\'))
		{
			d = c;
			c = _getc();
		}
		lex_token.type = LEX_TOKEN_TYPE_LITERAL_CHARACTER;
		break;
	case '"':
		d = '\\';
		while (c != EOF && c != '\n' && (c != '"' || d == '\\'))
		{
			d = c;
			c = _getc();
		}
		lex_token.type = LEX_TOKEN_TYPE_LITERAL_STRING;
		break;
	case '%':
		lex_token.type = c;
		c = _getc();

		if (c == '=') lex_token.type = LEX_TOKEN_TYPE_ASSIGN_MODULO;
		else _ungetc(c);
		break;
	case '^':
		lex_token.type = c;
		c = _getc();

		if (c == '=') lex_token.type = LEX_TOKEN_TYPE_ASSIGN_BITWISE_XOR;
		else _ungetc(c);
		break;
	case '&':
		lex_token.type = c;
		c = _getc();

		if (c == '=') lex_token.type = LEX_TOKEN_TYPE_ASSIGN_BITWISE_AND;
		if (c == '&') lex_token.type = LEX_TOKEN_TYPE_LOGICAL_AND;
		else _ungetc(c);
		break;
	case '*':
		lex_token.type = c;
		c = _getc();

		if (c == '=') lex_token.type = LEX_TOKEN_TYPE_ASSIGN_MULTIPLY;
		else _ungetc(c);
		break;
	case '-':
		lex_token.type = c;
		c = _getc();

		if (c == '=') lex_token.type = LEX_TOKEN_TYPE_ASSIGN_SUBTRACT;
		if (c == '-') lex_token.type = LEX_TOKEN_TYPE_DECREMENT;
		if (c == '>') lex_token.type = LEX_TOKEN_TYPE_MEMBER;
		else _ungetc(c);
		break;
	case '+':
		lex_token.type = c;
		c = _getc();

		if (c == '=') lex_token.type = LEX_TOKEN_TYPE_ASSIGN_ADD;
		if (c == '+') lex_token.type = LEX_TOKEN_TYPE_INCREMENT;
		else _ungetc(c);
		break;
	case '|':
		lex_token.type = c;
		c = _getc();

		if (c == '=') lex_token.type = LEX_TOKEN_TYPE_ASSIGN_BITWISE_OR;
		if (c == '|') lex_token.type = LEX_TOKEN_TYPE_LOGICAL_OR;
		else _ungetc(c);
		break;
	case '!':
		lex_token.type = c;
		c = _getc();

		if (c == '=') lex_token.type = LEX_TOKEN_TYPE_NOT_EQUATE;
		else _ungetc(c);
		break;
	case '=':
		lex_token.type = c;
		c = _getc();

		if (c == '=') lex_token.type = LEX_TOKEN_TYPE_EQUATE;
		else _ungetc(c);
		break;
	case '.':
		lex_token.type = c;
		c = _getc();
		if (isdigit(c)) goto _number;
		else _ungetc(c);
		break;
	case '#':
		c = _getc();
		// eat any whitespace after it
		while (isspace(c) && c != '\n')
		{
			c = _getc();
		}
		long offset = lex_token.bufsz-1;
		// eat the first word
		while (isalpha(c))
		{
			c = _getc();
		}
		_ungetc(c);

		lex_token.type = LEX_TOKEN_TYPE_HASH;
		// find the word
		switch (lex_token.buf[offset])
		{
		case 'i':
			if (!strcmp(lex_token.buf+offset+1, "f"))
			{
				lex_token.type = LEX_TOKEN_TYPE_HASH_IF;
			}
			else if (!strcmp(lex_token.buf+offset+1, "fdef"))
			{
				lex_token.type = LEX_TOKEN_TYPE_HASH_IFDEF;
			}
			else if (!strcmp(lex_token.buf+offset+1, "fndef"))
			{
				lex_token.type = LEX_TOKEN_TYPE_HASH_IFNDEF;
			}
			else if (!strcmp(lex_token.buf+offset+1, "nclude"))
			{
				lex_token.type = LEX_TOKEN_TYPE_HASH_INCLUDE;
			}
			break;
		case 'u':
			if (!strcmp(lex_token.buf+offset+1, "ndef"))
			{
				lex_token.type = LEX_TOKEN_TYPE_HASH_UNDEF;
			}
			break;
		case 'd':
			if (!strcmp(lex_token.buf+offset+1, "efine"))
			{
				lex_token.type = LEX_TOKEN_TYPE_HASH_DEFINE;
			}
			break;
		case 'l':
			if (!strcmp(lex_token.buf+offset+1, "ine"))
			{
				lex_token.type = LEX_TOKEN_TYPE_HASH_LINE;
			}
			break;
		case 'w':
			if (!strcmp(lex_token.buf+offset+1, "arning"))
			{
				lex_token.type = LEX_TOKEN_TYPE_HASH_WARNING;
			}
			break;
		case 'p':
			if (!strcmp(lex_token.buf+offset+1, "ragma"))
			{
				lex_token.type = LEX_TOKEN_TYPE_HASH_PRAGMA;
			}
			break;
		case '_':
			if (!strcmp(lex_token.buf+offset+1, "_has_include"))
			{
				lex_token.type = LEX_TOKEN_TYPE_HASH_HAS_INCLUDE;
			}
			else if (!strcmp(lex_token.buf+offset+1, "_has_embed"))
			{
				lex_token.type = LEX_TOKEN_TYPE_HASH_HAS_EMBED;
			}
			else if (!strcmp(lex_token.buf+offset+1, "_has_c_attribute"))
			{
				lex_token.type = LEX_TOKEN_TYPE_HASH_HAS_C_ATTRIBUTE;
			}
			break;
		case 'e':
			if (!strcmp(lex_token.buf+offset+1, "lif"))
			{
				lex_token.type = LEX_TOKEN_TYPE_HASH_ELIF;
			}
			else if (!strcmp(lex_token.buf+offset+1, "lse"))
			{
				lex_token.type = LEX_TOKEN_TYPE_HASH_ELSE;
			}
			else if (!strcmp(lex_token.buf+offset+1, "ndif"))
			{
				lex_token.type = LEX_TOKEN_TYPE_HASH_ENDIF;
			}
			else if (!strcmp(lex_token.buf+offset+1, "lifdef"))
			{
				lex_token.type = LEX_TOKEN_TYPE_HASH_ELIFDEF;
			}
			else if (!strcmp(lex_token.buf+offset+1, "lifndef"))
			{
				lex_token.type = LEX_TOKEN_TYPE_HASH_ELIFNDEF;
			}
			else if (!strcmp(lex_token.buf+offset+1, "mbed"))
			{
				lex_token.type = LEX_TOKEN_TYPE_HASH_EMBED;
			}
			else if (!strcmp(lex_token.buf+offset+1, "rror"))
			{
				lex_token.type = LEX_TOKEN_TYPE_HASH_ERROR;
			}
			break;
		}

		break;
	case '~':
	case '?':
	case ',':
	case ';':
	case ':':
	case '(':
	case ')':
	case '[':
	case ']':
	case '{':
	case '}':
		lex_token.type = c;
		break;
	case '<':
		c = _getc();
		if (c == '<')
		{
			c = _getc();
			if (c == '<')
			{
				c = _getc();
				if (c == '=')
				{
					lex_token.type = LEX_TOKEN_TYPE_ASSIGN_ROLL_LEFT;
				}
				else
				{
					lex_token.type = LEX_TOKEN_TYPE_ROLL_LEFT;
					_ungetc(c);
				}
			}
			else if (c == '=')
			{
				lex_token.type = LEX_TOKEN_TYPE_ASSIGN_SHIFT_LEFT;
			}
			else
			{
				lex_token.type = LEX_TOKEN_TYPE_SHIFT_LEFT;
				_ungetc(c);
			}
		}
		else if (c == '=')
		{
			lex_token.type = LEX_TOKEN_TYPE_LESS_THAN_OR_EQUAL;
		}
		else
		{
			lex_token.type = LEX_TOKEN_TYPE_LESS_THAN;
			_ungetc(c);
		}
		break;
	case '>':
		c = _getc();
		if (c == '>')
		{
			c = _getc();
			if (c == '>')
			{
				c = _getc();
				if (c == '=')
				{
					lex_token.type = LEX_TOKEN_TYPE_ASSIGN_ROLL_RIGHT;
				}
				else
				{
					lex_token.type = LEX_TOKEN_TYPE_ROLL_RIGHT;
					_ungetc(c);
				}
			}
			else if (c == '=')
			{
				lex_token.type = LEX_TOKEN_TYPE_ASSIGN_SHIFT_RIGHT;
			}
			else
			{
				lex_token.type = LEX_TOKEN_TYPE_SHIFT_RIGHT;
				_ungetc(c);
			}
		}
		else if (c == '=')
		{
			lex_token.type = LEX_TOKEN_TYPE_GREATER_THAN_OR_EQUAL;
		}
		else
		{
			lex_token.type = LEX_TOKEN_TYPE_GREATER_THAN;
			_ungetc(c);
		}
		break;
	default:
		if (isspace(c))
		{
			while (isspace(c))
			{
				c = _getc();
			}
			_ungetc(c);
			lex_token.type = LEX_TOKEN_TYPE_WHITESPACE;
			break;
		}

		if (isalpha(c) || c == '_')
		{
			while (isalnum(c) || c == '_')
			{
				c = _getc();
			}
			_ungetc(c);

			lex_token.type = LEX_TOKEN_TYPE_SYMBOL;

			// look for reserved words
			switch (lex_token.buf[0])
			{
			case '_':
				switch (lex_token.buf[1])
				{
				case 'A':
					if (!strcmp(lex_token.buf+2, "lignas"))
					{
						lex_token.type = LEX_TOKEN_TYPE_ALIGNAS;
					}
					else if (!strcmp(lex_token.buf+2, "lignof"))
					{
						lex_token.type = LEX_TOKEN_TYPE_ALIGNOF;
					}
					else if (!strcmp(lex_token.buf+2, "tomic"))
					{
						lex_token.type = LEX_TOKEN_TYPE_ATOMIC;
					}
					break;
				case 'B':
					if (!strcmp(lex_token.buf+2, "itInt"))
					{
						lex_token.type = LEX_TOKEN_TYPE_BITINT;
					}
					else if (!strcmp(lex_token.buf+2, "ool"))
					{
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
				case 'I':
					if (!strcmp(lex_token.buf+2, "maginary"))
					{
						lex_token.type = LEX_TOKEN_TYPE_IMAGINARY;
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
						lex_token.type = LEX_TOKEN_TYPE_STATIC_ASSERT;
					}
					break;
				case 'T':
					if (!strcmp(lex_token.buf+2, "hread_local"))
					{
						lex_token.type = LEX_TOKEN_TYPE_THREAD_LOCAL;
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
				if (!strcmp(lex_token.buf+1, "loat"))
				{
					lex_token.type = LEX_TOKEN_TYPE_FLOAT;
				}
				else if (!strcmp(lex_token.buf+1, "or"))
				{
					lex_token.type = LEX_TOKEN_TYPE_FOR;
				}
				else if (!strcmp(lex_token.buf+1, "alse"))
				{
					lex_token.type = LEX_TOKEN_TYPE_FALSE;
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
				else if (!strcmp(lex_token.buf+1, "rue"))
				{
					lex_token.type = LEX_TOKEN_TYPE_TRUE;
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
			case 'n':
				if (!strcmp(lex_token.buf+1, "ullptr"))
				{
					lex_token.type = LEX_TOKEN_TYPE_NULLPTR;
				}
				break;
			}
			break;
		}

		if (isdigit(c))
		{
			lex_token.type = LEX_TOKEN_TYPE_LITERAL_INTEGER;
		_number:
			while (isalnum(c) || c == '.' || c == '\'' || c == '_')
			{
				if (c == '.')
				{
					lex_token.type = LEX_TOKEN_TYPE_LITERAL_FLOAT;
				}

				c = _getc();
			}
			_ungetc(c);
			break;
		}

		lex_token.type = LEX_TOKEN_TYPE_UNKNOWN;
		break;
	}
}
