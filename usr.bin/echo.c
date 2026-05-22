#include <string.h>
#include <locale.h>
#include <stdio.h>
#include <ctype.h>

int
main (int argc, char *argv[])
{
	setlocale(LC_ALL, "");

	int finalnewline = 1;

	for (int i = 1; i<argc; i++)
	{
		char *s = argv[i];
		while (*s)
		{
			switch (*s)
			{
			case '\\':
				s++;
				switch (*s)
				{
				case 'a':
					putchar('\a');
					break;
				case 'b':
					putchar('\b');
					break;
				case 'c':
					finalnewline = 0;
					break;
				case 'f':
					putchar('\f');
					break;
				case 'n':
					putchar('\n');
					break;
				case 'r':
					putchar('\r');
					break;
				case 't':
					putchar('\t');
					break;
				case 'v':
					putchar('\v');
					break;
				case '\\':
					putchar('\\');
					break;
				case '0':
					s++;
					int val = 0;

					while (*s >= '0' && *s <= '7')
					{
						val *= 8;
						val += *s - '0';
						s++;
					}
					s--;

					putchar(val);
					break;
				default:
					putchar('\\');
					putchar(*s);
					break;
				}
				break;
			default:
				putchar(*s);
				break;
			}
			s++;
		}
	}

	if (finalnewline) putchar('\n');

	return 0;
}
