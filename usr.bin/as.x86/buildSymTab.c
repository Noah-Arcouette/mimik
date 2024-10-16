#include "defs.h"
#include <mio.h>
#include <string.h>
#include <stdio.h>
#include <endian.h>
#include <errno.h>
#include <stdlib.h>

void
buildSymbolTable (void)
{
	// build symbol table
	enterSection(MIO_SYMLIST_NAME, ""); // enter section

	// mio structures
	struct MiO_SymList sym;
	// offsets
	size_t bssOff  = 0;
	size_t dataOff = 0;
	// for each section
	struct section *csect = firstSection;
	struct symbol  *csym;
	while (csect)
	{
		// for each symbol
		csym = csect->firstSymbol;
		while (csym)
		{
			// compile into mio structure
			sym.flags = csym->flags;
			// copy name over
			strncpy((char *)sym.name, csym->name, sizeof(sym.name)); // doesn't need to be terminated if all bytes are used

			// write size
			size_t x = htole64(csym->size);
			memcpy(sym.size, &x, sizeof(size_t));

			// write possition
			x = csym->val;

			// address?
			if ((csym->flags&MIO_SYMLIST_TYPE_MASK) == MIO_SYMLIST_TYPE_ADDRESS)
			{
				x += dataOff; // add current offset
			}

			// bss address?
			if ((csym->flags&MIO_SYMLIST_TYPE_MASK) == MIO_SYMLIST_TYPE_BSS)
			{
				x += bssOff; // add current offset
			}

			// write to structure
			x = htole64(x);
			memcpy(sym.val, &x, 8);

			// write, whole structure, into section
			if (fwrite(&sym, sizeof(struct MiO_SymList), 1, currentSection->stream) != 1)
			{
				// writting error
				int errnum = errno;
				fprintf(stderr, "%s: Failed to write to buffer.\n", self);
				fprintf(stderr, "Error %d: %s.\n", errnum, strerror(errnum));
				exit(1);
			}

			csym = csym->next; // next symbol
		}

		// update offsets
		bssOff  += csect->bssz;
		dataOff += ftell(csect->stream);

		csect = csect->next; // next section
	}
}
