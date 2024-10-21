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

	push %ds
	push %es
	push %di
	push %si

	cli

	xor %ax, %ax
	mov %ax, %es


	mov %ax, %ds

	mov $0x0500, %di
	mov $0x0510, %si


	push %ax


	push %ax





	pop %ax


	pop %ax


	mov $0, %ax
	je stageTwo_checkA20.exit

	inc %ax
stageTwo_checkA20.exit:
	pop %si
	pop %di
	pop %es
	pop %ds


	ret

.section .rodata, "r"
stageTwo_enableA20.noA20Msg:
	.asciz "HIIIIIIIIIIII"
