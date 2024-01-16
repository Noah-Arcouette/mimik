[BITS 64]

section .text
global __syscall1
__syscal1:
    push rdi

    mov rax, rdi
    mov rdi, rsi
    syscall

    pop rdi
    ret

global __syscall2
__syscal2:
    push rdi
    push rsi

    mov rax, rdi
    mov rdi, rsi
    mov rsi, rdx
    syscall

    pop rsi
    pop rdi
    ret
