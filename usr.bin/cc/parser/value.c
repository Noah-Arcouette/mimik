#include "../defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./value/value.h"

int
value (size_t *var, struct type *type)
{
	return value_expr(var, type);
}
