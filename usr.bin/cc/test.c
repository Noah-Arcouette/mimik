
extern int  yyparse       (void);
extern void yylex_destroy (void);

      int   errors = 0;
const char *self   = "usr.bin/cc";

const char *filename = "<stdin>";

struct test
{
	union {
		int a;
		int b[10];
	}
	const void **x[100];
};

int
main (int argc, char *const *argv)
{
	if (argc > 0)
	{
		self = argv[0];
	}

	yyparse();

	yylex_destroy();

	return errors;
}
