.section .rodata
.data
    .globl a
    .align 8
a:  .quad 0
.text
    .globl aux


#di, si, dx, cx, r8, r9
aux:
    pushq %rbp
    movq %rsp, %rbp

    subq $16, %rsp

    # salva callee-saved
    movq %r12, -8(%rbp)
    movq %r13, -16(%rbp)

    movq %rdi, %r12    # r12 = ptr
    movb %cl,  %r13b   # r13b = limit

    # init(&a, ptr, SIZE);
    movq %rdi, %rsi
    movq $a, %rdi
    movl $120, %edx
    call init

    #for ( ; *ptr ; ptr++) {
    for:
        # _if ----------------------------------------------------------------
        cmpw $0, (%r12) #comparar o valor apontado na memória e não o endereço
        je afterfor

        if: #(char)ptr[a] > limit ---> (char)ptr[a] <= limit
        # $ptr é o próprio ptr então não precisa de movq $ptr, %r8
        movq a, %r9
        imulq $2, %r9
        addq %rdi, %r9

        movb (%r9), %r10b # (char)ptr[a] - truncamento de short pra char

        cmpb %cl, %r10b
        jbe else     #char é unsigned então é below/above
        # ----------------------------------------------------------------

        #corpo
        
        #printf(fmt, *ptr);
        movw (%r12), %si # 2 param 
        movq %rdx, %rdi # 1 param
        movq $0, %eax   # regra especial printf
        call printf

        # fim -------------------------------------------------------------
        jmp afterif
        else:
            #i ---> %r8d
            movl $5, %r8d

            while:
                #----------------------
                cmpl %esi, %r8d
                jle afterwhile
                #----------------------

                movslq %r8d, %r9    # i = (long)i
                addq %r9, a

                movq $a, %rdi
                call escape

                #----------------------
                jmp while
            afterwhile:

        afterif:

        addq $2, %r12 # ptr = ptr + sizeOf (deslocamento de memória)
        jmp for
    afterfor:

    #return (int)a;
    movq a, %r8
    movl %r8d, %eax

    movq -8(%rbp),  %r12
    movq -16(%rbp), %r13

    leave
    ret