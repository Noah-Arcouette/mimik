.file "gdt.S"
.code16

.section .rodata, "a"
.type stageTwo_gdtr, @object
.align 4
.globl stageTwo_gdtr
stageTwo_gdtr:
	.word stageTwo_gdt.end-stageTwo_gdt-1
	.long stageTwo_gdt
.size stageTwo_gdtr, .-stageTwo_gdtr

.type stageTwo_gdt,      @object
.type stageTwo_gdt.null, @object
.type stageTwo_gdt.text, @object
.type stageTwo_gdt.flat, @object
.type stageTwo_gdt.end,  @object
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
.size stageTwo_gdt, .-stageTwo_gdt

.size stageTwo_gdt.null, 8
.size stageTwo_gdt.text, 8
.size stageTwo_gdt.flat, 8
.size stageTwo_gdt.end,  0
