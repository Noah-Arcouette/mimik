#include "unreal.h"
#include "globs.h"

unsigned int column = 0;
unsigned int row    = 0;

void
putc (char character, unsigned char color)
{
	// restrict to buffer size, user may change these improperly so be aware
	row    = row % rows;
	column = column % columns;

	switch (character)
	{
	case '\n':
		row++;
	case '\r':
		column = 0;
		return;
	}

	videoMemory[(row*columns+column)*2+0] = character;
	videoMemory[(row*columns+column)*2+1] = color;

	// move to next line
	column++;
	if (column >= columns){
		column = 0;
		row++;
	}
}
