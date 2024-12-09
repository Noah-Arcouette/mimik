.code16
.section .text, "x"
.file "test2.S"

test2:
	mov $0, %al
	mov %al, data1
	jmp test1

.section .rodata, "r"

data2:
.global data2
	.byte 0
