.code16
.file "panic.S"

.section .boot, "ax"
.globl boot_panic
.type boot_panic, @function
boot_panic:
	mov $0, %di // start of video memory
boot_setupVideo.fillVideo:
	movb $' ',  %fs:(%di)
	inc %di
	movb $0x40, %fs:(%di) // fill background with red
	inc %di

	cmp $0xffff, %di // until end of video memory
	jg boot_setupVideo.fillVideo

	mov $0, %di  // start of video memory
boot_panic.loop:
	mov (%bx), %al // read message byte
	cmp $0, %al // check if terminator
	je boot_panic.halt // leave on terminator

	movb %al, %fs:(%di) // print character
	inc %di
	movb $0x40, %fs:(%di) // red background

	inc %di // next character
	inc %bx

	jmp boot_panic.loop // loop
boot_panic.halt:
	cli // stop interrupts
	hlt // await interrupts
	jmp boot_panic.halt // loop forever
.size boot_panic, .-boot_panic
