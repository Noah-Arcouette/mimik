
int
strncmp (const char *restrict s1, const char *restrict s2, unsigned int n)
{
	while (1)
	{
		// all equal up to that point
		if (!n)
		{
			return 0;
		}

		if (*s1 == *s2)
		{
			if (*s1 == '\0')
			{
				return 0;
			}

			s1++;
			s2++;
		}
		else if (*s1 > *s2)
		{
			return 1;
		}
		else if (*s1 < *s2)
		{
			return -1;
		}

		n--;
	}
}
