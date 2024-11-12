#include "../defs.h"

void
recover (void)
{
	while (token != SEMICOLON && token)
	{
		token = (enum token)yylex();
	}
	token = (enum token)yylex();
}
