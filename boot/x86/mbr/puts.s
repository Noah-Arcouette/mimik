.arch x86_16
.section .text x

puts:
	mov %bh [pageNumber]
	mov %ah 0x0e
puts.loop:
	mov %al [%si]
	cmp %al 0
	je puts.end

	int 0x10

	inc %si
	jmp puts.loop
puts.end:
	ret

.global puts
