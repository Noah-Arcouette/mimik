.code16

.section .rodata, "r"
.file "gdt.S"
.align 4
stageTwo_gdtr:
.globl stageTwo_gdtr
	.word stageTwo_gdt.end
	.long stageTwo_gdt

.align 4
stageTwo_gdt:
	stageTwo_gdt.null:  .long 0 .long 0
	stageTwo_gdt.text:
		.word 0xffff
		.word 0
		.byte 0
		.byte 0b10011010
		.byte 0b10001111
		.byte 0
	stageTwo_gdt.flat:
		.word 0xffff
		.word 0
		.byte 0
		.byte 0b10010010
		.byte 0b11001111
		.byte 0
stageTwo_gdt.end:
