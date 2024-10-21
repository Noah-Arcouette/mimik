.code16

.section .bss, "brw"
.file "init.S"
bootDisk: .byte 0
.globl bootDisk

.section .boot.init, "x"
boot_init:
.globl boot_init
	xor %ax, %ax
	mov %ax, %es
	mov %ax, %gs

	mov %ax, %ds
	mov %ax, %ss

	mov $0xb800, %ax
	mov %ax, %fs

	mov $BSS_START, %bx
boot_init_bss_clear:

	inc  %bx



	mov $BSS_END, %sp
	mov %sp, %bp

	mov %dl, bootDisk
	ljmp $0,$_boot
