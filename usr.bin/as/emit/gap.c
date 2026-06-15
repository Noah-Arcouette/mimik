#include "../emit.h"

void
emitGap (const char *symbol, int type)
{
	// create the new gap
	// fill in data

	// emit zeros data
	int size = 0;
	switch (type)
	{
	case MIO_GAP_TYPE_LIT_BYTE:
	case MIO_GAP_TYPE_DISP_BYTE:
		size = 1;
		break;
	case MIO_GAP_TYPE_LIT_LE16:
	case MIO_GAP_TYPE_LIT_BE16:
	case MIO_GAP_TYPE_DISP_BE16:
	case MIO_GAP_TYPE_DISP_LE16:
		size = 2;
		break;
	case MIO_GAP_TYPE_LIT_LE32:
	case MIO_GAP_TYPE_LIT_BE32:
	case MIO_GAP_TYPE_DISP_LE32:
	case MIO_GAP_TYPE_DISP_BE32:
		size = 4;
		break;
	case MIO_GAP_TYPE_LIT_LE64:
	case MIO_GAP_TYPE_DISP_BE64:
	case MIO_GAP_TYPE_DISP_LE64:
	case MIO_GAP_TYPE_LIT_BE64:
		size = 8;
		break;
	case MIO_GAP_TYPE_LIT_LE128:
	case MIO_GAP_TYPE_DISP_BE128:
	case MIO_GAP_TYPE_DISP_LE128:
	case MIO_GAP_TYPE_LIT_BE128:
		size = 16;
		break;
	}

	char zeros[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	emit(zeros, size);
}
