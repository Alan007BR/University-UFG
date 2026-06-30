.section .rodata
fmt: .string "%d\n"
.data

.text
    .globl show

#di, si, dx, cx, r8, r9
#ax - retorno
show:
    pushq %rbp
    movq %rsp, %rbp

    #alocat mem pilha
    subq $32, %rsp

    #i --> %ecx
    movl $0, %ecx

    for: #i < size --> i>=size
    cmpl %esi, %ecx
    jge end_for

    #v[i]

    movq %rdi, %r8
    movslq %ecx, %r9
    imulq $4, %r9
    addq %r8, %r9
    movl (%r9), %r10d #v[i]


    movq %rcx, -8(%rbp)
    movq %rdi, -16(%rbp)
    movq %rsi, -24(%rbp)

    
    movq $fmt, %rdi   #1 param
    movl %r10d, %esi  #2 param
    movq $0, %eax     #3 regra adicional do printf
    call printf       #chamada de função


    movq -8(%rbp), %rcx
    movq -16(%rbp), %rdi
    movq -24(%rbp), %rsi



    incl %ecx
    jmp for
    end_for:


    leave
    ret