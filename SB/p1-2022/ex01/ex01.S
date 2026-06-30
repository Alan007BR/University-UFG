.section .rodata
fmt: .string "%d, %ld\n"

.data
    .globl values
    .align 4
values: .long 10,20,10,40,20,50,30,10

.text
    .globl process

#di, si, dx, cx, r8,r9
#n usar: di,si,dx,ax
process:
    pushq %rbp
    movq %rsp, %rbp

    subq $48, %rsp #sempre multiplos de 16

    #int i ---> ecx
    movl $7, %ecx
    for:
    cmpl $0, %ecx # i>=0 ---> i < 0 -- int --> signed --> greater/less
    jl afterfor

    movq $values, %r8
    movslq %ecx, %r9
    imulq $4, %r9
    addq %r8, %r9
    movl (%r9), %r10d #r10d = values[i] = &values + (i*sizeof)

    #body
    if:
        cmpl %r10d, %edi # stamp > values[i] ---> stamp <= values[i] -- signed --> greater/less
        jle else

        #salva
        movq %rsi, -8(%rbp)
        movq %rdi, -16(%rbp)
        movq %rdx, -24(%rbp)
        movq %rcx, -32(%rbp) #i
        movq %r9, -40(%rbp) #r9 &values que pode ser destruído na chamada de aux


        #chama
        #aux((short)i, (values + i)      
        movw %cx, %di    #1param
        movq %r9, %rsi     #2 param
        call aux            #chamada

        #restaura
        movq -8(%rbp), %rsi
        movq -16(%rbp), %rdi
        movq -24(%rbp), %rdx
        movq -32(%rbp), %rcx #i
        movq -40(%rbp), %r9 #r11

        #limit = (2*limit)
        imulq $2, %rsi
        #limit = (2*limit) + aux((short)i, (values + i));
        movq %rax, %rsi
          

        jmp afterif
    else:
        movq %rsi, -8(%rbp)
        movq %rdi, -16(%rbp)
        movq %rdx, -24(%rbp)
        movq %rcx, -32(%rbp) #i

        #printf("%d, %ld\n", stamp, limit);
        movq %rsi, %rdx     #3 param
        movl %edi, %esi     #2 param
        movq $fmt, %rdi     #1 param

        call printf

        movq -8(%rbp), %rsi
        movq -16(%rbp), %rdi
        movq -24(%rbp), %rdx
        movq -32(%rbp), %rcx #i

    afterif:

    decl %ecx
    jmp for
    afterfor:

    #return limit
    movq %rsi, %rax
    leave
    ret