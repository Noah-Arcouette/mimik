#include <string.h>

int
strcmp (const char *s1, const char *s2)
{
#ifdef RESILIENT
	if (!s1 && !s2)
	{
		return 0;
	}
	if (!s1)
	{
		return -1;
	}
	if (!s2)
	{
		return 1;
	}
#endif

	while (*s1 == *s2)
	{
		if (!*s1)
		{
			return 0;
		}

		s1++;
		s2++;
	}
	
	return *s1 - *s2;
}
