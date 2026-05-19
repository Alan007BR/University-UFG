.section .rodata
fmt: .string "%d, %ld\n"
.data
    .globl values
    .align 4
values: .long 10, 20, 10, 40, 20, 50, 30, 10

.text
    .globl process

#ordem di, si, dx, cx, r8, r9
process:
    pushq %rbp
    movq %rsp, %rbp

    subq $32, %rsp #tamanho da mem em pilha

    #i -> %ecx
    movl $7, %ecx

    for:
        cmpl $0, %ecx
        jl afterfor             #i >= 0 --> i < 0

        #values[i]
        movq $values, %r8
        movslq %ecx, %r9
        imulq $4, %r9
        addq %r8, %r9
        movl (%r9), %r10d #r10 = values[i]

        if:
            #(stamp > values[i] --> stamp <= values[i])
            cmpl %r10d, %edi
            jle else
        
            # limit = (2*limit) + aux((short)i, (values + i));
            #pilha
            movq    %rdi, -8(%rbp)
            movq    %rsi, -16(%rbp)
            movq    %rcx, -24(%rbp)

            #1. aux((short)i, (values + i)
            movw %cx, %di
            movq $values, %rsi
            movslq %ecx, %r11
            imulq $4, %r11
            addq %r11, %rsi
            call aux

            #retirar pilha
            movq -8(%rbp),   %rdi
            movq -16(%rbp),   %rsi
            movq -24(%rbp),   %rcx

            #2. (2*limit)
            movq %rsi, %r11 
            imulq $2, %r11  #r11 = 2*limit

            #3. +
            addq %r11, %rax #rax = rax (retorno de aux) + 2*limit

            #4. limit = 3. 
            addq %rax, %rsi #limit = rax

            jmp afterif
        else:
            # pilha
            movq    %rdi, -8(%rbp)
            movq    %rsi, -16(%rbp)
            movq    %rcx, -24(%rbp)

            # printf("%d, %ld\n", stamp, limit);
            movq %rsi, %rdx
            movl %edi, %esi
            movq $fmt, %rdi
            movl $0, %eax
            call printf

            # retirar pilha
            movq -8(%rbp),   %rdi
            movq -16(%rbp),   %rsi
            movq -24(%rbp),   %rcx

        afterif:

    decl %ecx
    jmp for
    afterfor:

    movq %rsi, %rax
    leave
    ret