# Mimik

The public domain self sufficient system project.
Create a fully usable, in as many ways as possible, operating system in the public domain.
Overly ambitious, creating everything you can see on an operating system while staying as much in the public domain as possible.
Choose innovation over standards. Compatibility with common standards will be kept in a good amount but new formats and interfaces will be created basically everyway for the purpose of full public domain and free roam to explore.

# Warning

This is not even close to any thing close to any thing. This is just the beginnings of the toolchain and boot loader and some sparse notes and ideas. Please be patient, things should come in time.

# License

There are three main public domain licenses all are flawed in some way. CC0: Maintain patents and trademarks. Unlicense: Worded and structured poorly. WTFPL: Is more of a joke than a license. So I created my own public domain license. All authors' copyrights and liabilities are removed from the source, and the source is put into the public domain.

# Prerequisites

 - `c17`/as compiler (may be shifted to c99, and assembly compatibility may be removed, after the compiler is implemented)
 - gnu compatible `ld` (may be removed in the future)
 - `ar`
 - `yacc` (byacc is recommended, may be removed in the future)
 - `lex` (may be removed in the future)
 - `tup` (may be boot strapped and removed in the future)
 - `kconfig-frontends` (same note as tup)

# Configuring

Defaults: `yes "" | ./oldconfig`

Question Config: `./oldconfig`

Menu Config: `./menuconfig`

# Building

`tup`

or for the VM:

 - create a bochs 1.44M floppy compatibly disk file
 - add a bootable MBR partition at sector `33`
 - run `sh ./build.sh`
   - requires `dd` and `tar`, and `bochs`
