.section .rodata
fmt: "Soma %f maior que o limite %f (%d)\n"
        .align 8
const0: .double 0.0
.data
.text
    .globl sum
sum:
pushq %rbp
movq %rsp, %rbp

subq $72, %rsp

#i=4
movq $4, -4(%rbp)

#s=0.0
movq const0, %xmm7
movq %xmm7, -16(%rbp)

#vi[4] = {5,6,7,8};
movl $5, -32(%rbp)
movl $6, -28(%rbp)
movl $7, -24(%rbp)
movl $8, -20(%rbp)

#salvando registradores
movq %xmm0, -72(%bp)

#multi(v1, vd, i)
leaq -32(%rbp), %rdi
leaq -64(%rbp), %rsi
movl  -4(%rbp), %rdx
call mult

movq -72(%bp), %xmm0

while:
    movl -4(%rbp), %r8
    cmpl $0, %r8
    jle afterwhile

    #--i
    decl -4(%rbp)

    #vd[i]
    leaq -64(%rbp), %r8
    movslq -4(%rbp), %r9
    imulq $8, %r9
    addq %r8, %r9

    movsd (%r9), %xmm1

    movsd-16(%rbp), %xmm5
    addsd %xmm1, %xmm5
    movsd %xmm5, -16(%rbp)

    if:
        ucomisd %xmm0, %xmm5
        jp  afterif
        jbe afterif
        
        movq %xmm0, -72(%rbp)

        movq $fmt, %rdi
        movsd %xmm0, %xmm1
        movsd -16(%rbp), %xmm0
        movl -4(%rbp), %esi
        call printf

        movq -72(%bp), %xmm0

    afterif:


    jmp while
afterwhile:

    movsd -16(%rbp), %xmm0

leave
ret

#pilha
# i     -> -4
# p     -> -8
# s     -> -16
# vi    -> -32
# vd    -> -64
# xmm0  -> -72