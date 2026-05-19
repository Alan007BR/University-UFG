.section .rodata
.data
.text
    .globl process

process:
    pushq %rbp
    movq %rsp, %rbp

    subq $48, %rsp //16x3
    # r -> %r10d

    # antes de chamar a função, como chamadora é necessário salvar na pilha os valores atuais para preservar depois da chamada
    movq %rdi, -8(%rbp)
    movq %rsi, -16(%rbp)
    movq %rdx, -24(%rbp)
    movq %rcx, -32(%rbp)
    movq %r8, -40(%rbp)
    movq %r9, -48(%rbp)

    #inverter
    movq -48(%rbp), %rdi
    movq -40(%rbp), %rsi
    movq -32(%rbp), %rdx
    movq -24(%rbp), %rcx
    movq -16(%rbp), %r8
    movq  -8(%rbp), %r9

    call calc
    movl %eax, %r10d #r = calc(f, e, d, c, b, a);

    # retirando a pilha (restaurando)
    movq -8(%rbp)   , %rdi
    movq -16(%rbp)  , %rsi
    movq -24(%rbp)  , %rdx
    movq -32(%rbp)  , %rcx
    movq -40(%rbp)  , %r8
    movq -48(%rbp)  , %r9

    # r + a + b + c + d + e + f;
    addl %edi, %r10d
    addl %esi, %r10d
    addl %edx, %r10d
    addl %ecx, %r10d
    addl %r8d, %r10d
    addl %r9d, %r10d

    # return int
    movl %r10d, %eax
    leave
    ret