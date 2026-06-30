.section .rodata
fmt: .string "Iteração %d, v = %d\n"
.data
    .globl i
    .align 4
i:  .long 0

    .globl v
    .align 2
v:  .word  0

    .globl vetA
    .align 2
vetA:.word 28,42,16,23,47

    .globl vetB
    .align 4
vetB:.long 0, 0, 0, 0, 0

.text
    .globl main

#di, si, dx, cx, r8, r9
#n usar: di, si, cx, ax
main:
    pushq %rbp
    movq  %rsp, %rbp

    subq $16, %rsp

    while:
        cmpl $5, i  # i<5 --> i>=5 signed ---> greater/less
        jge afterwhile

        #corpo do while
        #v = vetA[i] << 2;
        #vetA[i]
        movq $vetA, %r8
        movslq i, %r9
        imulq $2, %r9
        addq %r8, %r9
        movw (%r9), %r10w

        #vetA[i] << 2
        shl $2, %r10w
        #v = vetA[i] << 2;
        movw, %r10w, v 

        #printf("Iteração %d, v = %d\n", i, (int)v);
        movq $fmt, %rdi #1 param
        movl i, %esi    #2 param
        movswl v, %edx  #3 param
        call printf     #chamada

        #&vetB[i]
        movq $vetB, %r8
        movslq i, %r9
        imulq $4, %r9
        addq %r8, %r9
        movl (%r9), %r10d #desnecessária, eu só preciso do & e não do valor apontado

        movq %r9, -8(%rbp)  #unico param que não está em memória, passar pra pilha

        movl i, %edi    #1 param
        movw v, %si     #2 param
        movq %r9, %rdx  #3 param
        call process    #chamada

        movq -8(%rbp), %r9

        incl i
        jmp while
    afterwhile:

        movq $vetB, %rdi    #1 param
        movq $5, %rsi       #2 param
        call show           #3 param


    movl $0, %eax
    leave
    ret