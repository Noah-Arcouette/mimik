[BITS 64]

section .text
global __system_unlink
__system_unlink:
    mov rax, 0x57
    syscall
    ret

global __system_link
__system_link:
    mov rax, 0x56
    syscall
    ret
