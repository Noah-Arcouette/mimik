#include "../defs.h"

void
recover (void)
{
	// consume all until `}' or `;', or end of file
	while (token != SEMICOLON && token != RCURLY && token != TEOF)
	{
		token = (enum token)yylex();
	}
	token = (enum token)yylex();
}
