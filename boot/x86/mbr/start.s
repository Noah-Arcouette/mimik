.arch x86_16
.section .text x

_start:
	; find bootable partition
	call find_mbr_partition
	cmp %ax 0
	je _start.no_partition

	; load the partition and jump to it
	jmp halt
_start.no_partition:
	mov %si _start.no_partition.msg
	call puts
	jmp halt

.global _start

.section .rodata r
_start.no_partition.msg:
	.byte "No bootable partition\n\r\0"
