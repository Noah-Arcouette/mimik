[BITS 64]

section .text
global __syscall1
__syscall1:
    push rdi

    mov rax, rdi
    mov rdi, rsi
    syscall

    pop rdi
    ret

global __syscall2
__syscall2:
    push rdi
    push rsi

    mov rax, rdi
    mov rdi, rsi
    mov rsi, rdx
    syscall

    pop rsi
    pop rdi
    ret

global __syscall3
__syscall3:
    push rdi
    push rsi
    push rdx

    mov rax, rdi
    mov rdi, rsi
    mov rsi, rdx
    mov rdx, r10
    syscall

    pop rdx
    pop rsi
    pop rdi
    ret
