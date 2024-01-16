[BITS 64]

section .text
global unlink
unlink:
    mov rax, 0x57
    syscall
    ret
