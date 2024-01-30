#include <stdio.h>
#include <string.h>
#include <stdarg.h>

static int 
__vfprint_int(FILE *file, int num)
{
	if (num < 10)
	{
		if (fputc(num + '0', file) == EOF)
		{
			return 1;
		}
	}
	else
	{
		if (__vfprint_int(file, num/10))
		{
			return 1;
		}

		if (fputc((num%10)+'0', file) == EOF)
		{
			return 1;
		}
	}
	return 0;
}

int
vfprintf (FILE *restrict file, const char *restrict fmt, va_list ap)
{
	va_list vargs;
	va_copy(vargs, ap);

	// int cont;
	while (*fmt)
	{
		if (*fmt == '%')
		{
			// cont = 1;
			// while (cont)
			// {
				fmt++;
				switch (*fmt)
				{
					case 's':
						const char *str = va_arg(vargs, const char *);

						size_t len = strlen(str);
						if (fwrite(str, len, 1, file) != len)
						{
							return 1;
						}
						// cont = 0;
						break;
					case 'c':
						int chr = va_arg(vargs, int);

						if (fputc(chr, file) == EOF)
						{
							return 1;
						}
						// cont = 0;
						break;
					case 'd':
						int num = va_arg(vargs, int);

						if (num < 0)
						{
							if (fputc('-', file) == EOF)
							{
								return 1;
							}
							num *= -1;
						}

						if (__vfprint_int(file, num) == EOF)
						{
							return 1;
						}

						// cont = 0;
						break;
					default:
						if (fputc('%', file) == EOF)
						{
							return 1;
						}
						// cont = 0;
						break;
				}
			// }
		}
		else
		{
			fputc(*fmt, file);
		}

		fmt++;
	}
	va_end(vargs);

	return 0;
}
