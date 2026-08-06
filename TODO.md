**Please remove things after completion**

# POSIX Utils

alias
ar
at
awk
basename
batch
bc
cd
chmod
cksum
cmp
comm
command
cp
crontab
csplit
cut
date
dd
df
diff
dirname
du
ed
env
expand
expr
file
find
fold
gencat
getconf
getopts
gettext
grep
hash
iconv
id
join
kill
ln
locale
localedef
logger
lp
ls
m4
mailx
mesg
mkdir
mkfifo
msgfmt
mv
newgrp
ngettext
nohup
od
paste
patch
pathchk
pax
pr
printf
ps
pwd
read
realpath
renice
rm
rmdir
sed
sh
sort
split
strings
stty
tabs
tail
test
timeout
touch
tput
tr
tsort
ulimit
umask
unalias
unexpand
uniq
wait
wc
who
write
xargs

strip:
	gc-static-symbols
	gc-empty-symbols
	gc-empty-sections
	gc-empty-maps
	gc-literal-symbols
	gc-global-symbols
	merge-literals
	merge-symbols
	merge-maps
	reduce-symbols
	reduce-gaps
	reduce-entry
	resolve-literals
	resolve-displacements
	remove-entry
	remove-arch
	split-zero-sections
	compress-file

cc:
	lexer
	linter
	preprocessor
	parser
	AST rundown
	- some kind of optimization
	lowering:
		calling conventions
		x86-16
		x86-32
		x86-64
		x86 extensions
		+RISC-V
		+SPARC
		+POWER ISA, POWER, PowerPC, Cell
		+Itanium
		+ARM
		+M68k
		+MIPS
		+z/Arch
		+WebAssembly
		+NVidia-, AMD-, Intel- GPU
		+DEC Alpha
	assembling
	linking
as:
	x86 16bit:
		push
		pop
		xchg
		in
		out
		xlat
		lea
		lds
		les
		lahf
		sahf
		pushf
		popf
		aaa
		baa
		neg
		aas
		das
		mul
		imul
		aam
		div
		idiv
		aad
		cbw
		cwd
		not
		shl/sal
		shr
		sar
		rol
		ror
		rcl
		rcr
		call
		into
		iret
		esc
	x86 32bit
	x86 64bit
	x86 extensions
	+RISC-V
	+SPARC
	+POWER ISA, POWER, PowerPC, Cell
	+Itanium
	+ARM
	+M68k
	+MIPS
	+z/Arch
	+WebAssembly
	+NVidia-, AMD-, Intel- GPU
	+DEC Alpha
ld:
	+archive inputs
	+compressed inputs
	+ir inputs
	output:
		+libraries
		+informative data
		+restrictive data
		+checksum data
		+signature data

[SD]:
	make
	nm
[CD]:
	c17
	ctags
	lex
	yacc
	xgettext
[XSI]:
	admin
	cal
	cflow
	compress
	uncompress
	cxref
	delta
	fuser
	get
	ipcrm
	ipcs
	link
	unlink
	nice
	nl
	prs
	rmdel
	sact
	sccs
	type
	unget
	val
	what
	zcat
[FR]:
	asa
[UP]:
	bg
	ex
	fc
	fg
	jobs
	man
	more
	talk
	vi
[UU]:
	uucp
	uudecode
	uuencode
	uustat
	uux


# Toolchain

manuals:
	include/mio.h
	include/mbr.h
	format/mbr
	abi/bios
	guide/booting/x86-bios
disassembler
mio2pe32+
fuzzy testing, valgrind, unit-tests, dbg, profiling
tup, kconfig, git


# Boot Image

mbr.bin:
	load partition and hand-off
	+EBR partitioning support
	+GPT partitioning support
vbr.bin:
	setup (16bit C code?)
	load memory map
	find root partition:
		MBR
		+EBR
		+GPT
	load standing
	load kernel
	load init
	start kernel
mkfs
fdisk:
	option -z
	option -s
	option -o
	option -f
	option -A
	option -Z
	option -i
	+EBR partitioning support
	+GPT partitioning support
boot.efi


# Kernel-ish

kernel:
	replace kill?, yield-to?, jump-point?
	fork pid = child
	caps pid caps = caps (some kind of capability or bitfield security)
	capture vec_t pid
	wait = vec_t ... (wait for a captured interrupt, or preemption)
	union pid pid (merge to process execution memory and level, can be used
		with kernel; this is just for optimization)
	in/out (port i/o stuff)
init
services:
	fabric (
		the core IPC -- in user-space -- using memory pages and map for
		security.
		blocking client writing when being used and returning it after the
		command is finished or some other thing
	)
	vfs, mem, net, proc, ui, acct
drivers:
	ahci, scsi
	acpi
	apic, mp (multiprocessor stuff)
	uefi
	pci
	nvme
	usb
	timer
	bios
	tty
	ip, dhcp, dns, arp, ether, wifi, tcp, udp...


# Userland

shred
useradd, usermod, passwd, groupadd, groupmod, etc
su, sudo, whoami
top, htop
ping, host, ssh, ftp, wget, curl
libc, libm...
fsck, sys-admin...
protect -- error correction encoding
encrypt -- encrypt files
dictionary, translations, locale
lib*: html, css, clang, js, ts, jsx, tsx, json, deflate, lzma, http1.1, http2,
	http3/quic, pdf, png, jpeg, mp4, webm, mkv, elf, bfd...
graphics
media and web browser
games
spreadsheet and other stuffs
python, ruby, js runtime, java, ada
rocq, idris, isabelle
editor
