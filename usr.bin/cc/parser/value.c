#include "../defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./value/value.h"

int
value (size_t *delta, struct type *type)
{
	return value_expr(delta, type);
}
