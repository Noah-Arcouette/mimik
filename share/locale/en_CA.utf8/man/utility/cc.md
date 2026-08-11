# Name

cc -- The C compiler


# Synopsys

```sh
$ cc [*options*] [*files*]
```


# Description

*cc* shall take the input files given and apply a select amount of compilation.
*options* may be interspersed with *files* and all options shall take place
before any level of compilation on the given files takes place.


# Options

**-Bdynamic**
	Attempt to link to the most dynamic libraries as possible. This is the
	default mode.

**-Bstatic**
	Attempt to link to the most static libraries as possible.

**-Bonly-static**
	Only link to static libraries, failing if not possible.

**-c**
	Produce object files from the given files. The output files shall be in the
	format `*basename*.o`. Do not apply linking.

**-Dname[=value]**
	Create a macro of the given name, and optionally the given value. See
	**Extended Description -- Intrinsic Macros**.

**-E**
	Only execute the pre-processor on the given C files. Using standard output
	as the default output file, unless otherwise set.

**-ffreestanding**
	Enable free standing mode, do not include or link anything unless specified.
	No default include paths shall be present. No default libraries shall be
	present, nor library search paths. And no C-library specific optimizations
	shall take place.

**-G**
	Produce a shared library. If combined with **-c**, the **-c** option shall
	always take precedence. If **-c** is not given, then the **-o** option is
	required to be given and the specified file shall be a shared object.

**-g**
	Produce debugging information.

**-I path**
	Include the given path in the include and embed search paths before the
	default places. The paths shall be searched in the order given. The default
	paths are: `/usr/include/` and `/usr/local/include/`.

**-i**
	Produce IR files in the form `*basename*.ir` where possible.

**-L path**
	Include the given path in the library search list, before the default
	places. They shall be search in the order that they are given. The default
	paths are: `/lib/`, `/usr/lib/`, and `/usr/local/lib/`.

**-l library**
	Link the given -- by name -- library. The prefixed `lib` need not be
	present. By default the `libc` library shall be linked. See `library/*` for
	the specific include files and libraries to link.

**-m i8086**
	Produce an output for the i8086 CPU.

**-O opt|level**
	See **Extended Description -- Optimizations**.

**-o outfile**
	Set the output file, in mode where multiple output files are emitted they
	shall be concatenated together to produce an single output. The default
	output file -- unless other wise stated -- is `a.out`. May `-` for standard
	output.

**-R path**
	Include the given path in the loading search path before the regular places.
	They shall be searched in the order given. The defaults are the same as the
	**-L** option.

**-S**
	Produce assembler source output files, in the form `*basename*.s`, for each
	input that applies.

**-s**
	Pass `-O1` to the linker, stripping unnecessary information from the final
	output file.

**-U name**
	Disregard any initial definition of the given macro; this includes
	definitions within source material, command-line, or intrinsic macros.


# Operands

*file*
	See **Input Files**. `-` may be given to read from standard input.


# Environment Variables

*LANG*, *LC_ALL*, *LC_MESSAGES*, *NLSPATH*
	Control the locale message output.

*AS*
	The assembler to use, default `as`.

*LD*
	The linker to use, default `ld`.

*STRIP*
	The strip -- Post-Link-Optimization -- utility to execute, default `strip`.


# Standard Input

Used if a `-` is given as an input file.


# Input Files

Shall be one of the following:

*file*.c
	A C-source file.

*file*.i
	A C-source file with pre-processor directives executed.

*file*.ir
	An Intermediate Representation file.

*file*.s
	An assembler source file, which does not include pre-processor directives.

*file*.o
	An object file.

*file*.so
	A shared object to link, note: unless present in the loading search path
	the inclusion of a shared object file may cause the output to not load.

*file*.a
	A static library to link.


# Standard Output

Used if `-` is given as the output file.


# Output Files

Shall be one of the following:

*file*.i
	A C-source file with pre-processor directives executed.

*file*.ir
	An Intermediate Representation file.

*file*.s
	An assembler source file, which does not include pre-processor directives.

*file*.o
	An object file.

*file*.so
	A shared object file.

*file*
	An executable file.


# Standard Error

Use to print any diagnostic messages.


# Asynchronous Events

Default.


# Extended Description

## Optimizations

The following optimization are present:

All optimizations under `utility/strip`; `-Os` shall be passed as `-O2`, and
`-Oz` as `-O3`.


## Intrinsic Macros

**__FILE__**
	Shall always expand to a string constant of the current file name. `#line`
	may change this value.

**__LINE__**
	Shall always expand to a numerical constant of the current line number.
	`#line` may change this value.

**__DATE__**
	Shall always expand to a string constant of the current date of compilation;
	the output shall always be in the form described by the locale at the time
	of compilation.

**__TIME__**
	Shall always expand to a string constant of the current time of compilation;
	the output shall always be in the form described by the locale at compile
	time.

**__STDC__**
	Shall expand to `1`.

**__STDC_VERSION__**
	Shall expand to `202411L`.

**__STDC_HOSTED__**
	Shall expand to `1`, if **-ffreestanding** is not given.

**__mimik__**
	Shall expand to `1`.

**__x86_16__**
**__i8086__**
	Shall expand to `1` if **-m i8086** is provided or the default compilation
	machine is `i8086`.


# Exit Status

`>0`
	An error occurred.

`0`
	Successful.


# Consequences of Error

No output file shall be created upon error.


# Application Usage

This application is designed for use in Mimik and only produces MiO files from
Mimik source input files.


# Examples

None.


# Rationale

None.


# Future Directions

None.


# History

None.


# See Also

`format/c` -- The C input format

`format/s` -- The assembler input format

`format/mio` -- The MiO output format

[POSIX 2024](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/c17.html) -- The POSIX specification

[FreeBSD](https://man.freebsd.org/cgi/man.cgi?query=clang) -- The FreeBSD manual

[GNU](https://www.man7.org/linux/man-pages/man1/gcc.1.html) -- The GNU manual
