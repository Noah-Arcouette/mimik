#include "../defs.h"

void
recover (void)
{
	// consume all until `}' or `;'
	while (token != SEMICOLON && token != RCURLY && token)
	{
		token = (enum token)yylex();
	}
	token = (enum token)yylex();
}
