.section .rodata


.data
    .globl i
    .align 4
i: .long 0

    .globl bias
    .align 8
bias: .quad 256

    .globl vet
    .align 1
vet: .byte 12, 3, 20, 8

.text


.globl main

main:
   pushq %rbp
   movq  %rsp, %rbp

   # Seu código aqui...
    movl $0, i
    movl i, %r9d
    for:
    #condição i < LEN -> i >= 4
    cmp $4, %r9d
    jge afterfor

    #corpo
    #bias = filtro(vet[i], LIM, bias);
    #filtro= %dil, %si, %rdx (n usar esses pra fazer o vetor se n da BO)
    
    # vet[i] = &vet + (i * sizeOf)
    movq $vet, %r8
    movslq %r9d, %r10
    imulq $1, %r10
    addq %r8, %r10

    movb (%r10), %r11b #r11d = vet[i]

    movb %r11b, %dil
    movw $10, %si
    movq bias, %rdx
    call filtro

    #bias = filtro(.....)
    movq %rax, bias

    #incremento
    movl   i, %r9d # call está destruindo r9d?
    incl %r9d
    movl %r9d, i
    jmp for
    afterfor:
    
   # Faça o "return"
    movq $0, %rax

   leave
   ret