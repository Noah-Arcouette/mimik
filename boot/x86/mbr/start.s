.arch x86_16
.section .text x

_start:
	; find bootable partition
	; load the partition and jump to it
	jmp halt

.global _start
