.section .rodata
.data
.text
    .globl calc1

#xmm0, xmm1
calc1:
    pushq %rbp
    movq %rsp, %rbp

    #(a+b)*(a-b);

    cvtss2sd %xmm1, %xmm3
    addsd %xmm0, %xmm3      #(a+b)

    cvtss2sd %xmm1, %xmm4 #xmm4 = a
    subsd %xmm4, %xmm0  # (a-b)

    mulsd %xmm3, %xmm4

    movsd %xmm4, %xmm0

    leave
    ret