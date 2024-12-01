.code16

.section .text, "ax"
.file "enableA20.S"
stageTwo_enableA20:
.globl stageTwo_enableA20
	call stageTwo_checkA20 // check A20 line
	cmp  $0, %ax
	je stageTwo_enableA20.noA20 // fail if it isn't pre set from BIOS/CSM

	ret
stageTwo_enableA20.noA20:
	mov $stageTwo_enableA20.noA20Msg, %bx // panic
	jmp  boot_panic

// ax: 0, if A20 disabled
stageTwo_checkA20:
	pushf // save registers
	push %ds
	push %es
	push %di
	push %si

	cli // no interrupts

	xor %ax, %ax // clear es
	mov %ax, %es

	not %ax // set ds to all ones
	mov %ax, %ds

	mov $0x0500, %di // set addresses to start of usable address space
	mov $0x0510, %si

	// save data
	mov  %es:(%di), %al
	push %ax

	mov  %ds:(%si), %al
	push %ax

	// set data
	movb $0x00, %es:(%di)
	movb $0xff, %ds:(%si)
	cmpb $0xff, %es:(%di) // check if memory wraps around

	// restore data
	pop %ax
	mov %al, %ds:(%si)

	pop %ax
	mov %al, %es:(%di)

	mov $0, %ax // no using xor becasue it sets flags
	je stageTwo_checkA20.exit // check if it wrapped around

	inc %ax // failed
stageTwo_checkA20.exit:
	pop %si // reset registers
	pop %di
	pop %es
	pop %ds
	popf

	ret

#include "../lang.h"
.section .rodata, "a"
stageTwo_enableA20.noA20Msg:
	.asciz STAGE_TWO_A20_ERROR
