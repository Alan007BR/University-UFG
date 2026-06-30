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

    subq        $64, %rsp

    movq        $0, -8(%rbp)                        #j = 0
    movq        $50, -16(%rbp)                      #drop = 50
    
    movl        $0, -4(%rbp)
    for:                                            #i=0, i<5; i++
        movl        -4(%rbp), %r8d
        cmpl        $5, %r8d
        jge         afterfor

        movq        $vets, %r9
        movslq      -4(%rbp), %r10
        imulq       $4, %r10
        addq        %r9, %r10

        movss       (%r10), %xmm10                  #vets[i] 
        cvtss2sd    %xmm10, %xmm12                  #(double)vets[i]               
        movsd       factor, %xmm11
        mulsd       %xmm11, %xmm12                  #double tmp = vets[i] * factor;

        if:
            cvtsi2sdq       -16(%rbp), %xmm13       #(double)drop
            ucomisd         %xmm13, %xmm12
            jae             afterif

            leaq            -56(%rbp), %r9
            movslq          -8(%rbp), %r10
            imulq           $8, %r10
            addq            %r9, %r10    

            movsd           (%r10), %xmm5             #copy[j]
            incl            -8(%rbp)                  #j++ 

            movsd           %xmm12, (%r10)             #copy[j]=tmp
        afterif:

        incl        -4(%rbp)                          #i++
        jmp         for
    afterfor:

        movl            $0, -4(%rbp)
        for2:
            movl        -4(%rbp), %r8d
            cmpl        -8(%rbp), %r8d
            jge         afterfor2


            leaq        -56(%rbp), %r9
            movslq      -4(%rbp), %r10
            imulq       $8, %r10
            addq        %r9, %r10    

            movsd       (%r10), %xmm0             #copy[i]

            movq        $fmt, %rdi
            movl        -4(%rbp), %esi
            movl        $1, %eax
            call        printf

            incl        -4(%rbp)
            jmp         for2
        afterfor2:

        movl        $0, %eax
    leave
    ret

#pilha
# i     -> -4
# j     -> -8
# drop  -> -16
# copy  -> -56