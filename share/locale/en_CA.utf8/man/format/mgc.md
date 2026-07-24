# Name

`.mgc` - A magic file test


# Synopsis

The magic file format is a list of file tests, in ascii text.


# Description

A magic file shall contain one of three line types:
 - empty line or white space
 - a comment line
 - a file test line
 - a response setter

## A comment line

A comment line shall begin with a `#`, and all following character shall be
ignored by the file parser.

## A file test line

A file test line shall have three entries separated by whitespace. The entries
being: *offset* *test* *value* *message*. (The *message* portion may not be
present)

*offset*
	An offset shall be a positive integer supported by `library/libc/strtol`.
	This offset shall be referencing an offset within the tested file. *offset*
	may be preceded by one or more `>`, this will cause the test to only run if
	the last test of one `>` shorter succeeded.

*type*
	Type shall specify the testing value type to be retrieved from the file. If
	the file is too short to retrieve the type then the test shall fail.

	The following type may be preceded by a `u` to signify unsignedness. And may
	be suffixed with `&` then a positive integer to signify a bit mask:
	 - byte -- A single byte integer

	The following types may be preceded by a `u` to signify unsignedness, and
	`le` or `be` to signify little endian and big endian respectively. And may
	be suffixed with `&` then a positive integer to signify a bit mask:
	 - short -- A two byte integer
	 - long -- A four byte integer
	 - quad -- An eight byte integer

	The following types may be preceded by `le` or `be` to signify little endian and big endian respectively. And may be suffixed with `&` then a positive
	integer to signify a bit mask:
	 - float -- A four byte floating point
	 - double -- An eight byte floating point

	The following types are also supported:
	 - string -- A given string to match, not including a null terminator
	 - regex -- A given regex pattern to run on the file

	The following types are provided for compatibility, they may be suffixed
	with a positive integer to delimit size, or suffixed with `C` to represent
	`1`, `S` to represent `2`, `I` to represent `4`, or `L` to represent `8`:
	 - d -- A signed integer
	 - u -- An unsigned integer
	 - f -- A floating point

	The following type is provided for compatibility:
	 - s -- A synonym for `string`

*value*
	For all types excluding `string` and `regex` this shall be one of the
	following, note *number* may also be a float where applicable and value
	refers to the value read from the input file:
	 - =*number* -- The test succeeds if the value is equal to *number*
	 - *number* -- Same as =*number*
	 - <*number* -- The test succeeds if the value is less than *number*
	 - >*number* -- The test succeeds if the value is greater than *number*
	 - &*number* -- The test succeeds if all of the set bits in *number* are set
	 in value
	 - ^*number* -- The test succeeds if at least one of the set bits in *number*
	 are not set in value
	 - x -- The test shall succeed if the file is large enough to contain the
	 *type* specified as the given *offset*

	If the type is `string`, then *value* shall be a set of characters to test
	for from the file at *offset*, the *value* may also include escape sequences
	as follows:
	 - `\\` -- a single back slash
	 - `\a` -- an alert character
	 - `\b` -- a backslash character
	 - `\f` -- a form-feed character
	 - `\n` -- a newline
	 - `\r` -- a character return
	 - `\t` -- a horizontal tab
	 - `\v` -- a vertical tab
	 - `\ ` -- a space character
	 - \*octal* -- an octal sequence
	 - \x*hex* -- a hex-code sequence

	If the type is `regex`, then *value* shall be treated the same as *string*
	but be passed to a regex test over the entire file instead of a verbatim
	test.

*message*
	Message shall be a printf compatible string with the first argument set to
	that of the value retrieved for the test. The message shall only be printed
	if the test succeeds.

## A response setter

Shall be one of the following:
 - `!:ext *extensions*` -- If the above command succeeds, *extensions* shall be
 the returned possible extensions -- delimited by a `/` -- for the file.
 - `!:mime *mime*` -- If the above command succeeds, *mime* shall be the
 returned possible mime type for the file.
 - `!:man *man*` -- If the above command succeeds, *man* shall be the returned
 possible manual page for the file.


# Rationale

This document is a subset of the *gnu* and *freebsd* magic file manual, and is
inline with -- I believe at least -- POSIX.


# Future Directions

Additional support for the rest of *gnu* and *freebsd* magic file format.


# Examples

```magic
0 string \037\235 LZW compressed data
>2 byte&0x80 >0     Block compression used
>2 byte&0x1f x      %d codeword bits
```


# History

None.


# See Also

`utility/file` -- The magic file parsing utility

[POSIX 2024](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/file.html) -- The POSIX specification

[FreeBSD](https://man.freebsd.org/cgi/man.cgi?query=magic&sektion=5) -- The FreeBSD manual

[GNU](https://www.man7.org/linux/man-pages/man4/magic.4.html) -- The GNU manual
