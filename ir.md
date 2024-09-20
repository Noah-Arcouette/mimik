
```C
extern int printf (ptr, ...)

self.0: .asciz "self"
fmt: .asciz "%s: %s\n"

global self: .ptr self.0

global function main:
	int argc = input.int 0
	ptr argv = input.ptr 1

	void = goto_le argc 0 next
	ptr t1 = load.ptr argv
	void = store.ptr self t1
next:

	int i.start = 1
	ptr t2.start = argv
for_start:
	int i = phi i.start i.new

	void = goto_ge argc i for_end

	ptr t2 = phi t2.start t2.new
	void = printf fmt self t2

	ptr t2.new = add.ptr t2 sizeof(ptr)

	int i.new = add.int i 1
	void = goto for_start
for_end:
	void = return.int 0
```


```C
extern int printf (const char *restrict fmt, ...);

const char *self = "self";

int
main (int argc, const char *argv)
{
	if (argc > 0)
	{
		self = argv[0];
	}

	for (int i = 1; i<argc; i++)
	{
		printf("%s: %s\n", self, argv[i]);
	}

	return 0;
}
```
