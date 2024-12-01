.code16

.section .rodata, "a"
.file "gdt.S"
.align 4
stageTwo_gdtr:
.globl stageTwo_gdtr
	.word stageTwo_gdt.end-stageTwo_gdt-1
	.long stageTwo_gdt

// simple flat GDT
// used for unreal mode
.align 4
stageTwo_gdt:
	stageTwo_gdt.null:  .long 0, 0
	stageTwo_gdt.text:
		.word 0xffff     // limit
		.word 0          // base
		.byte 0          // base
		.byte 0b10011010 // access bit
		.byte 0b10001111 // flags+limit (16 bit code)
		.byte 0          // base
	stageTwo_gdt.flat:
		.word 0xffff     // limit
		.word 0          // base
		.byte 0          // base
		.byte 0b10010010 // access bit
		.byte 0b11001111 // flags+limit (32 bit data)
		.byte 0          // base
stageTwo_gdt.end:
