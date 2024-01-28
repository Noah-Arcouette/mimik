#include <string.h>

void *
memchr (const void *s, int c, size_t n)
{
#ifdef RESILIENT
	if (!s)
	{
		return (void*)s;
	}
#endif

	do
	{
		if (*(unsigned char *)s++ == (unsigned char)c)
		{
			return (void *)s;
		}
	} while (n--);

	return (void*)NULL;
}
