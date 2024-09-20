
[x] Setup Video
[x] Load Stage Two

[/] Enable A20
[x] Unreal Mode

***Com0, debug***

-C-
[ ] Get Memory Map
[x] File system, and partitions

[ ] Load object file and build page map - object file format

[ ] Setup APIC, LAPIC, I/O APIC
[ ] Start up the other processors

[ ] Protected Mode
[ ] Setup extended features

[ ] Jump to payload { needs Memory map, I/O APIC and Local APIC data, Binary file information (MiO Data) }


liblog:
	add log

	__LIBC__ add file log

	log, verbosity, type, section, process, file, function, line, message, ...
	LOG, verbosity, type, message, ...
	SECTION, section
	PROCESS, section


Install:
	Boot Loader: None, BIOS
	Boot Device: ./disk.bin

 - [x] cp

 - [ ] c99
   - [ ] cpp
   - [ ] ctranslate
   - [ ] optimize
   - [ ] compile
   - [/] as

 - [ ] ld
 - [ ] objcopy


executable loading server:
	sets up argv/argc
	loads dynamic and static executables
	provides dl* commands capable of loading all available formats
