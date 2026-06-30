.section .rodata
fmt: .string "copy[%d] = %f\n"

.data
    .globl factor
    .align 8
factor: .double 15.0

    .globl vets
    .align 4
vets: .float 1.0, 2.0, 3.0, 4.0, 5.0

.text
    .globl main

main:
    pushq %rbp
    movq %rsp, %rbp

    subq $64, %rsp

    movl $0,  -8(%rbp)
    movq $50, -16(%rbp)


    movl $0, -4(%rbp)
    for:
        movl -4(%rbp), %r8d
        cmpl $5, %r8d
        jge afterfor

        #double tmp = vets[i] * factor;
        #vets[i]
        movq $vets, %r9
        movslq %r8d, %r10
        imulq $4, %r10
        addq %r9, %r10

        movss (%r10), %xmm0 #xmm0 = vets[i]

        cvtss2sd %xmm0, %xmm0
        mulsd factor, %xmm0 #tmp = vets[i]*factor

        if:
            cvtsi2sdq -16(%rbp), %xmm1  #xmm1 = (double)drop
            ucomisd %xmm1, %xmm0
            jae afterif
            
            #copy[j++] = tmp;
            leaq -56(%rbp), %r11
            movl -8(%rbp), %r10d
            movslq %r10d, %r10
            imulq $8, %r10
            addq %r10, %r11

            movsd %xmm0, (%r11)

            incl -8(%rbp)

        afterif:

        incl -4(%rbp)
        jmp for
    afterfor:

    movl $0, -4(%rbp)
    for2:
        movl -8(%rbp), %r11d
        cmpl %r11d, -4(%rbp)
        jge afterfor2

        movq $fmt, %rdi
        movl -4(%rbp), %esi
        
        #copy[i]
        leaq -56(%rbp),  %r8
        movslq -4(%rbp), %r9
        imulq $8, %r9
        addq %r8, %r9
        movsd (%r9), %xmm0


        movl $0, %eax
        call printf

        incl -4(%rbp) 
        jmp for2
    afterfor2:


        movl $0, %eax
    leave
    ret

#pilha
# i     -> -4
# j     -> -8
# drop  -> -16
# copy  -> -56