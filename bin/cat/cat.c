#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <nl_types.h>

#define FLAG_PARSING  0b001
#define FLAG_ERROR    0b010
#define FLAG_NO_FILES 0b100

#define DEFAULT_SELF "/bin/cat"
#define UNKNOWN_OPTION "%s: Unknown option `-%c'\n" // 1:1
#define CANNOT_OPEN    "%s: Cannot open file `%s' for reading, errno %d: %s\n" // 1:2
#define CAT_ERROR      "%s: Cannot open current locale message catalogue, errno %d: %s\n"

#ifndef BUFF_SIZE
#	warning "/bin/cat: BUFF_SIZE not given, defaulting to 4096"
#	define BUFF_SIZE 4096
#endif

int
main (const int argc, const char **argv)
{
#ifdef RESILIENT
	const char *self = DEFAULT_SELF;
	if (argc > 0)
	{
		self = argv[0];
	}
#else
	const char *self = argv[0];
#endif

	FILE *fp;

	unsigned char buff[BUFF_SIZE]; // the read/write buffer
	size_t buffSize	 = BUFF_SIZE;

	size_t read;

	// Don't use LC_MESSAGES because it's implementation is very weird on most platforms
	nl_catd catd = catopen("cat", 0);
	if (catd == (nl_catd)-1)
	{
		fprintf(stderr, CAT_ERROR, self, errno, strerror(errno));
	}

	int j;
	unsigned char flags = FLAG_PARSING | FLAG_NO_FILES;
	for (int i = 1; i<argc; i++)
	{
		if (
			(flags & FLAG_PARSING) &&
			(argv[i][0] == '-') &&
			argv[i][1]
		)
		{
			for (j = 1; argv[i][j]; j++)
			{
				switch (argv[i][j])
				{
					case 'u': // -u : non-buffering i/o, read byte by byte
						buffSize = 1; // set i/o buffer size to 1
						setbuf(stdin,  (char*)NULL); // disable buffering
						setbuf(stdout, (char*)NULL);
						break;
					case '-': // -- : parsing stop
						flags &= ~FLAG_PARSING;
						break;
					default:
						flags |= FLAG_ERROR;
						fprintf(stderr, catgets(catd, 1, 1, UNKNOWN_OPTION), self, argv[i][j]);
						break;
				}
			}
			continue;
		}

		// files have been given
		if (flags &	  FLAG_NO_FILES)
			flags &= ~FLAG_NO_FILES;

		// check if not stdin
		if (strcmp(argv[i], "-")) 
		{
			fp = fopen(argv[i], "r"); // open for reading

			if (!fp) // check if opened successfully
			{
				flags |= FLAG_ERROR;

				fprintf(stderr, catgets(catd, 1, 2, CANNOT_OPEN), self, argv[i], errno, strerror(errno));
				continue;
			}
		}
		else // stdin is used
		{
			fp = stdin;
		}

		// output file
		do
		{
			// fill buffer with file
			read = fread(buff, sizeof(unsigned char), buffSize, fp);

			// fill output with buffer
			fwrite(buff, sizeof(unsigned char), read, stdout);
		} while (read >= buffSize); // read should never be greater, but it's better to catch all possibilities

		// close if not stdin
		if (strcmp(argv[i], "-"))
		{
			fclose(fp);
		}
	}

	// no files given
	if (flags & FLAG_NO_FILES)
	{
		// output stdin
		do
		{
			// fill buffer with stdin
			read = fread(buff, sizeof(unsigned char), buffSize, stdin);

			// fill output with buffer
			fwrite(buff, sizeof(unsigned char), read, stdout);
		} while (read >= buffSize); // read should never be greater, but it's better to catch all possibilities
	}

	if (catd != (nl_catd)-1)
	{
		catclose(catd);
	}

	return (flags & FLAG_ERROR);
}
