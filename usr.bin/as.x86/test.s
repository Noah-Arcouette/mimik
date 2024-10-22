.code16

.section .text, "x"
.file "enableA20.S"
stageTwo_enableA20:
.globl stageTwo_enableA20
	call stageTwo_checkA20
	cmp  $0, %ax
	je stageTwo_enableA20.noA20

	ret
stageTwo_enableA20.noA20:
	mov $stageTwo_enableA20.noA20Msg, %bx
	jmp  boot_panic

stageTwo_checkA20:
	pushf
	push %ds
	push %es
	push %di
	push %si

	cli

	xor %ax, %ax
	mov %ax, %es

	not %ax
	mov %ax, %ds

	mov $0x0500, %di
	mov $0x0510, %si

	mov  %es:(%di), %al
	push %ax

	mov  %ds:(%si), %al
	push %ax

	movb $0x00, %es:(%di)
	movb $0xff, %ds:(%si)
	cmpb $0xff, %es:(%di)

	pop %ax
	mov %al, %ds:(%si)

	pop %ax
	mov %al, %es:(%di)

	mov $0, %ax
	je stageTwo_checkA20.exit

	inc %ax
stageTwo_checkA20.exit:
	pop %si
	pop %di
	pop %es
	pop %ds
	popf

	ret

.section .rodata, "r"
stageTwo_enableA20.noA20Msg:
	.asciz "HIIIIIIIIIIII"
