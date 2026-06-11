.arch x86_16
.section .init x

_init:
	sjmp _init

.global _init
