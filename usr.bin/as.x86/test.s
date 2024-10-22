.code16

.section .text, "x"
.file "stage2.S"
_stageTwo:
.globl _stageTwo
	call stageTwo_enableA20

	cli






	ljmp $0x08,$_stageTwo.pmode
.code32
_stageTwo.pmode:







	ljmp $0,$_stageTwo.unreal
.code16
_stageTwo.unreal:
	xor %ax, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %ss

	sti

	jmp _unreal
