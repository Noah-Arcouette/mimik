#include <string.h>
#include <stdio.h>

#define TITLE(x) printf("libc/%s %d: ", __FILE__, __LINE__)

int
main (void)
{
	int err = 0;
	char buff[256];
	char *x = stpncpy(buff, "TEST!", 6);
	if (strcmp(buff, "TEST!"))
	{
		TITLE();
		puts("Does not copy to empty dst");
		err = 1;
	}
	if (x != buff+5)
	{
		TITLE();
		puts("Does not return end of dst on empty dst");
		err = 1;
	}

	x = stpncpy(buff, "TEST2!", 7);
	if (strcmp(buff, "TEST2!"))
	{
		TITLE();
		puts("Does not copy to dst");
		err = 1;
	}
	if (x != buff+6)
	{
		TITLE();
		puts("Does not return end of dst");
		err = 1;
	}

	x = stpncpy(buff, "", 1);
	if (strcmp(buff, ""))
	{
		TITLE();
		puts("Does not clear src on empty dst");
		err = 1;
	}
	if (x != buff+0)
	{
		TITLE();
		puts("Does not return end of dst on empty src");
		err = 1;
	}

	strcpy(buff, "xxx");
	x = stpncpy(buff, "yy", 1);
	if (strcmp(buff, "yxx"))
	{
		TITLE();
		puts("Fixed sized src does not copy properly");
		err = 1;
	}
	if (x != buff+1) 
	{
		TITLE();
		puts("Does not return end of dst on fixed sized src");
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
