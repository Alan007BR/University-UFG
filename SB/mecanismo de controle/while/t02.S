.section .rodata
.data
    .globl a
    .align 4
a:  .long 0

    .globl b
    .align 4
b:  .long 0

.text

.globl t02

t02:
pushq %rbp
movq %rsp, %rbp

### Seu código aqui...

movl a, %eax
movl b, %ecx
loop:
    # (a < 5 && b != 10)
    cmpl $5, %eax
    jge afterloop

    cmpl $10, %ecx
    je afterloop

    #corpo
    #b = b + a
    movl b, %r9d
    addl %eax, %r9d
    movl %r9d, b

    #a++
    addl $1, %eax
    jmp loop

afterloop:
    movl %eax, a


leave
ret