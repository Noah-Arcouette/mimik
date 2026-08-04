.arch x86_16
.section .init x

_init:
	; setup segments
	xor %ax %ax
	; mov %es %ax
	; mov %ds %ax
	; mov %ss %ax
	; mov %sp BSS_END
	; mov %bp %sp
	ljmp _init.next 0
_init.next:
	; move the boot code
	; find bootable partition
	; load the partition and jump to it

	jmp halt

.global _init
