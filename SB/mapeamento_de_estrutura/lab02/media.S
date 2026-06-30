.section .rodata
fmt: .string "Diferença em %d/%d: %ld\n"
.data

.globl prods
.align 8
prods:
    .byte 0
    .zero 7
    .quad 0
    .long 0
    .zero 4

    .byte 0
    .zero 7
    .quad 0
    .long 0
    .zero 4

.text
    .globl media
    .globl main

media:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp

movq %r12, -8(%rbp)
movq %r13, -16(%rbp)
#----------------------------

movl $0, %r12d  #i
movq $0, %r13   #soma

movl $0, %r12d  #i=0

for01:
movslq %r12d, %rax
cmpq %rsi, %rax
jge endfor01

movslq %r12d, %rax  #(long)i
imulq $24, %rax     #i*sizeOf(prduto)
addq %rdi, %rax     #&ptr + (i*sizeOf)

addq 8(%rax), %r13  #soma = r13 = ptr[i].preco


incl %r12d
jmp for01
endfor01:


movq %r13, %rax # rax = soma
cqto
idivq %rsi   # soma (rax) / size

#-------------------------
movq -8(%rbp), %r12
movq -16(%rbp), %r13

leave
ret

main:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    #i ---> %r8d
    movl $0, %r8d

    movq $prods, %r10
    #prods[0].mes   = JAN;
    #prods[0].preco = 100;
    #prods[0].ano   = 2020;
    movb $1, (%r10)
    movq $100, 8(%r10)
    movl $2020, 16(%r10)

    addq $24, %r10 #&prod[i] = &prods + sizeOf(Produto)
    #prods[1].mes   = FEV;
    #prods[1].preco = 120;
    #prods[1].ano   = 2020;

    movb $2, (%r10)
    movq $120, 8(%r10)
    movl $2020, 16(%r10)   

    # salvando registradores, sempre salvamos o registrador inteiro
    movq %r10, -8(%rsp)
    movq %r8,  -16(%rsp)

    #media(prdos, SIZE)
    movq $prods, %rdi
    movq $2, %rsi
    call media

    #restaurando registradores
    movq 8(%rsp), %r10
    movq 16(%rsp), %r8
    
    #long m = media(prods, SIZE);
    movq %rax, %r9

    while:
    cmpl $2, %r8d
    jge afterwhile

    #prods[i]
    #r10 = &prods
    movq $prods, %r10
    movslq %r8d, %r11  #(long)i
    imulq $24, %r11    #sizeOF(produto)*i
    addq  %r11, %r10   # prods[i] = &prods + (i*sizeOf(produtos))


    movq %r10, -8(%rbp)
    movq %r8,  -16(%rbp)
    movq %rdi, -24(%rbp)
    movq %r9,  -32(%rbp)

    movq $fmt, %rdi         #1param
    movsbl (%r10), %esi     #2param
    movl 16(%r10), %edx     #3param
    movq 8(%r10), %rcx      #4param
    subq %r9, %rcx          #4param
    call printf

    movq 8(%rbp),  %r10
    movq 16(%rbp), %r8
    movq 24(%rbp), %rdi
    movq 32(%rbp), %r9

    incl %r8d
    jmp while
    afterwhile:

    movl $0, %eax
    leave
    ret