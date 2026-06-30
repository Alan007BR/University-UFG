.section .rodata

.data
    .globl a
    .align 4
a: .long 30

    .globl b
    .align 4
b: .long 45

    .globl c
    .align 4
c: .long -60

    .globl d
    .align 4
d: .long 25


.text

.globl ex01

ex01:

   pushq %rbp

   movq  %rsp, %rbp



   # Seu código aqui...
   # _if (a > b) {
   # c = -c;
   # d = c * 3;
   #}
    # n pode comparar memorias globais, então jogar no registrador
    movl a, %eax
    movl b, %edx

    cmpl %edx, %eax
    jle end_if # > se torna <=

    // if(b>=a) { -> b < a
    movl a, %eax
    movl b, %edx

    cmpl %eax, %edx
    jl end_if2 # >= se torna <

end_if:

    #c = -c;
    movl c, %r10d
    negl %r10d
    movl %r10d, c
    
    #d = c * 3;
    movl c, %r11d
    imull $3, %r10d
    movl %r11d, d

end_if2:
    # c = (a + b) * c;
    movl c, %r10d

    #(a+b)
    movl a, %r11d
    movl b, %r9d
    addl %r9d, %r11d

    # (r11d * c)
    imull %r10d, %r11d
    movl %r11d, c

    # d = 1024;
    movl $1024, %r8d
    movl %r8d, d

   leave

   ret
   
    