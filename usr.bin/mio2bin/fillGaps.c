#include "main.h"
#include <libintl.h>
#include <endian.h>
#include <string.h>
#include <stdio.h>

void
fillGaps (void)
{
	for (long i = 0; i<gaps; i++)
	{
		struct MiO_Gap *g = &gap[i];

		int type = le16toh(g->type);

		int foundIt = 0;
		for (long j = 0; j<symbols; j++)
		{
			struct MiO_Symbol *s = &symbol[j];

			if (strncmp((char *)s->name, (char *)g->symbol, 256)) continue;

			long symbolValue = le64toh(s->value);

			foundIt = 1;

			// check if they're comptaible
			int flags = le16toh(s->flags);

			if (type & MIO_GAP_TYPE_EXECUTING)
			{
				if (!(flags & MIO_SYMBOL_FLAG_EXECUTABLE))
				{
					fprintf(stderr, gettext(
"%s: Refusing to fill executing gap with non-executable symbol `%.*s'\n"),
						self, 256, s->name);
					errors++;
				}
			}
			if (type & MIO_GAP_TYPE_READING)
			{
				if (!(flags & MIO_SYMBOL_FLAG_READABLE))
				{
					fprintf(stderr, gettext(
"%s: Refusing to fill executing gap with non-readable symbol `%.*s'\n"),
						self, 256, s->name);
					errors++;
				}
			}
			if (type & MIO_GAP_TYPE_WRITING)
			{
				if (!(flags & MIO_SYMBOL_FLAG_WRITABLE))
				{
					fprintf(stderr, gettext(
"%s: Refusing to fill executing gap with non-writable symbol `%.*s'\n"),
						self, 256, s->name);
					errors++;
				}
			}

			// check if the gap can be filled
			int offset = le64toh(g->offset);
			int size   = 0;
			switch (type & MIO_GAP_TYPE_MASK)
			{
			case MIO_GAP_TYPE_LIT_BYTE:
			case MIO_GAP_TYPE_DISP_BYTE:
				size = 1;
				break;
			case MIO_GAP_TYPE_LIT_LE16:
			case MIO_GAP_TYPE_LIT_BE16:
			case MIO_GAP_TYPE_DISP_LE16:
			case MIO_GAP_TYPE_DISP_BE16:
				size = 2;
				break;
			case MIO_GAP_TYPE_LIT_LE32:
			case MIO_GAP_TYPE_LIT_BE32:
			case MIO_GAP_TYPE_DISP_LE32:
			case MIO_GAP_TYPE_DISP_BE32:
				size = 4;
				break;
			case MIO_GAP_TYPE_LIT_LE64:
			case MIO_GAP_TYPE_LIT_BE64:
			case MIO_GAP_TYPE_DISP_LE64:
			case MIO_GAP_TYPE_DISP_BE64:
				size = 8;
				break;
			case MIO_GAP_TYPE_LIT_LE128:
			case MIO_GAP_TYPE_LIT_BE128:
			case MIO_GAP_TYPE_DISP_LE128:
			case MIO_GAP_TYPE_DISP_BE128:
				size = 16;
				break;
			default:
				fprintf(stderr, gettext("%s: Unknown gap type %03x\n"),
					self, type&MIO_GAP_TYPE_MASK);
				errors++;
				break;
			}

			if (!size) continue; // unknown gap

			if ((offset+size) >= bufsz)
			{
				fprintf(stderr, gettext("%s: Gap offset out of file bounds\n"),
					self);
				errors++;
				continue;
			}

			// fill the gap
			switch (type & MIO_GAP_TYPE_MASK)
			{
			case MIO_GAP_TYPE_DISP_BYTE:
				symbolValue = offset - symbolValue;
			case MIO_GAP_TYPE_LIT_BYTE:
				buf[offset] = symbolValue&0xff;
				break;
			case MIO_GAP_TYPE_DISP_LE16:
				symbolValue = offset - symbolValue;
			case MIO_GAP_TYPE_LIT_LE16:
				buf[offset  ] = symbolValue&0xff;
				buf[offset+1] = (symbolValue>>8)&0xff;
				break;
			case MIO_GAP_TYPE_DISP_LE32:
				symbolValue = offset - symbolValue;
			case MIO_GAP_TYPE_LIT_LE32:
				buf[offset  ] = symbolValue&0xff;
				buf[offset+1] = (symbolValue>>8 )&0xff;
				buf[offset+2] = (symbolValue>>16)&0xff;
				buf[offset+3] = (symbolValue>>24)&0xff;
				break;
			case MIO_GAP_TYPE_DISP_LE64:
				symbolValue = offset - symbolValue;
			case MIO_GAP_TYPE_LIT_LE64:
				buf[offset  ] = symbolValue&0xff;
				buf[offset+1] = (symbolValue>>8 )&0xff;
				buf[offset+2] = (symbolValue>>16)&0xff;
				buf[offset+3] = (symbolValue>>24)&0xff;
				buf[offset+4] = (symbolValue>>32)&0xff;
				buf[offset+5] = (symbolValue>>40)&0xff;
				buf[offset+6] = (symbolValue>>48)&0xff;
				buf[offset+7] = (symbolValue>>56)&0xff;
				break;
			case MIO_GAP_TYPE_DISP_LE128:
				symbolValue = offset - symbolValue;
			case MIO_GAP_TYPE_LIT_LE128:
				buf[offset   ] = symbolValue&0xff;
				buf[offset+ 1] = (symbolValue>>8  )&0xff;
				buf[offset+ 2] = (symbolValue>>16 )&0xff;
				buf[offset+ 3] = (symbolValue>>24 )&0xff;
				buf[offset+ 4] = (symbolValue>>32 )&0xff;
				buf[offset+ 5] = (symbolValue>>40 )&0xff;
				buf[offset+ 6] = (symbolValue>>48 )&0xff;
				buf[offset+ 7] = (symbolValue>>56 )&0xff;
				buf[offset+ 8] = 0;
				buf[offset+ 9] = 0;
				buf[offset+10] = 0;
				buf[offset+11] = 0;
				buf[offset+12] = 0;
				buf[offset+13] = 0;
				buf[offset+14] = 0;
				buf[offset+15] = 0;
				break;
			case MIO_GAP_TYPE_DISP_BE16:
				symbolValue = offset - symbolValue;
			case MIO_GAP_TYPE_LIT_BE16:
				buf[offset  ] = (symbolValue>>8)&0xff;
				buf[offset+1] = symbolValue&0xff;
				break;
			case MIO_GAP_TYPE_DISP_BE32:
				symbolValue = offset - symbolValue;
			case MIO_GAP_TYPE_LIT_BE32:
				buf[offset  ] = (symbolValue>>24)&0xff;
				buf[offset+1] = (symbolValue>>16)&0xff;
				buf[offset+2] = (symbolValue>>8 )&0xff;
				buf[offset+3] = symbolValue&0xff;
				break;
			case MIO_GAP_TYPE_DISP_BE64:
				symbolValue = offset - symbolValue;
			case MIO_GAP_TYPE_LIT_BE64:
				buf[offset  ] = (symbolValue>>56)&0xff;
				buf[offset+1] = (symbolValue>>48)&0xff;
				buf[offset+2] = (symbolValue>>40)&0xff;
				buf[offset+3] = (symbolValue>>32)&0xff;
				buf[offset+4] = (symbolValue>>24)&0xff;
				buf[offset+5] = (symbolValue>>16)&0xff;
				buf[offset+6] = (symbolValue>>8 )&0xff;
				buf[offset+7] = symbolValue&0xff;
				break;
			case MIO_GAP_TYPE_DISP_BE128:
				symbolValue = offset - symbolValue;
			case MIO_GAP_TYPE_LIT_BE128:
				buf[offset   ] = 0;
				buf[offset+ 1] = 0;
				buf[offset+ 2] = 0;
				buf[offset+ 3] = 0;
				buf[offset+ 4] = 0;
				buf[offset+ 5] = 0;
				buf[offset+ 6] = 0;
				buf[offset+ 7] = 0;
				buf[offset+ 8] = (symbolValue>>56 )&0xff;
				buf[offset+ 9] = (symbolValue>>48 )&0xff;
				buf[offset+10] = (symbolValue>>40 )&0xff;
				buf[offset+11] = (symbolValue>>32 )&0xff;
				buf[offset+12] = (symbolValue>>24 )&0xff;
				buf[offset+13] = (symbolValue>>16 )&0xff;
				buf[offset+14] = (symbolValue>>8  )&0xff;
				buf[offset+15] = symbolValue&0xff;
				break;
			}
			break;
		}

		if (!foundIt)
		{
			fprintf(stderr, gettext("%s: Unknown symbol `%.*s'\n"), self,
				256, g->symbol);
			errors++;
		}
	}
}
