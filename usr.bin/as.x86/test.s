.code16
.section .boot, "x"
.file "panic.S"

boot_panic:
.globl boot_panic
	mov $0, %di
boot_setupVideo.fillVideo:
	movb $' ',  %fs:(%di)
	inc %di
	movb $0x40, %fs:(%di)
	inc %di

	cmp $0xffff, %di
	jg boot_setupVideo.fillVideo

	mov $0, %di
boot_panic.loop:
	mov (%bx), %al
	cmp $0, %al
	je boot_panic.halt

	mov %al, %fs:(%di)
	inc %di
	movb $0x40, %fs:(%di)
	inc %di
	inc %bx

	jmp boot_panic.loop
boot_panic.halt:
	cli
	hlt
	jmp boot_panic.halt
