.arch x86_16
.section .init x

_init:
	; setup segments, other than cs as our addresses are wrong
	xor %ax %ax
	mov %es %ax
	mov %ds %ax
	mov %ss %ax
	mov %sp BSS_END
	mov %bp %sp

	; save the DL register
	mov [diskNumber] %dl

	mov %si 0x7c00
	mov %di 0x600
	mov %cx 0x100
	repz movs .word

	; addresses are good now
	ljmp _start 0

.global _init

.section .bss vrw

diskNumber:
	.res.byte 1

.global diskNumber
