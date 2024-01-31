# Prologue

This manual is part of the Mimik System Tree, other implementations may differ. Some compatibility with existing standards may be met but to do not expect any.


# Name

stderr - The standard error stream, part of libc


# Synopsis

```C
#include <.h>

nl_catd catopen (const char *name, int flag);
```


# Description

*catopen* shall open a new catalogue descriptor for use in `catgets`. The catalogue name shall be *name*. If *flag* is set to `NL_CAT_LOCALE` then the environment variable `LC_MESSAGES` shall be used instead of the environment variable `LANG` for the current locale; *flag* of `0` shall use `LANG`.


# Environment Variables

## LANG, LC_MESSAGES

Lang, or LC_MESSAGES, shall be used as the current locale for the message catalogue resolution. In the form of `<language>[_<dialect>][.<code-space>]`.

## NLSPATH

`NLSPATH` shall be a list of paths, delimited by `:`, to check for locale data. `NLSPATH` shall support the following, resolution replaced, variables:

### %N

Resolves to *name*

### %L

Resolves to the current locale

### %l

Resolves to the language section of current locale

### %t

Resolves to the dialect section of the current locale

### %c

Resolves to the code space section of the current locale

### %%

Resolves to a single `%` character


# Errors

`(nl_catd)-1` shall be returned on error.

For errno value see [fopen](fopen.3).


# Extended Description

There is no extended description.


# Future Directions

There are no future directions.


# Compliance

This function shall comply with:

The Open Group Base Specifications Issue 7, 2018 edition
IEEE Std 1003.1-2017 (Revision of IEEE Std 1003.1-2008)
Copyright (c) 2001-2018 IEEE and The Open Group


# See Also

[catclose](catclose.3) - Close message catalogue

[catgets](catgets.3) - Get message from catalogue
