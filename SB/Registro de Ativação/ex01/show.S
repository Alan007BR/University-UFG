.section rodata
fmt: .string "%d\n"
.data

.text
    .globl main

main:
    pushq %rbp #abre chaves
    movq %rsp, %rbp

    subq $32, %rsp

    #int i
    # i -> edx

    # for ()
    movl $0, %edx   #i = 0

    for:
    #_if (i>= size)
    cmpl %esi, %edx  # além de trocar o sinal tem que trocar os comparadores
    jge end_for     

    #print
    movq %rdi, -8(%rbp)
    movq %rsi, -16(%rbp)
    movq %rdx, -24(%rbp)

    movq $fmt, %rdi

    #v[i]
    movq %rdi, %r8
    movslq %edx, %r9
    imulq $4, %r9
    addq %r8, %r9

    movl (%r9), %esi # v[i]

    call print

    movq -8(%rbp),  %rdi
    movq -16(%rbp), %rsi
    movq -24(%rbp), %rdx

    incl %edx
    jmp for
    end_for:

    movq %rbp, %rsp
    popq %rbp
    # ou só leave
    ret # fecha chaves