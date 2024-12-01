.code16

.section .boot, "ax"
.file "bootsect.S"
_boot:
.globl _boot
	call boot_setupVideo

	call boot_loadPayload
	jmp _stageTwo
