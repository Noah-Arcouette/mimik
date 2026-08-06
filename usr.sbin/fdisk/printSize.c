#include "main.h"
#include <libintl.h>
#include <stdio.h>

void
printSize (unsigned long _val)
{
	double val = (double)_val;

	// if divisible by 1024
	if (!(_val & 0x3ff))
	{
		// print 1024 type
		int ext = 0;
		val /= 1024; // its divisible by 1024, so we can divide it off the bat
		while (val >= 1024 && ext < 3)
		{
			val /= 1024;
			ext++;
		}

		switch (ext)
		{
		case 0:
			fprintf(stderr, gettext("%.2fKiB"), val);
			break;
		case 1:
			fprintf(stderr, gettext("%.2fMiB"), val);
			break;
		case 2:
			fprintf(stderr, gettext("%.2fGiB"), val);
			break;
		case 3:
			fprintf(stderr, gettext("%.2fTiB"), val);
			break;
		}
		return;
	}
	// else

	// print 1000 type
	int ext = 0;
	while (val >= 1000 && ext < 4)
	{
		val /= 1000;
		ext++;
	}

	switch (ext)
	{
	case 0:
		fprintf(stderr, gettext("%.2fB"), val);
		break;
	case 1:
		fprintf(stderr, gettext("%.2fKB"), val);
		break;
	case 2:
		fprintf(stderr, gettext("%.2fMB"), val);
		break;
	case 3:
		fprintf(stderr, gettext("%.2fGB"), val);
		break;
	case 4:
		fprintf(stderr, gettext("%.2fTB"), val);
		break;
	}
	return;
}
