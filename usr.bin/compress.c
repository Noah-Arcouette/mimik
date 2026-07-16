#include <libintl.h>
#include <locale.h>
#include <unistd.h>

const char *self;

int
main (int argc, char *argv[])
{
	textdomain("compress");
	setlocale(LC_ALL, "");
	self = argv[0];

	return 1;
}
