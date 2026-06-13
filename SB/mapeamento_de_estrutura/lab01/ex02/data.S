.section .rodata
fmt: .string "%ld\n"
.data

.text
    .globl show

show:
    pushq %rbp
    movq %rsp, %rbp

    subq $32, %rsp

    #i --> ecx
    #*ptr --> rdx
    #long *ptr = d->elems;
    movq %rdi, %rdx     # rdx = &d
    addq $8, %rdx       # d->elms = &d + 8

    movl $0, %ecx
    for:
        cmpl (%rdi), %ecx #i < d->len ---> i >= d->len
        jge afterfor

        #ptr[i] = &d + (i*sizeOf)
        movslq %ecx, %r8
        imulq $8, %r8
        addq %rdx, %r8 # &ptr[i] = (i*sizeOf) + &d

        movq (%rdi), -8(%rbp)
        movq (%rcx), -16(%rbp)
        movq (%rdx), -24(%rbp)

        movq $fmt, %rdi
        movq (%r8), %rsi
        call printf

        movq -8(%rbp),  %rdi
        movq -16(%rbp), %rcx
        movq -24(%rbp), %rdx

        incl %ecx
        jmp for
    afterfor:

    leave
    ret