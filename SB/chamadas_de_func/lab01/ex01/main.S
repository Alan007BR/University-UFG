.section .rodata
#Valores constante que não muda
        .align 1
str:    .string "Hello"


.data
    .globl val
    .align 4
val: .long 432

    .globl age
    .align 2
age: .word 4

    .globl r
    .align 4
r: .long 0

    .globl err
    .align 8
err: .quad 2048


.text



.globl main

main:
    pushq %rbp
    movq  %rsp, %rbp

    # Seu código aqui...
    #val = sum("Hello", val, age, &r);

    #1. colocar os params nos registradores
    #2. chamar função


    #int sum(const char *prefix, int v1, short v2, int *s);
    # rdi, esi, dx, rcx
    movq $str, %rdi
    movl val, %esi
    movw age, %dx
    movq $r, %rcx

    call sum
    # eax-> retorno
    movl %eax, val #val = sum(....)

    #void show(long err, int val, int r);
    #rdi, esi, edx

    movq err, %rdi
    movl val, %esi
    movl r, %edx
    
    call show


    # Faça o "return"
    movl $0, %eax
    leave
    ret