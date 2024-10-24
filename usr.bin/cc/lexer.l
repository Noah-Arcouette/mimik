%{

#include "y.tab.h"
#include "defs.h"

int lineno = 1;

%}

%%

%%

int
yywrap (void)
{
	return 1;
}

