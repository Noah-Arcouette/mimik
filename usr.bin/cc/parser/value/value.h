#ifndef __VALUE_H__
#define __VALUE_H__
#include <stddef.h>
#include "../../defs.h"

extern int value_value (size_t *delta, struct type *typeData); // immediate | symbol | function-call
extern int value_term  (size_t *delta, struct type *type); // value *,/,% value | value
extern int value_expr  (size_t *delta, struct type *type); // term  +,-   term  | term

#endif
