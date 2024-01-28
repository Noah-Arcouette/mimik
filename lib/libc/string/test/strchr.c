#include <stdio.h>
#include <string.h>

#define TITLE(x) printf("libc/%s %d: ", __FILE__, __LINE__)

int
main (void)
{
	int err = 0;
	char *buff = "StringString";
	char *x = strchr(buff, 'S');
	if (!x)
	{
		TITLE();
		puts("Does not find first character match");
		err = 1;
	}
	else if (x != buff)
	{
		TITLE();
		puts("Mismatches on first character match");
		err = 1;
	}

	x = strchr(buff, (char)0);
	if (!x)
	{
		TITLE();
		puts("Does not find last character match");
		err = 1;
	}
	else if (x != buff+12)
	{
		TITLE();
		puts("Mismatches on last character match");
		err = 1;
	}

	x = strchr(buff, 'r');
	if (!x)
	{
		TITLE();
		puts("Does not find character");
		err = 1;
	}
	else if (x != buff+2)
	{
		TITLE();
		puts("Mismatches");
		err = 1;
	}

	x = strchr(buff, '=');
	if (x)
	{
		TITLE();
		puts("Matches on nothing");
		err = 1;
	}

	if (err)
	{
		TITLE();
		puts("\tInconsistent!");
	}
	else
	{
		TITLE();
		puts("\tConsistent");
	}
	return err;
}
