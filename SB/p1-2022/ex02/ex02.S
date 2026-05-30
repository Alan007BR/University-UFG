.section .rodata
fmt: .string "i = %d, sum = %d\n"
.data
    .globl max
    .align 4
max:    .long 256
    .globl lim
    .align 2
lim:    .word    -3

    .globl timer
    .align 1
timer: .byte 100

    .globl vet1
    .align 8
vet1:.quad 1, 0, 2, 3, 4

    .globl vet2
    .align 4
vet2:   .long 0,0,0,0,0

.text
    .globl basic
    .globl modify

#di, si, dx, cx, r8, r9
#return ax
# n usar, di, si, dx, ax
basic:
    pushq %rbp
    movq %rsp, %rbp

    subq $48, %rsp

    # parabéns rcx, você é o ptr
    movq $vet1, %rcx

    while:
        movsbl timer, %r8d
        cmpl %r8d, %edi # sum < timer --> sum >= timer ---> int --> signed --> greater/less
        jge afterwhile

        #_if (sum == 13) --> sum != 13 sum--> int --> signed --> greater/less
        if:
            cmpl $13, %edi
            jne afterif

            #break
            jmp afterwhile

        afterif: 

        #for (i<10 --> i>=10 signed --> greater/less)
        #i --> %r9
        movl $0, %r9d
        for:
            cmpl $10, %r9d
            jge afterfor

            #salvar
            movq %rsi, -8(%rbp)
            movq %rdi, -16(%rbp)
            movq %rdx, -24(%rbp)
            movq %rcx, -32(%rbp)
            movq %r9,  -40(%rbp)

            # printf("i = %d, sum = %d\n", i, sum);
            movl %edi, %edx     #3 param
            movq $fmt, %rdi     #1 param
            movl %r9d, %esi     #2 param
            movl $0, %rax       # regra especial do printf
            call printf

            #restaurar
            movq -8(%rbp), %rsi
            movq -16(%rbp), %rdi
            movq -24(%rbp), %rdx
            movq -32(%rbp), %rcx
            movq -40(%rbp), %r9

            incl %r9d
            incl %edi
            jmp for
        afterfor:       


        #salvar
        movq %rsi, -8(%rbp)
        movq %rdi, -16(%rbp)
        movq %rdx, -24(%rbp)
        movq %rcx, -32(%rbp)
        
        #modify(vet2, ptr, timer);
        movq $vet2, %rdi
        movq %rcx, %rsi
        movb timer, %dl
        call modify

        movq -8(%rbp), %rsi
        movq -16(%rbp), %rdi
        movq -24(%rbp), %rdx
        movq -32(%rbp), %rcx

        addq $8, %rcx
        jmp while
    afterwhile:

    leave
    ret

modify:
    pushq %rbp
    movq  %rsp, %rbp

    subq $32, %rsp

    # salva callee
    movq %r12, -8(%rbp)
    movq %r13, -16(%rbp)
    movq %r14, -24(%rbp)
    movq %r15, -32(%rbp)

    #index --> %r12

    while_modify:
    #calc(v2, v1)
        movq %rsi, %rdi #1 param
        movq %r12, %rsi #2 param
        call calc
        movb %al, %r13b #r13b = return de calc (char)
        mov  %rdi, %r12 #salvar v1


        cmpb %r13b, %dl # values > calc(v2, v1) --> values <= calc(v2, v1) -- char --> unsigned --> above/bellow
        jbe afterwhile_modify

        #index = complex(max, lim, v1);
        movl max, %edi
        movw lim, %si
        movq %r12, %rdx
        call complex
        movq %rax, %r12

        jmp while_modify
    afterwhile_modify:      

    # v1[ v2[index] ] = (int)value;
    #v2[index]
    movq $v2, %r14
    movq %r12,%r15
    imulq $4, %r15
    addq %r14,%r15

    movl (%r15), %r15d  # r15d = v2[index]

    #v1[ v2[index] ]
    movslq %r15d, %r15
    imulq $4, %r15
    addq %rcx, %r15
    movq (%r15), %r15 # r15 =  v1[ v2[index] ]

    movsbl %dl, %eax
    movl %eax, (%r15)   # v1[v2[index]] = (int)value

    # restaura calee
    movq -8(%rbp), %r12
    movq -16(%rbp), %r13
    movq -24(%rbp), %r14
    movq -32(%rbp), %r15

    leave
    ret