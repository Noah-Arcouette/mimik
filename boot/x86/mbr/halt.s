.arch x86_16
.section .text x

halt:
	cli
	hlt

	sjmp halt

.global halt
