#include <stdio.h>

int
main (const int argc, const char **argv)
{
	int c;
	for (int i = 1; i<argc; i++)
	{
		if (i > 1)
			printf(" ");

		for (int j = 0; argv[i][j]; j++)
		{
			if (argv[i][j] == '\\')
			{
				j++;

				switch (argv[i][j])
				{
					case 'a':
						printf("\a");
						break;
					case 'b':
						printf("\b");
						break;
					case 'c':
						goto end;
					case 'f':
						printf("\f");
						break;
					case 'n':
						printf("\n");
						break;
					case 'r':
						printf("\r");
						break;
					case 't':
						printf("\t");
						break;
					case 'v':
						printf("\v");
						break;
					case '\\':
						printf("\\");
						break;
					case '0':
						c = 0;
						while (argv[i][j+1] >= '0' && argv[i][j+1] <= '7')
						{
							if (((c << 3) + 7) > 0xff)
							{
								break;
							}

							j++;
							c <<= 3;
							c  += argv[i][j] - '0';
						}

						printf("%c", (char)c);
						break;
					default:
						printf("\\%c", argv[i][j]);
						break;
				}
				continue;
			}

			printf("%c", argv[i][j]);
		}
	}

	printf("\n");

	end:

	return 0;
}
