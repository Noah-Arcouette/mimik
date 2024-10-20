#include <stdlib.h>
#include <stdio.h>
#include "defs.h"

void yylex_destroy (void); // lexer clean up, not portable but who cares

// free all data structures
void
freeAll (void)
{
	yylex_destroy(); // clean up lexer

	struct section *nextSection;
	currentSection = firstSection;
	while (currentSection)
	{
		nextSection = currentSection->next;

		// free symbols
		struct symbol *nextSymbol;
		struct symbol *currentSymbol = currentSection->firstSymbol;
		while (currentSymbol)
		{
			nextSymbol = currentSymbol->next;

			// free it
			if (currentSymbol->name)
			{
				free(currentSymbol->name);
			}
			free(currentSymbol);

			currentSymbol = nextSymbol;
		}

		// free gaps, and print them
		struct gap *currentGap = currentSection->firstGap;
		struct gap *nextGap;
		while (currentGap)
		{
			// free them and move onto the next
			nextGap = currentGap->next;
			if (currentGap->name)
			{
				free(currentGap->name);
			}
			free(currentGap);
			currentGap = nextGap;
		}

		// free data
		if (currentSection->stream)
		{
			fclose(currentSection->stream); // close output stream
			if (currentSection->buffer)
			{
				free(currentSection->buffer);
			}
		}
		if (currentSection->name)
		{
			free(currentSection->name);
		}
		free(currentSection);

		currentSection = nextSection; // next section
	}

	if (fout)
	{
		fclose(fout);
	}
}
