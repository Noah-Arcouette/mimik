.code16

.section .text, "ax"
.file "stage2.S"
_stageTwo:
.globl _stageTwo
	call stageTwo_enableA20

	cli // dissable interrupts

	// load GDT
	lgdt stageTwo_gdtr
	mov  %cr0, %eax
	or   $1,    %al // PE set
	mov  %eax, %cr0

	// setup PE segments
	ljmp $0x08,$_stageTwo.pmode
.code32
_stageTwo.pmode:
	mov $0x10, %ebx
	mov %ebx,  %ds // initialized data segment as the flat segment
	mov %ebx,  %es // and same for the extra segment
	mov %ebx,  %ss // and same for the stack segment

	and  $0xfe, %al // PE unset
	mov  %eax, %cr0
	ljmp $0,$_stageTwo.unreal // back to unreal mode
.code16
_stageTwo.unreal:
	xor %ax, %ax // clear segments back
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %ss

	sti // bring back interrupts

	jmp _unreal // jump to C
