
extern const unsigned long long int *restrict *const hi;
extern int h (int lo, int, const char **argv, const unsigned short hoi);

extern int numbro;

extern int test (int);

int
h (int lo, int x, const char **argv, const unsigned short hoi)
{
	int y;
	y = x+100*2;
	x = 10-100+20+y;

	return 1*(2+3*(x=1))-numbro;
	return y;
}

int
test (int i)
{
	int j = 10;
	return i+j;
	j = 10+23+j;
}

int
vib (int j, int i)
{
	int x = test(i);
	return vib(i, test(j)+x);
}

void
contexts (void)
{
	int x = 10;
	{
		int y = 5;
		x = 100;
	}
	int y = x+10;

	if (x-10*2)
		if (y) x = 1000;
		else if (y+1) x = 1;
		else x = 1;
}

void
loops ()
{
	int i = 255;
	while (i)
	{
		if (i*100)
		{
			i = 100;
			return;
		}
		else
		{
			break;
		}

		i = i - 1;

		if (i+2)
		{
			continue;
		}
	}
}

extern void arrays (int [10]);

void
arrays (int x[10])
{
	int *y[5][5];
}
