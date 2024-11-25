#ifndef __VALUE_H__
#define __VALUE_H__
#include <stddef.h>
#include "../../defs.h"

extern int value_value (size_t *delta, struct type *typeData);
extern int value_term  (size_t *delta, struct type *type);
extern int value_expr  (size_t *delta, struct type *type);

#endif
