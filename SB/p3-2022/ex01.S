.section .rodata
.data
    .align 8
    .globl varx
    varx:
        .byte 0
        .zero 7
        .quad 0
        .word 0
        .zero 6
.text
    .globl calc

calc:
    pushq %rbp
    movq %rsp, %rbp

    subq $32, %rsp

    #i --> rdx
    #j --> r12

    # salvando verdes
    movq %r12, -24(%rbp)

    #tmp = 3
    movl $3, -4(%rbp)

    movl $0, %edx
    for:
        cmpl $3, %edx
        jge afterfor

        #j = i + 1
        movl %edx, %r12d
        addl $1, %r12d

        #salvando amarelos
        movq %rdx, -32(%rbp)

        #process(&varx.z, &vector[j], (int)varx.x);
        #&varx.z = &varx + offset de z
        movq $varx, %rdi
        addq $16, %rdi      #1 param

        #&vector[j]
        leaq -16(%rbp), %r8
        movslq %r12d, %r9
        imulq $2, %r9
        addq %r8, %r9   #r9 = &vector[j]

        movq %r9, %rsi

        movq $varx, %r8
        movsbl (%r8), %edx #3 param        

        call process

        #restaurando amarelos
        movq -32(%rbp), %rdx

        addl %eax, -4(%rbp)

        incl %edx
        jmp for
    afterfor:


    # restaurando verdes
    movq -24(%rbp), %r12

    movl -4(%rbp), %eax

    leave
    ret

#Pilha
# tmp       -> -4
# padding   -> -6
# vector    -> -16
# r12       -> -24
# rdx       -> -32

#struct X        align 8
# x -> 0        offset 0
# p -> até 7    offset 1
# y -> 8...15   offset 8
# z -> 16, 17   offset 16
# p -> 18..23   offset 18