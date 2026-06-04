# Name

This document may refer to multiple documents:

`.so` - binary shared object file


# Synopsis

`.so` - binary share object file. A file usually produced by the `ld` or `cc`
utility, that is not designed to be used alone but with other executable
binaries; almost always dynamically loaded in form. Common formats:
 - MiO - Mimik
 - ELF - Linux, Unix*, and BSD* systems
 - PE32+ - Windows
 - Macho - MacOS and other Darwin based systems


# Rationale

None.


# See Also

`utility/ld` -- The linker

`utility/cc` -- The C compiler

`format/mio` -- The Mimik Object format
