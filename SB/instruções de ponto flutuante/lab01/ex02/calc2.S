.section .rodata
fmt: .string "a = %f, b = %f, e = %f\n"
.data
.text
    .globl calc2

#xmm0, #xmm1
calc2:
    pushq %rbp
    movq %rsp, %rbp

    subq $32, %rsp

    # salvar registradores
    movq %xmm0, -8(%rbp)

    cvtss2sd %xmm1, %xmm0
    call cos

    movsd %xmm0, %xmm2      #xmm10 = return of cos

    # restaurar
    movq -8(%rbp), %xmm0

    cvtss2sd %xmm1, %xmm9   #xmm9 = (double)a
    addsd %xmm9, %xmm2      #e = xmm10 = returnOfCos + a

    # salvar registradores
    movq %xmm0, -8(%rbp)
    movq %xmm1, -16(%rbp)

    movq $fmt, %rdi
    cvtss2sd %xmm0, %xmm8   #(double)a
    movsd %xmm8, %xmm0      #1param xmm0 = (double)a
    cvtss2sd %xmm1, %xmm7   #(double)b
    movsd %xmm7, %xmm1      #2param (double)b
    #xmm2 = %xmm2
    call printf

    # restaurar
    movq -8(%rbp), %xmm0
    movq -16(%rbp), %xmm1

    movss %xmm1, %xmm0

    leave
    ret