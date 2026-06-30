.section .rodata
fmt: .string "Soma: %ld\n"
.data
.text
    .globl main

main:
    pushq %rbp
    movq %rsp, %rbp

    subq $32, %rsp
    #short s ---> %r10w

    # int i e long l na pilha
    movq $0, -4(%rbp)   # int i
    movl $0, -16(%rbp) # int l
    
    call constante
    movsbw %al, %r10w   # s = ....


    #salvando registradores
    movq %r10, -24(%rbp)

    #init(s, &l, &i);
    movw %r10w, %di         # 1 param
    leaq -16(%rbp), %rsi    # 2 param
    leaq -4(%rbp), %rdx     # 3 param
    call init

    #recuperando registradores
    movq -24(%rbp), %r10

    movq    $fmt, %rdi
    movq   -4(%rbp),  %r11     # r11 = l
    movslq -16(%rbp), %rcx     # rcx = (long)i
    addq   %rcx, %r11          # r11 = l + i
    movswq %r10w, %rcx         # rcx = (long)s
    addq   %rcx, %r11          # r11 = l + i + s
    movq   %r11, %rsi
    call printf
    
    movl $0, %eax
    leave
    ret