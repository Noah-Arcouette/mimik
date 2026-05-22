**Not all discussed topics are fully implemented**

# Goals

 - Public domain
 - Compatible yet independent
 - Usable

## Public Domain

Any and all work is done under the BSD-Zero license, expressly to place the work
into the most Public Domain possible. Without license or copy right
restrictions.

## Compatible yet Independent

The Mimik system is happy to try new paradigms and create strange format, so
long as it does not hurt usefulness. Compatibility with other common unix-like
systems is important, but breaking the norms and fuzzing the lines of unix-like
are expressed greater. This is a public domain random system, use all you want
try all you want.

## Usable

The system is focused on access and experimentation but usability is also
important of course. Therefore, before submitting a pull request, please add at
least a basic utility or library manual -- hopefully accompanied with a guide.
Testing, specifically fuzzy testing, is not a must but is a best practice; the
configuration also uses [Valgrind](https://valgrind.org/) by default on all
tests and other invocations of built work.


# Building the System

1. Make sure you have [tup](https://gittup.org/tup/)
2. Make sure you have kconfig old-config aliased to `kconfig-conf`, and
	menu-config as `kconfig-mconf`
3. Run `./share/scripts/oldconfig` or `./share/scripts/menuconfig`. The defaults
	are there to quickly create a useful output without the minuet configuration
4. Run `tup init` then `tup` to build the system

***NOTE:*** Selecting `BUILD_HOST` in the configuration will limit the output,
as it builds a distribution for the current system using its compilers. Without
setting this, the system will cross-compile with its own compiler to the target
set -- optionally creating a bootible image. The built distribution is generally
a source based system with git, tup, and kconfig being the update mechanism.
