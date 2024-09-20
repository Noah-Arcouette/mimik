.code16
.file "setupVideo.S"

.section .boot, "ax"
.globl boot_setupVideo
.type boot_setupVideo, @function
boot_setupVideo:
	mov $0x05, %ah // set active page
	mov $0x00, %al // zero-th page
	int $0x10 // video services

	mov $0x00, %ah // set video mode
	mov $0x03, %al // 80x25 video mode
	int $0x10 // video services

	mov $0x01, %ah // Cursor shape
	mov $0x3f, %ch // Disable cursor
	int $0x10 // video services

	ret
.size boot_setupVideo, .-boot_setupVideo

.globl columns
.type columns, @object
columns:
	.short 80
.size columns, .-columns

.globl rows
.type rows, @object
rows:
	.short 25
.size rows, .-rows

.globl videoMemory
.type videoMemory, @object
videoMemory:
	.int 0xb8000
.size videoMemory, .-videoMemory
