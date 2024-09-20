.code16
.section .bss, "brw"
.file "init.S"

.globl bootDisk
bootDisk: .byte 0

.section .boot.init, "x"
.globl boot_init
boot_init:
	xor %ax, %ax

	mov %ax, %es
	mov %ax, %gs

	mov %ax, %ds
	mov %ax, %ss

	mov $0xb800, %ax
	mov %ax, %fs

	mov $BSS_START, %bx
boot_init_bss_clear:
	mov $BSS_END, %sp
	mov %sp, %bp

	mov $0x80, %dl
	mov $0x00, %dl
	mov %dl, bootDisk

	ljmp $0,$_boot

.section .bss
