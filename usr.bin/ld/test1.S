.code16
.section .text, "x"
.file "test1.S"

test1:
.global test1
	mov $0, %al
	mov %al, data2
	jmp test2

.section .bss, "brw"

data1:
	.byte 0
