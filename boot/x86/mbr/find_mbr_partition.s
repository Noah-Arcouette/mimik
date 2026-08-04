.arch x86_16
.section .text x

find_mbr_partition:
	mov %si MBR_PART1 ; the first partition
	mov %cx 4

find_mbr_partition.loop:
	; read the status byte
	mov %dl [%si]

	; see if its bootable
	test %dl 0x80
	jnz find_mbr_partition.found

	; continue if not
	add %si 16
	loop find_mbr_partition.loop
	; fall through, didn't find any

	xor %ax %ax
	ret
find_mbr_partition.found:
	mov %ax %si ; return the partition
	ret

.global find_mbr_partition
