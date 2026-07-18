# Name

compress -- Generic data compression utility


# Synopsys

```sh
$ compress [-fkv] [-b value] [-g | -m algo] [-p threads] [file...]

$ compress -c [-fkv] [-b value] [-g | -m algo] [-p threads] [file]

$ compress -d [-cfkv] [-p threads] [file...]
```


# Description

*compress* shall attempt to compress the given files using the default, or the
supplied, compression algorithm. If **-d** is given then compress shall
restore the files to the original state, using the detected or supplied
compression algorithm.

If no files are given then standard input shall be used as input file.

For each input file being compressed, a like-named file with the appropriate
suffix appended shall be created. And if successful compression takes place,
the original file shall be deleted.

For each input file being decompressed, a like-named file with the appropriate
suffix removed shall be created. And if successful decompression takes place,
the original file shall be deleted.

If no algorithm is provided, then compression shall use the default compression
algorithm, and decompression shall attempt to use file contents to detect the
format.


# Options

**-b value**
	For most formats, this shall set the relative compression level, and shall
	be between one and nine inclusive, with a default of six.

	Specifically for LZW compression, this shall be the maximum number of code
	bits to use, and shall be higher than eight with a default of sixteen. It is
	recommended not to set about sixteen for compatibility reasons.

**-c**
	Write to standard output, no input files shall be modified and no output
	files shall be created.

**-d**
	Decompress the given files, restoring them to their original state.
	Including, file mode, file ownership, file access and modification times,
	and file name.

**-f**
	Force compression or decompression even if: the compression results in a
	larger file, or the output file already exists. If **-f** is not given and
	stdin is a tty then the user shall be prompted whether or not to replace an
	existing file. If stdin is not a tty then *compress* shall write a
	diagnostic message and exit, not overwriting the file. If **-f** is not
	given and compression will result in a larger file then *compress* shall
	exit with a code of `2`.

**-g**
	Same as **-m gzip**.

**-k**
	Do not delete the given inputs files.

**-m algo**
	Set the algorithm of compression, this may include:

	+-----------------+----------+-----------------+
	|    Algorithm    |   Algo   | Filename Suffix |
	+-----------------+----------+-----------------+
	| Adaptive LZW    | lzw      | .Z              |
	| Deflate Stream  | deflate  | .deflate        |
	| GZip            | gzip     | .gz             |
	+-----------------+----------+-----------------+

	But also includes all file-based compressing formats supported by
	libzio.

**-p threads**
	Set the amount of threads to use to decompress or compress files.

**-v**
	Print diagnostic information about the compression or decompression ratio.


# Operands

*file*
	The pathname of a file to be compressed or decompressed. If *file* is `-`
	then standard input shall be used and standard output shall be used as the
	output file.


# Environment Variables

*LANG*, *LC_ALL*, *LC_MESSAGES*, *NLSPATH*
	Control the locale message output.


# Standard Input

Standard input shall be used as an input file if `-` is given. And be used, if
a tty, for user input.


# Input Files

Input files for compression may be of any format. Input files for decompression
shall be any file format supported by *compress*.


# Standard Output

Standard output shall be used if standard input is an input file, or if **-c**
is provided.


# Output Files

Output files for compression shall be of the provided format or the default
format. Output file for decompression shall be of any format.


# Standard Error

Shall be used for diagnostic messages and for prompt messages.


# Asynchronous Events

Default.


# Extended Description

None.


# Exit Status

`0`
	Success

`1`
	An error occurred

`2`
	One or more files were not compressed because they would have increased in
	size

`>2`
	An error occurred


# Consequences of Error

If an error occurs during compression or decompression the file which caused
the error shall be unchanged an *compress* shall exit at that point.


# Application Usage

None.


# Examples

None.


# Rationale

None.


# Future Directions

None.


# History

None.


# See Also

`library/libzio` -- The backing library

[POSIX 2024](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/compress.html) -- The POSIX specification

[FreeBSD](https://man.freebsd.org/cgi/man.cgi?query=compress) -- The FreeBSD manual
