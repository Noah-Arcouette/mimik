.arch x86_16
.section .init x

_init:
	; setup segments
	xor %ax %ax
	mov %es %ax
	mov %ds %ax
	mov %ss %ax
	mov %sp BSS_END
	mov %bp %sp

	; save the BH and DL registers
	mov [diskNumber] %dl
	mov [pageNumber] %bh

	ljmp _start 0

.global _init

.section .bss vrw

diskNumber:
	.res.byte 1
pageNumber:
	.res.byte 1

.global diskNumber
.global pageNumber
