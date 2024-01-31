# Mimik System Tree

Mimik System Tree, or Mimik for short, is an implementation of a POSIX-Like operating system, as well as many other free to use data. All under the same license and with the same goal.

## Goal

The goal of Mimik is to provide a completely free, and open, collection of everything someone would have on their computer. All of this work is designed to be objective, easy to use, for the user, and conforming to open source ideals. Compatibility with existing standards will hold, but new Mimik created standards are preferred.


# Configuration

Mimik uses kconfig, usually called kconfig-frontends on linux distributions. Use this to generate a `.config` file. Also do not forget to add `*.config*` to your global git-ignore since all ignore files are auto generated in Mimik.


# Building

Mimik uses [Tup](gittup.org/tup), so make sure you have it installed. To build Mimik us the provided script.

`$ ./scripts/build.sh`


# Distribution Tree Organization

```
/boot/ ; Work required for the boot-loader to function, kernel may or may not be here
/bin/ ; Executable binaries required for the system to come up
/sbin/ ; Same as the above /bin/, but requires root privileges
	init ; The initial system, the first process started after the kernel is up
/lib/ ; Libraries required for the system to come up
/lib<arch>/ ; Same as the above /lib/, but for multi-architecture systems
/usr/ ; Work not required for the system to come up
	bin/ ; Executable binaries shipped with the distribution
	sbin/ ; Same as the above bin, but requires root privileges
	lib/ ; Libraries shipped with the distribution
	lib<arch> /; Same as the above lib, but for multi-architecture systems
	libexec/ ; Binaries designed to be ran by other programs, not users
	include/ ; System include files
	src/<project>/ ; System source code files
	config/<project>/ ; System build time configuration files
	share/ ; Architecture independent work
		locale/<locale>/ ; Locale selectable work
			man/ ; Manual pages
				man1/ ; Utilities
				man2/ ; ABIs
				man3/ ; Library APIs
				man4/ ; Special files / Device files
				man5/ ; File formats and conventions
				man6/ ; Games and screensavers
				man7/ ; Miscellanea
				man8/ ; System administrative utilities
			manp/ ; POSIX manual pages
				; same structure as the above man directory
			messages/<application>.cat ; Message catalogues
			licenses/<project>/... ; Licensing and project information
		test/<application>/<function> ; Unit tests, as scripts
	test/<application>/<function> ; Unit tests, as binaries
/etc/ ; System-wide configuration
	opt/ ; System-wide configuration for optional packages
	skel/ ; The base for a new user's /home/
/var/ ; Variable sized data
	opt/ ; Variable sized data for optional packages
	log/ ; Application log files
/opt/ ; Same structure as /usr/, but for optional, installed, packages
/home/<user>/ ; User data
/root/ ; Same structure as the above /home/<user>/, but for the root user
/run/ ; Data about the system since it was booted
/sys/ ; System capability information
/proc/ ; Running process information
/dev/ ; Device files
/tmp/ ; Temporary data
/srv/ ; Served data
/mnt/ ; Mount points
```
