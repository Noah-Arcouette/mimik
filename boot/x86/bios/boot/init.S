.code16
.file "init.S"

.bss
.globl bootDisk
.type bootDisk, @object
bootDisk: .byte 0
.size bootDisk, .-bootDisk

.section .boot.init, "ax"
.globl boot_init
.type boot_init, @function
boot_init:
	// Clear segments
	xor %ax, %ax

	// Extra segments
	mov %ax, %es
	mov %ax, %gs

	// Data segments
	mov %ax, %ds
	mov %ax, %ss

	// Use FS for the frame buffer
	mov $0xb800, %ax
	mov %ax, %fs

	// Clear bss
	mov $BSS_START, %bx
boot_init_bss_clear:
	movb $0, (%bx)
	inc  %bx
	cmp  $BSS_END, %bx
	jl   boot_init_bss_clear

	// Setup Stack
	mov $BSS_END, %sp
	mov %sp, %bp

	// save boot disk
#ifdef HDD
	mov $0x80, %dl // Hard disk boot number
#endif
#ifdef FLOPPY
	mov $0x00, %dl // floppy boot disk number
#endif
	mov %dl, bootDisk
	// if unknown then do nothing, using the BIOS given one
	// 	which may be incorrect on buggy BIOSes

	// Set Code segment and jump to boot
	ljmp $0,$_boot
.size boot_init, .-boot_init
