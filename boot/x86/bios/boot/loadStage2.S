.code16
.file "loadStage2.S"

.section .boot, "ax"
.globl boot_loadPayload
.type boot_loadPayload, @function
boot_loadPayload:
	mov $0, %dh // First head
	mov $0, %ch // First cylinder
	mov $2, %cl // Second sector, after MBR
	// Load payload from MBR break
	mov $0x02, %ah // BIOS read sectors
	mov $STAGE_TWO_SECTORS, %al // Amount of sectors
	mov bootDisk, %dl // set disk to boot disk
	mov $STAGE_TWO_START, %bx // load into payload start address
	int $0x13 // disk services

	// check if error
	jc boot_loadPayload.error

	// make sure the right amount of sectors were read
	cmp $STAGE_TWO_SECTORS, %al
	je boot_loadPayload.ret

boot_loadPayload.error:
	// Print read error message
	mov $readErrorMsg, %bx
	jmp boot_panic

boot_loadPayload.ret:
	ret
.size boot_loadPayload, .-boot_loadPayload

#include "../lang.h"
.type readErrorMsg, @object
readErrorMsg:
	.asciz STAGE_TWO_READ_ERROR
.size readErrorMsg, .-readErrorMsg
