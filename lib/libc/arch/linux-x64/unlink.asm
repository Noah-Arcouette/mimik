[BITS 64]

section .text
global __system_unlink
__system_unlink:
    mov rax, 0x57
    syscall
    ret
