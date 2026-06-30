.section .rodata
fmt: .string "Soma %f maior que o limite %f (%d)\n"

        .align 8
const0: .double 0.0
.data
.text
    .globl sum

#xmm0
sum:
    pushq %rbp
    movq %rsp, %rbp

    subq $80, %rsp

    movl $4, -4(%rbp)       #i = 4

    movsd const0, %xmm5     #constante é memória, n ia complicar pq é memoria memoria
    movsd %xmm5, -16(%rbp)

    # invertido, pois a pilha é invertida
    movl $5, -32(%rbp)      #v4[1] 
    movl $6, -28(%rbp)      #v4[2]
    movl $7, -24(%rbp)      #v4[3]
    movl $8, -20(%rbp)      #v4[4]

    # salvar xmm0
    movq %xmm0, -72(%rbp)

    leaq -32(%rbp), %rdi    #1 param
    leaq -64(%rbp), %rsi    #2 param
    movl  -4(%rbp),  %edx   #3 param

    call mult

    # restaurar xmm0
    movq -72(%rbp), %xmm0

    while:
        cmpl $0, -4(%rbp)
        jle afterwhile

        #s += vd[--i];
        #--i
        decl -4(%rbp)

        #vd[i] = &vd + (i * sizeOf vd) já decrementamos o i
        leaq -64(%rbp), %r8       #&vd
        movslq -4(%rbp), %r9      #long i
        imulq $8, %r9             #i*sizeOFvd
        addq %r8, %r9             #r9 = &vd + (i * sizeOf vd)

        movsd (%r9), %xmm1

        movsd -16(%rbp), %xmm2  #ponto flutuante tem que fazer um registrado e a unica que manda pra memoria é um mov
        addsd %xmm1, %xmm2
        movsd %xmm2, -16(%rbp)

        #se usa l e g no inteiro, a e b no flutuante
        if:
            movsd -16(%rbp), %xmm2
            ucomisd %xmm0, %xmm2    #ponto flutuante é ucomiss ou ucomisd
            jp  afterif             #jp é o not a number NaN
            jbe afterif

            # salvar xmm0
            movq %xmm0, -72(%rbp)

            movq $fmt, %rdi         #1 param  (1)
            movsd %xmm0, %xmm1      #3 param  (1xmm)
            movsd -16(%rbp), %xmm0  #2 param  (2xmm)
            movl -4(%rbp), %esi     #4 param  (2)
            call printf

            # restaurar xmm0
            movq -72(%rbp), %xmm0


        afterif:

        jmp while
    afterwhile:    

    movsd -16(%rbp), %xmm0

    leave
    ret


#pilha

# i  -> -4
# p  -> -8
# s  -> -16
# vi -> -32
# vd -> -64
# xmm0 -> -72