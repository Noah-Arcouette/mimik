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




	mov $0, %di
boot_panic.loop:


	je boot_panic.halt


	inc %di
	movb $0x40, %fs:(%di)
	inc %di
	inc %bx

	jmp boot_panic.loop
boot_panic.halt:
	cli
	hlt
	jmp boot_panic.halt
