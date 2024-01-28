#include <string.h>
#include <stdio.h>

#define TITLE(x) printf("libc/%s %d: ", __FILE__, __LINE__)

int
main (void)
{
	int err = 0;
	char buff[256];
	char *x = strcpy(buff, "TEST!");
	if (strcmp(buff, "TEST!"))
	{
		TITLE();
		puts("Does not copy to empty dst");
		err = 1;
	}
	if (x != buff)
	{
		TITLE();
		puts("Does not return dst on empty dst");
		err = 1;
	}

	x = strcpy(buff, "TEST2!");
	if (strcmp(buff, "TEST2!"))
	{
		TITLE();
		puts("Does not copy to dst");
		err = 1;
	}
	if (x != buff)
	{
		TITLE();
		puts("Does not return dst\n");
		err = 1;
	}

	x = strcpy(buff, "");
	if (strcmp(buff, ""))
	{
		TITLE();
		puts("Does not clear src on empty dst");
		err = 1;
	}
	if (x != buff)
	{
		TITLE();
		puts("Does not return dst on empty src");
		err = 1;
	}

	if (!err)
	{
		TITLE();
		puts("\tConsistent");
	}
	else
	{
		TITLE();
		puts("\tInconsistent!");
	}
	return err;
}
