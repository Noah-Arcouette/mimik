.code16
.file "bootsect.S"

.section .boot, "ax"
.globl _boot
.type _boot, @function
_boot:
	call boot_setupVideo

	call boot_loadPayload
	jmp _stageTwo
.size _boot, .-_boot
