#include <string.h>

char *
strcat (char *restrict s1, const char *restrict s2)
{
	stpcpy(s1+strlen(s1), s2);
	return s1;
}

char *
strncat (char *restrict s1, const char *restrict s2, size_t n)
{
	stpncpy(s1+strlen(s1), s2, n);
	return s1;
}
