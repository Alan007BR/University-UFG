.section .rodata
.data
    .globl v1
    .align 2
v1: .word 1, 2

    .globl v2
    .align 8
v2: .quad 1, 2, 3

.text
    .globl main
    .globl aux

#di, si, dx, cx, r8, r9
main:
    pushq %rbp
    movq %rsp, %rbp

    subq $32, %rsp

    #i --> %r11
    movl $0, %r11d

    while:
        cmpl $2, %r11d #i < 2 --> i>= 2
        jge afterwhile

        # joga na pilha
        movq %rdi, -8(%rbp)
        movq %rsi, -16(%rbp)
        movq %r11, -24(%rbp)
        
        #aux(v1, i);
        movq $v1, %rdi
        movl %r11d, %esi
        call aux

        # tira da pilha
        movq -8(%rbp), %rdi
        movq -16(%rbp), %rsi
        movq -24(%rbp), %r11      

        incl %r11d
        jmp while
    afterwhile:

    movl $0, %eax
    leave
    ret

aux:
    pushq %rbp
    movq %rsp, %rbp

    subq  $32, %rsp
    movq %rbx, -8(%rbp)


    # i --> %ecx
    movl $2, %ebx
    
    for:
        cmpl $0, %ebx
        jl afterfor #i>=0 --> i < 0

        # joga na pilha
        movq %rdi, -16(%rbp)
        movq %rsi, -24(%rbp)

        # 1 e 2 param já estão nas posições

        movq $v2, %rdx
        movl %edx, %ecx
        call sum


        # tira da pilha
        movq -16(%rbp), %rdi
        movq -24(%rbp), %rsi


    decl %ecx
    jmp for
    afterfor:

    movq -8(%rbp), %rbx
    leave
    ret