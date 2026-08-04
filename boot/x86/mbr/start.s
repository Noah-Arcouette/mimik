.arch x86_16
.section .text x

_start:
	mov %bh [pageNumber]
	mov %al 0x0e
	mov %ah 0x69
	; int 0x10

	; find bootable partition
	; load the partition and jump to it

	jmp halt

.global _start
