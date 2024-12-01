.code16

.section .boot, "ax"
.file "setupVideo.S"
boot_setupVideo:
.globl boot_setupVideo
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

columns:
.globl columns
	.short 80

rows:
.globl rows
	.short 25

videoMemory:
.globl videoMemory
	.int 0xb8000
