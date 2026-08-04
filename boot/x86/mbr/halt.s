.arch x86_16
.section .text x

halt:
	mov %si halt.msg
	call puts
halt.loop:
	cli
	hlt

	sjmp halt.loop

.global halt

.section .rodata r

halt.msg:
	.byte "Halting...\n\r\0"
